#include "dhcp.h"
#include "tests_nir.h"

#include <stdio.h>
#include <stdlib.h>

TestResult CreateTest();
TestResult AllocTest();
TestResult FreeTest();
TestResult CountTest();
TestResult IpToStringTest();
TestResult FlowTest();

int main()
{
    RUN_TEST(CreateTest);
    RUN_TEST(AllocTest);
    RUN_TEST(FreeTest);
    RUN_TEST(CountTest);
    RUN_TEST(IpToStringTest);
    RUN_TEST(FlowTest);
    return (0);
}


TestResult CreateTest()
{
    dhcp_t *new_dhcp = DHCPCreate(0x0A0A0000, 0xFFFFFFF0);

    DHCPDestroy(new_dhcp);

    return (TEST_PASS);
}

TestResult AllocTest()
{
    dhcp_t *new_dhcp = DHCPCreate(0x0A0A0000, 0xFFFFFFF0);
    size_t i = 0;
    ip_t requested_ips[] = {0x0A0A0005, 0x0A0A0007, 0x0A0A0008, 0x0A0A0009, 0x0A0A0004};
    ip_t recived_ips[5] = {0};

    for (i = 0; i < 5; ++i)
    {
        REQUIRE(0 == DHCPAllocIP(new_dhcp, (recived_ips + i), requested_ips[i]));
    }

    DHCPDestroy(new_dhcp);

    return (TEST_PASS);
}

TestResult FreeTest()
{
    dhcp_t *new_dhcp = DHCPCreate(0x0A0A0000, 0xFFFFFFF0);
    size_t i = 0;
    ip_t requested_ips[] = {0x0A0A0005, 0x0A0A0007, 0x0A0A0008, 0x0A0A0009, 0x0A0A0004};
    ip_t recived_ips[5] = {0};
    ip_t garbage_ips[] = {0x0A0A0055, 0x0A0A0507, 0x0A0A5008, 0x0A000009, 0x010A0004};

    for (i = 0; i < 5; ++i)
    {
        DHCPAllocIP(new_dhcp, (recived_ips + i), requested_ips[i]);
    }

    for (i = 0; i < 5; ++i)
    {
        REQUIRE(0 == DHCPFreeIP(new_dhcp, recived_ips[4 - i]));
    }

    for (i = 0; i < 5; ++i)
    {
        REQUIRE(-1 == DHCPFreeIP(new_dhcp, recived_ips[4 - i]));
    }

    for (i = 0; i < 5; ++i)
    {
        REQUIRE(-2 == DHCPFreeIP(new_dhcp, garbage_ips[i]));
    }

    DHCPDestroy(new_dhcp);

    return (TEST_PASS);
}

TestResult CountTest()
{
    dhcp_t *new_dhcp = DHCPCreate(0x0A0A0000, 0xFFFFFFF0);
    size_t i = 0;
    ip_t requested_ips[] = {0x0A0A0005, 0x0A0A0007, 0x0A0A0008, 0x0A0A0009, 0x0A0A0004};
    ip_t recived_ips[5] = {0};


    REQUIRE(13 == DHCPCountFree(new_dhcp));

    for (i = 0; i < 5; ++i)
    {
        REQUIRE(0 == DHCPAllocIP(new_dhcp, (recived_ips + i), requested_ips[i]));
        REQUIRE((13 - i -1) == DHCPCountFree(new_dhcp));
    }

    for (i = 0; i < 5; ++i)
    {
        REQUIRE(0 == DHCPFreeIP(new_dhcp, recived_ips[4 - i]));
        REQUIRE((13 + i -4) == DHCPCountFree(new_dhcp));
    }

    DHCPDestroy(new_dhcp);

    return (TEST_PASS);
}

TestResult IpToStringTest()
{
    dhcp_t *new_dhcp = DHCPCreate(0x0A0A0000, 0xFFFFFFF0);
    size_t i = 0;
    ip_t requested_ips[] = {0x0A0A0005, 0x0A0A0007, 0x0A0A0008, 0x0A0A0009, 0x0A0A0004};
    ip_t recived_ips[5] = {0};
    char *string = malloc(16*sizeof(char));


    REQUIRE(13 == DHCPCountFree(new_dhcp));

    for (i = 0; i < 5; ++i)
    {
        REQUIRE(0 == DHCPAllocIP(new_dhcp, (recived_ips + i), requested_ips[i]));
    }

    for (i = 0; i < 5; ++i)
    {
        DHCPIpToString(recived_ips[i], string);
        printf("%s\n", string);
    }

    DHCPDestroy(new_dhcp);

    return (TEST_PASS);
}

TestResult FlowTest()
{
    dhcp_t *new_dhcp = DHCPCreate(0x0A0A0000, 0xFFFFFF00);
    size_t i = 0;
    ip_t requested_ips[253] = {0};
    ip_t recived_ips[253] = {0};
    ip_t garbage_ip = 0x0A0A0000;

    for (i = 0; i < 253; ++i)
    {
        requested_ips[i] = 0x0A0A0000 + i;
    }

    REQUIRE(253 == DHCPCountFree(new_dhcp));

    for (i = 0; i < 253; ++i)
    {
        REQUIRE(0 == DHCPAllocIP(new_dhcp, (recived_ips + i), requested_ips[i]));
        REQUIRE((253 - i -1) == DHCPCountFree(new_dhcp));
        /*printf("%lu\n", DHCPCountFree(new_dhcp));*/
    }

    REQUIRE(-2 == DHCPAllocIP(new_dhcp, &garbage_ip, garbage_ip));

    for (i = 0; i < 253; ++i)
    {
        REQUIRE(0 == DHCPFreeIP(new_dhcp, recived_ips[252 - i]));
        REQUIRE((1 + i) == DHCPCountFree(new_dhcp));
    }

    DHCPDestroy(new_dhcp);

    return (TEST_PASS);
}
