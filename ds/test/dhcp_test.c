#include <string.h>
#include <stdio.h>

#include "dhcp.h"
#include "tests.h"

#define RESET "\x1B[0m"
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"

void TestDHCPCreateAndDestroy();
void TestDHCPAllocIPFreeIPAndCount();
void TestDHCPIpToString();

int main()
{
	TestDHCPCreateAndDestroy();
	TestDHCPAllocIPFreeIPAndCount();
	TestDHCPIpToString();

	return (0);
}

void TestDHCPCreateAndDestroy()
{
	ip_t ip = 0x0a0101f0;	/* 10.1.1.240 */
	ip_t sm = 0xfffffff0;	/* 255.255.255.128 */
	dhcp_t *dhcp = DHCPCreate(ip, sm);

	if (dhcp != NULL)
	{
		printf(GRN"success with DHCPCreate (dont get your hopes up, its only Create)\n"RESET);
	}
	else
	{
		printf(RED"FAILURE with DHCPCreate......!!\n"RESET);
	}

	DHCPDestroy(dhcp);
}

void TestDHCPAllocIPFreeIPAndCount()
{
	ip_t ip = 0x0a0101f0;	/* 10.1.1.240 */
	ip_t sm = 0xfffffff0;	/* 255.255.255.240 */
	dhcp_t *dhcp = DHCPCreate(ip, sm);
	ip_t bad_ip = 0x0a0102f0;
	ip_t good_ip = 0x0a0101fe;
	ip_t res_ip;
	size_t size = 0;
	ip_t ip1 = 0;
	ip_t ip2 = 0;
	ip_t ip3 = 0;

	size = DHCPCountFree(dhcp);
	WrapperCompareSizet("DHCPCountFree for empty DHCP", size, 13);

	WrapperCompareInt("DHCPAllocIP for bad IP", DHCPAllocIP(dhcp, &res_ip, bad_ip), 0);

	if (res_ip != bad_ip)
	{
		printf(GRN"Asking for a bad IP resulted with a different IP!\n"RESET);
	}
	else
	{
		printf(RED"Asking for a bad IP resulted with a bad IP!\n"RESET);
	}

	WrapperCompareInt("DHCPAllocIP for good IP", DHCPAllocIP(dhcp, &res_ip, good_ip), 0);
	WrapperCompareInt("Comparing the actual IPs as requested for a good IP", (int)res_ip, (int)good_ip);

	WrapperCompareInt("DHCPAllocIP for existing good IP", DHCPAllocIP(dhcp, &res_ip, good_ip), 0);

	if (res_ip != good_ip)
	{
		printf(GRN"Asking for an existing IP resulted with a different IP!\n"RESET);
	}
	else
	{
		printf(RED" Asking for an existing IP resulted with the existing IP!\n"RESET);
	}

	WrapperCompareSizet("DHCPCountFree", DHCPCountFree(dhcp), 10);

	WrapperCompareInt("Freeing an existing IP", DHCPFreeIP(dhcp, good_ip), 0);
	WrapperCompareInt("Freeing a freed IP", DHCPFreeIP(dhcp, good_ip), -1);

	WrapperCompareSizet("DHCPCountFree after free", DHCPCountFree(dhcp), 11);

	WrapperCompareInt("Allocating a freed good IP", DHCPAllocIP(dhcp, &res_ip, good_ip), 0);

	if (res_ip == good_ip)
	{
		printf(GRN"Asking for a good freed IP resulted with the good IP!\n"RESET);
	}
	else
	{
		printf(RED"Asking for a good freed IP did not result with the good IP!\n"RESET);
	}

	WrapperCompareSizet("DHCPCountFree", DHCPCountFree(dhcp), 10);

	DHCPAllocIP(dhcp, &ip1, 0);
	DHCPAllocIP(dhcp, &ip2, 0);
	DHCPAllocIP(dhcp, &ip3, 0);
	DHCPAllocIP(dhcp, &res_ip, 0);
	DHCPAllocIP(dhcp, &res_ip, 0);
	DHCPAllocIP(dhcp, &res_ip, 0);
	DHCPAllocIP(dhcp, &res_ip, 0);

	WrapperCompareSizet("DHCPCountFree", DHCPCountFree(dhcp), 3);

	DHCPAllocIP(dhcp, &res_ip, 0);
	DHCPAllocIP(dhcp, &res_ip, 0);
	DHCPAllocIP(dhcp, &res_ip, 0);

	WrapperCompareSizet("DHCPCountFree for a full DHCP", DHCPCountFree(dhcp), 0);

	WrapperCompareInt("Allocating a good IP to a full DHCP", DHCPAllocIP(dhcp, &res_ip, good_ip), -2);
	WrapperCompareInt("Allocating a bad IP to a full DHCP", DHCPAllocIP(dhcp, &res_ip, 0), -2);
	WrapperCompareInt("Allocating a bad IP to a full DHCP", DHCPAllocIP(dhcp, &res_ip, 0), -2);

	WrapperCompareSizet("DHCPCountFree for a full DHCP", DHCPCountFree(dhcp), 0);

	WrapperCompareInt("Freeing an existing IP", DHCPFreeIP(dhcp, good_ip), 0);
	WrapperCompareInt("Freeing an existing IP", DHCPFreeIP(dhcp, ip1), 0);
	WrapperCompareInt("Freeing an existing IP", DHCPFreeIP(dhcp, ip2), 0);
	WrapperCompareInt("Freeing an existing IP", DHCPFreeIP(dhcp, ip3), 0);

	DHCPDestroy(dhcp);
}

void TestDHCPIpToString()
{
	ip_t ip = 0x0a0101f0;	/* 10.1.1.240 */
	ip_t sm = 0xfffffff0;	/* 255.255.255.240 */
	char str_ip[30];
	char ip_in_string[] = "10.1.1.240";
	char sm_in_string[] = "255.255.255.240";

	DHCPIpToString(ip, str_ip);
	WrapperCompareStringsWithStrLen("comparing ip1 to string", (char *)ip_in_string, (char *)str_ip);
	/*printf("str_ip=%s\nip_in_string=%s\n", str_ip, ip_in_string);*/

	DHCPIpToString(sm, str_ip);
	WrapperCompareStringsWithStrLen("comparing ip2 to string", (char *)sm_in_string, (char *)str_ip);
	/*printf("str_ip=%s\nsm_in_string=%s\n", str_ip, sm_in_string);*/


}
