/****************************************************************************
Name: 					Roy Yablonka
Project:				DHCP

Reviewer Name:			Nir
Version:				Fixing

Time of Last Change:	04/09/2019	08:55
****************************************************************************/

#include <stdlib.h>		/* malloc */
#include <stdio.h>		/* sprintf */
#include <math.h>		/* pow 	*/
#include <string.h>		/* strcpy */
#include <assert.h>		/* assert */

#include "dhcp.h"

#define NUM_OF_CHILDREN 	(2)
#define LEFT 				(0)
#define RIGHT 				(1)
#define BYTES_IN_IP_ADD 	(4)
#define BITS_IN_BYTE 		(8)

typedef struct dhcp_node_s dhcp_node_t;

struct dhcp_s
{
    dhcp_node_t *root;
    ip_t net_ip;
    ip_t subnet_mask;
};

struct dhcp_node_s
{
    dhcp_node_t *parent;
    dhcp_node_t *child[NUM_OF_CHILDREN];
    int is_occupied;
};

/*******************************************************************************
* 							STATIC FUNCTIONS DECLARATIONS
*******************************************************************************/

static dhcp_node_t *DHCPNodeCreate(dhcp_node_t *parent);
static void FreeTree(dhcp_node_t *root);

static size_t RetrieveHeight(ip_t subnet_mask);

static int HasNoChildren(dhcp_node_t *node);
static int HasRightChild(dhcp_node_t *node);
static int HasLeftChild(dhcp_node_t *node);
static int HasChild(dhcp_node_t *node);

static int HasOccupiedLeftChild(dhcp_node_t *node);
static int HasOccupiedRightChild(dhcp_node_t *node);

static int IsValidIP(dhcp_t *dhcp, ip_t ip);
static void UpdateOccupation(dhcp_node_t *occupied_node);
static int IsOccupied(const dhcp_t *dhcp, ip_t ip);

static dhcp_node_t *FreeNodeUntilLastIntersection(dhcp_node_t *node);
static int WhichChild(dhcp_node_t *mother, dhcp_node_t *daughter);

static ip_t FindNextAvailIP(dhcp_t *dhcp);
static int DoesRouteExistInDHCP(dhcp_t *dhcp, ip_t ip);
static ip_t ModifyValue(int original, int height);

/*******************************************************************************
* 								API IMPLEMANTATION
*******************************************************************************/

dhcp_t *DHCPCreate(ip_t net_ip, ip_t subnet_mask)
{
	dhcp_t *dhcp = malloc(sizeof(dhcp_t));
	ip_t ip1 = 0;
	ip_t ip2 = 0;
	ip_t ip3 = 0;

	if (NULL == dhcp)
	{
		return (NULL);
	}

	dhcp->root = DHCPNodeCreate(NULL);

	if (NULL == dhcp->root)
	{
		free(dhcp);
		return (NULL);
	}

	dhcp->net_ip = net_ip;
	dhcp->subnet_mask = subnet_mask;

	DHCPAllocIP(dhcp, &ip1, (net_ip));
	DHCPAllocIP(dhcp, &ip2, (net_ip) + 1);
	DHCPAllocIP(dhcp, &ip3, (net_ip) + (~subnet_mask));

	if ((ip1 != net_ip) || (ip2 != (net_ip + 1)) || (ip3 != (net_ip | ~subnet_mask)))
	{
		DHCPDestroy(dhcp);
	}

	return (dhcp);
}

void DHCPDestroy(dhcp_t *dhcp)
{
	assert(NULL != dhcp);

	FreeTree(dhcp->root);

	dhcp->root->child[LEFT] = NULL;
	dhcp->root->child[RIGHT] = NULL;
	dhcp->root->is_occupied = 0;
	dhcp->root->parent = NULL;

	free(dhcp->root);	dhcp->root = NULL;
	free(dhcp);
}

int DHCPAllocIP(dhcp_t *dhcp, ip_t *res_ip, ip_t requested_ip)
{
	ip_t route = 0;
	ip_t mask = 0x01;
	dhcp_node_t *runner = NULL;
	int height = 0;
	int dig = 0;

	assert(NULL != dhcp);
	assert(NULL != res_ip);

	height = RetrieveHeight(~(dhcp->subnet_mask));
	route = requested_ip & ~(dhcp->subnet_mask);
	route = ModifyValue(route, height);
	runner = dhcp->root;

	if ((!IsValidIP(dhcp, requested_ip)) || (DoesRouteExistInDHCP(dhcp, route)))
	{
		requested_ip = dhcp->net_ip + FindNextAvailIP(dhcp);
		route = requested_ip;
	}

	while ((height > 0))
	{
		dig = (route & mask);
		route = route >> 1;

		if ((runner->child[dig] != NULL) && ((height == 1)))
		{
			return (-2);
		}

		if (runner->child[dig] == NULL)
		{
			runner->child[dig] = DHCPNodeCreate(runner);

			if (NULL == runner->child[dig])
			{
				return (-1);
			}
		}

		runner = runner->child[dig];

		if (height == 1)
		{
			runner->is_occupied = 1;
		}
		--height;
	}

	*res_ip = requested_ip;

	UpdateOccupation(runner);
	return (0);
}

int DHCPFreeIP(dhcp_t *dhcp, ip_t requested_ip)
{
	ip_t mask = 0x01;
	dhcp_node_t *runner = NULL;
	int height = 0;
	ip_t route = 0;
	int dig = 0;

	assert(NULL != dhcp);

	runner = dhcp->root;
	height = RetrieveHeight(~(dhcp->subnet_mask));
	route = ModifyValue(requested_ip & ~(dhcp->subnet_mask), height);

	if ((dhcp->subnet_mask & dhcp->net_ip) != (dhcp->subnet_mask & requested_ip))
	{
		return (-2);
	}

	while (height > 0)
	{
		dig = (route & mask);
		route = route >> 1;

		if (runner->child[dig] == NULL)
		{
			return (-1);
		}

		runner = runner->child[dig];

		--height;
	}

	runner = FreeNodeUntilLastIntersection(runner);
	UpdateOccupation(runner);

	return (0);
}

size_t DHCPCountFree(const dhcp_t *dhcp)
{
	int height = 0;
	size_t i = 0;
	size_t end_value = 0;
	size_t counter = 0;

	assert(NULL != dhcp);

	height = RetrieveHeight(~(dhcp->subnet_mask));
	end_value = pow(2, height);

	for (i = 0; i < end_value; ++i)
	{
		counter += IsOccupied(dhcp, i);
	}

	return(end_value - counter);
}


void DHCPIpToString(ip_t ip_address, char *str)
{
	int mask = 0xFF000000;
	int i = 0;

	assert(NULL != str);

	strcpy(str, "\0");

	for (i = 0; i < BYTES_IN_IP_ADD; ++i)
	{
		int curr_value = (mask & ip_address) >> (3 * BITS_IN_BYTE);
		char str_num[5];
		if (i < (BYTES_IN_IP_ADD - 1))
		{
			sprintf(str_num,"%d.", curr_value);
		}
		else
		{
			sprintf(str_num,"%d", curr_value);
		}

		strcat(str, str_num);
		ip_address = ip_address << BITS_IN_BYTE;
	}
}

/*******************************************************************************
* 							STATIC FUNCTIONS IMPLEMANTATIONS
*******************************************************************************/

static dhcp_node_t *DHCPNodeCreate(dhcp_node_t *parent)
{
	dhcp_node_t *node = malloc(sizeof(dhcp_node_t));

	if (NULL == node)
	{
		return (NULL);
	}

	node->parent = parent;
	node->child[LEFT] = NULL;
	node->child[RIGHT] = NULL;
	node->is_occupied = 0;

	return (node);
}

static size_t RetrieveHeight(ip_t subnet_mask)
{
	size_t height = 0;

	while (subnet_mask > 0)
	{
		subnet_mask = subnet_mask >> 1;
		++height;
	}

	return (height);
}

static void FreeTree(dhcp_node_t *root)
{
	dhcp_node_t *runner = root;

	while ((runner != root) || HasChild(runner))
	{
		if (HasRightChild(runner))
		{
			runner = runner->child[RIGHT];
		}
		else if (HasLeftChild(runner))
		{
			runner = runner->child[LEFT];
		}
		else
		{
			dhcp_node_t *temp_runner = runner->parent;

			temp_runner->child[temp_runner->child[RIGHT] == runner] = NULL;

			runner->parent = NULL;
			runner->child[LEFT] = NULL;
			runner->child[RIGHT] = NULL;
			runner->is_occupied = 0;

			free(runner);

			runner = temp_runner;
		}
	}
}

static int HasNoChildren(dhcp_node_t *node)
{
	return ((node->child[RIGHT] == NULL) && (node->child[LEFT] == NULL));
}

static int HasRightChild(dhcp_node_t *node)
{
	return ((node->child[RIGHT] != NULL));
}

static int HasLeftChild(dhcp_node_t *node)
{
	return ((node->child[LEFT] != NULL));
}

static int HasChild(dhcp_node_t *node)
{
	return (HasRightChild(node) || HasLeftChild(node));
}

static int IsValidIP(dhcp_t *dhcp, ip_t ip)
{
	ip_t range = ~(dhcp->subnet_mask);

	if ((ip > dhcp->net_ip) && (ip <= (dhcp->net_ip + range)))
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

static int HasOccupiedLeftChild(dhcp_node_t *node)
{
	if (HasLeftChild(node))
	{
		return (node->child[LEFT]->is_occupied);
	}

	return (0);
}

static int HasOccupiedRightChild(dhcp_node_t *node)
{
	if (HasRightChild(node))
	{
		return (node->child[RIGHT]->is_occupied);
	}

	return (0);
}

static void UpdateOccupation(dhcp_node_t *occupied_node)
{
	dhcp_node_t *runner = occupied_node->parent;

	while (runner->parent != NULL)
	{
		if (HasOccupiedLeftChild(runner) && HasOccupiedRightChild(runner))
		{
			runner->is_occupied = 1;
		}

		runner = runner->parent;
	}
}

static int IsOccupied(const dhcp_t *dhcp, ip_t ip)
{
	ip_t route = ip & ~(dhcp->subnet_mask);
	ip_t mask = 0x01;
	dhcp_node_t *runner = dhcp->root;
	int height = RetrieveHeight(~(dhcp->subnet_mask));
	int dig = 0;

	while (height > 0)
	{
		dig = (route & mask);
		route = route >> 1;

		if (runner->child[dig] == NULL)
		{
			return (0);
		}

		runner = runner->child[dig];

		--height;
	}

	return (runner->is_occupied);
}

static dhcp_node_t *FreeNodeUntilLastIntersection(dhcp_node_t *node)
{
	while (HasNoChildren(node))
	{
		dhcp_node_t *parent = node->parent;
		parent->child[WhichChild(parent, node)] = NULL;
		free(node);
		node = parent;
	}

	return (node);
}

static int WhichChild(dhcp_node_t *mother, dhcp_node_t *daughter)
{
	return(mother->child[RIGHT] == daughter);
}

static ip_t FindNextAvailIP(dhcp_t *dhcp)
{
	int height = RetrieveHeight(~(dhcp->subnet_mask));
	size_t end_value = pow(2, height);
	size_t  i = 0;

	for (i = 0; i < end_value; ++i)
	{
		int temp = ModifyValue(i, height);
		if (!DoesRouteExistInDHCP(dhcp, temp))
		{
			return (temp);
		}
	}

	return (0);
}

static int DoesRouteExistInDHCP(dhcp_t *dhcp, ip_t route)
{
	ip_t mask = 0x01;
	dhcp_node_t *runner = dhcp->root;
	int height = RetrieveHeight(~(dhcp->subnet_mask));
	int dig = 0;

	while (height > 0)
	{
		dig = (route & mask);
		route = route >> 1;

		if (runner->child[dig] == NULL)
		{
			return (0);
		}

		runner = runner->child[dig];

		--height;
	}

	return (1);
}

static ip_t ModifyValue(int original, int height)
{
	int mask = 0x01;
	int i = 0;
	ip_t new_value = 0;

	for (i = 0; i < height; ++i)
	{
		new_value = new_value << 1;
		new_value = new_value | ((mask & original) == mask) ;
		mask = mask << 1;
	}

	return (new_value);
}
