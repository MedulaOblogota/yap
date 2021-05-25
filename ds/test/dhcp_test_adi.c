#include <unistd.h>

#include "dhcp.h"
#include "tests_adi.h"



void TestDHCPCreateAndDestroy();
void TestDHCPAllocAndFreeIP();

int main()
{
    TestDHCPCreateAndDestroy();
    TestDHCPAllocAndFreeIP();

    return (0);
}

void TestDHCPCreateAndDestroy()
{
    char *creation_msg = "DHCP creation!\n";
    char *count_msg = "DHCPCountFree!\n";
    ip_t net_ip = 0x0A0101F0; /*10.1.1.0*/
    ip_t subnet_mask = 0xFFFFFFF0; /*255.255.255.0*/
    dhcp_t *dhcp = DHCPCreate(net_ip, subnet_mask);

    puts(CYN "\n********* Testing DHCPCreate & DHCPDestroy ***********\n" RESET);

    Check(NULL != dhcp, creation_msg, 0);

    puts("------Count free IPs after DHCP creation------\n");
    puts(YEL "***Should be IP pool size minus three***\n" RESET);
    Check(13 == DHCPCountFree(dhcp), count_msg, 0);
    printf("Free IPs: %lu\n", DHCPCountFree(dhcp));

    puts(BOLD "\nNOTE: to complete DHCPDestroy test - run valgrind command." RESET);

    DHCPDestroy(dhcp);

    puts(CYN "\n******************************************************\n" RESET);
}

void TestDHCPAllocAndFreeIP()
{
    char *creation_msg = "DHCP creation.";
    char *alloc_msg = "IP allocation.";
    char *free_msg = "freeing IP.";
    ip_t net_ip = 0x0A0101F0; /*10.1.1.0*/
    ip_t subnet_mask = 0xFFFFFFF0; /*255.255.255.0*/
    dhcp_t *dhcp = DHCPCreate(net_ip, subnet_mask);
    char str_ip[16] = {'\0'};
    ip_t ip_runner = (net_ip | 0x02);
    ip_t last_ip = (net_ip | 0x0F);
    ip_t res_ip = 0;
    int status = 0;
    size_t i = 1;

    puts(CYN "\n********** Testing DHCPAllocIP & DHCPFreeIP **********\n" RESET);

    Check(NULL != dhcp, creation_msg, 0);

    puts(BOLD YEL "\n************ Start allocating ips ************\n" RESET);
    sleep(3);

    while ((0 == status) && (ip_runner < last_ip))
    {
        printf("-------- Allocating IP number %lu --------\n\n", i);
        printf("Requested IP: ");
        DHCPIpToString(ip_runner, str_ip);
        status = DHCPAllocIP(dhcp, &res_ip, ip_runner);
		printf("res_ip=%d\nip_runner=%d\n", res_ip, ip_runner);
		printf("status=%d\n", status);
        Check(ResCmp(0, status) && ResCmp(res_ip, ip_runner), alloc_msg, 0);
        ++ip_runner;
        ++i;
        printf("\n\n");
        sleep(1);
    }

    puts(BOLD "Allocating IPs is done!.\n" RESET);
    printf(BOLD "Free IPs left after allocating: %lu\n\n\n\n\n" RESET,
                                                            DHCPCountFree(dhcp));
    sleep(3);

    ip_runner = (net_ip | 0x02);
    i = 0;

    puts("---------------------------------------\n");
    puts(BOLD YEL "\n************ Start freeing ips ************\n" RESET);
    sleep(3);

    while ((0 == status) && (ip_runner < last_ip))
    {
        printf("---------- Freeing IP number %lu ---------\n\n", i);
        printf("IP to free: ");
        DHCPIpToString(ip_runner, str_ip);
        status = DHCPFreeIP(dhcp, ip_runner);
        Check(ResCmp(0, status), free_msg, 0);
        ++ip_runner;
        ++i;
        printf("\n\n");
        sleep(1);
    }

    DHCPDestroy(dhcp);

    puts(CYN "\n******************************************************\n" RESET);
}
