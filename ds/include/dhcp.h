#ifndef DHCP_OL70 /*header guard*/
#define DHCP_OL70
/*******************************************************************************
* The functions in this file handle DHCP.
*
* Written by: OL-70
* Last update: 16:30 , 01.09.2019
*******************************************************************************/

#include <stddef.h>

typedef struct dhcp_s dhcp_t;
typedef unsigned int ip_t;


/*******************************************************************************
* Allocates memory for DHCP.
* net_ip - Network ip address.
* subnet_mask - Subnet Mask.
*
* Return Value: A pointer to the new DHCP.
* If memory allocation failes - NULL will be returned.
*******************************************************************************/
dhcp_t *DHCPCreate(ip_t net_ip, ip_t subnet_mask);

/*******************************************************************************
* Releases the memory that has been allocted for the DHCP.
*
* dhcp - a pointer to the DHCP. Cannot be NULL.
*******************************************************************************/
void DHCPDestroy(dhcp_t *dhcp);

/*******************************************************************************
* Allocates ip address.
*
* dhcp - pointer to the DHCP.
* res_ip - pointer to the allocted ip.
* requested_ip - ip requested by the user.
*
* Return Values:
*    0 - allocation has been successful.
*   -1 - allocation has failed - memory allocation error.
*   -2 - allocation has failed - no more adresses to allocate.
*******************************************************************************/
int DHCPAllocIP(dhcp_t *dhcp, ip_t *res_ip, ip_t requested_ip);

/*******************************************************************************
* Free a given address from the DHCP.
*
* dhcp - pointer to the DHCP.
* requested_ip - requested ip to free by the user.
*
* Return Values:
*    0 -free has been successful.
*   -1 -free has failed - non occupide IP.
*   -2 - free has failed - non valid IP.
*******************************************************************************/
int DHCPFreeIP(dhcp_t *dhcp, ip_t requested_ip);


/*******************************************************************************
* Counts number of allocated ip addresses.
*
* dhcp - pointer to the DHCP.
* Return Value: the number of allocated ip addresses in the DHCP.
*******************************************************************************/
size_t DHCPCountFree(const dhcp_t *dhcp);


/*******************************************************************************
* Convert ip_address to string.
*
* str - pointer to string. needed to be at least 16 bytes long.
*******************************************************************************/
void DHCPIpToString(ip_t ip_address, char *str);



#endif  /*DHCP_OL70*/
