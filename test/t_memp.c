#include "../src/pub/pub.h"
#include "../src/memp.h"


#define MEMP_INIT_SIZE 1024
#define MEMP_GROW_SIZE 1024


int main(int argc, char *argv[])
{
    Memp memp = T_NULL;
    T_VOID *tmp = T_NULL;
    T_UINT32 ul_ret = 0;
    ul_ret = memp_create(&memp,
                         MEMP_INIT_SIZE,
                         MEMP_GROW_SIZE);

    FR_RET(ul_ret);

    tmp = (T_VOID*)memp_alloc(memp, 1024);
    PN_RET(tmp, -1);
    tmp = (T_VOID*)memp_alloc(memp, 1024);
    PN_RET(tmp, -1);

    return 0;
}

