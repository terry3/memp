#include "pub.h"
#include "memp_i.h"
#include "memp.h"
#include "memp_l.h"
#include "memp_v.h"

F_RET memp_init()
{
    T_UINT32 ret = NULL_UINT32;
    ret = memp_l_create_list(&g_memp_list);
    FR_RET(ret);
    return T_OK;
}
