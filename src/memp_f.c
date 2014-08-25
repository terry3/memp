#include "pub.h"
#include "memp.h"
#include "memp_l.h"
#include "memp_v.h"

F_RET memp_create(Memp *memp)
{
    Memp_n *node = T_NULL;
    T_UINT32 ret = NULL_UINT32;
    PN_RET(memp, NULL_PTR);

    ret = memp_l_create_memp(g_memp_list, &node);
    FR_RET(ret);

    *memp = &(node->memp);
/* todo: implement the 2 function */
    /* set memp alloc/free function */
    /* (*memp)->alloc = T_NULL; */
    /* (*memp)->free  = T_NULL; */

    return T_OK;
}

F_RET memp_free(Memp memp)
{
    Memp_n          *memp_n = T_NULL;
    T_UINT32         ret    = NULL_UINT32;

    PN_RET(memp, NULL_PTR);

    memp_n = F_GETSP(memp, Memp_n, memp);
    ret = memp_l_remove_mem_list_all(memp_n->list);
    FR_RET(ret);

    return T_OK;
}

T_VOID* memp_alloc(Memp memp, T_UINT32 size, T_UINT32 tag)
{
    Memp_n          *memp_n = T_NULL;
    Memp_mem_l      *list   = T_NULL;
    T_UINT32         ret    = NULL_UINT32;
    PN_RET(memp, T_NULL);
    memp_n = F_GETSP(memp, Memp_n, memp);
    list = memp_n->list;
    PN_RET(list, T_NULL);
    ret = memp_l_create_insert_memp_mem_list(list, size, tag);
    F_NCHK_RET(ret, T_OK, T_NULL);

    return (T_VOID*)list->head->p;
}
