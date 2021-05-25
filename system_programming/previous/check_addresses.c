#include <stdio.h>
#include <stdlib.h>

int init_global = 5;
int uninit_global;
/*extern int init_extern_global = 1;*/
extern int uninit_extern_global;
/*extern const int init_extern_const_global = 2;*/
extern const int uninit_extern_const_global;
const int init_const_global = 2;
const int uninit_const_global;
static int init_static_global = 7;
static int uninit_static_global;

static void staticfunc()
{
    return;
}

void regularfunc()
{
    return;
}

int main()
{
    int init_local = 4;
    int uninit_local;

    static int init_static_local = 3;
    static int uninit_static_local;

    /*extern int init_extern_local = 1;*/
    extern int uninit_extern_local;

    /*extern const int init_extern_const_local = 2;*/
    extern const int uninit_extern_const_local;

    const int init_const_local = 2;
    const int uninit_const_local;

    int *malloced = NULL;
    int *null = NULL;

    void (*func)() = &regularfunc;
    static void (*func2)() = &staticfunc;

    int (*libc_so_func)( const char * format, ... ) = printf;

    uninit_local = 6;
    malloced = malloc(sizeof(int));

    printf("init_local: %p\n", &init_local);
    printf("uninit_local: %p\n", &uninit_local);
    printf("init_static_local: %p\n", &init_static_local);
    printf("uninit_static_local: %p\n", &uninit_static_local);
    /*printf("uninit_extern_local: %p\n", &uninit_extern_local);
    printf("uninit_extern_const_local: %p\n", &uninit_extern_const_local);*/
    printf("init_const_local: %p\n", &init_const_local);
    printf("uninit_const_local: %p\n", &uninit_const_local);
    printf("&regularfunc: %p\n", regularfunc);
    printf("&staticfunc: %p\n", staticfunc);
    printf("printf: %p\n", printf);
    printf("********************************************\n");
    printf("init_global: %p\n", &init_global);
    printf("uninit_global: %p\n", &uninit_global);
    /*printf("uninit_extern_global: %p\n", &uninit_extern_global);
    printf("uninit_extern_const_global: %p\n", &uninit_extern_const_global);*/
    printf("init_const_global: %p\n", &init_const_global);
    printf("uninit_const_global: %p\n", &uninit_const_global);

    printf("init_static_global: %p\n", &init_static_global);
    printf("uninit_static_global: %p\n", &uninit_static_global);

    return (0);




}
