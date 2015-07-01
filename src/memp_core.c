#include "./pub/pub.h"
#include "memp.h"
#include "memp_private.h"

/* create memp */
F_RET memp_create
(
    Memp      *pps_memp,
    T_UINT32   ul_init_size,
    T_UINT32   ul_grow_size
)
{
    Memp_p  *ps_mempp = T_NULL;
    Mem_hdr *ps_hdr   = T_NULL;
    PN_RET(pps_memp, MEMP_NULL_PTR);

    ps_mempp = (Memp_p*)malloc(sizeof(*ps_mempp));
    PN_RET(ps_mempp, MEMP_NULL_PTR);
    F_ZERO(ps_mempp, sizeof(*ps_mempp));
    ps_mempp->ul_grow_size = ul_grow_size;
    ps_mempp->ul_size = 0;
    ps_mempp->ul_magic = MEMP_MAGIC;
    ps_mempp->pc_mem_addr = (Mem_hdr*)malloc(sizeof(Mem_hdr) + ul_init_size);
    PN_RET(ps_mempp->pc_mem_addr, MEMP_NULL_PTR);
    F_ZERO(ps_mempp->pc_mem_addr, sizeof(Mem_hdr));
    ps_hdr = (Mem_hdr*)(ps_mempp->pc_mem_addr);
    ps_hdr->pc_next_hdr = T_NULL; /* have no next mem_hdr */
    ps_hdr->ul_size = ul_init_size;
    ps_hdr->ul_left = ul_init_size;
    ps_hdr->pc_curr = (T_CHAR*)ps_hdr + sizeof(Mem_hdr);
    *pps_memp = (Memp)ps_mempp;
    return F_SUCCESS;
}

/* alloc another mem_hdr to alloc memory */
F_RET memp_alloc_another
(
    Memp    ps_memp_in
)
{
    Memp_p  *ps_memp  = T_NULL;
    Mem_hdr *ps_hdr   = T_NULL;
    T_UINT32 ul_grow_size = 0;

    PN_RET(ps_memp_in, MEMP_NULL_PTR);

    ps_memp = (Memp_p*)ps_memp_in;

    ul_grow_size = ps_memp->ul_grow_size;
    ps_hdr = (Mem_hdr*)malloc(ul_grow_size);
    PN_RET(ps_hdr, MEMP_NULL_PTR);
    F_ZERO(ps_hdr, sizeof(Mem_hdr));

    ps_hdr->pc_next_hdr = ps_memp->pc_mem_addr; /* change to original mem_hdr */
    ps_hdr->ul_size = ul_grow_size;
    ps_hdr->ul_left = ul_grow_size;
    ps_hdr->pc_curr = (T_CHAR*)ps_hdr + sizeof(Mem_hdr);
    ps_memp->pc_mem_addr = ps_hdr; /* refresh memp pointer */
    return F_SUCCESS;
}

/* use memp alloc memory */
T_VOID* memp_alloc
(
    Memp     ps_memp_in,
    T_UINT32 ul_size
)
{
    Memp_p  *ps_memp = T_NULL;
    Mem_hdr *ps_hdr   = T_NULL;
    T_VOID  *p_ret    = T_NULL;
    F_RET    ul_ret   = 0;
    PN_RET(ps_memp_in, T_NULL);
    ps_memp = (Memp_p*)ps_memp_in;
    F_CHK_MAGIC(ps_memp, T_NULL);

    ps_hdr = ps_memp->pc_mem_addr;

    if (ul_size > ps_hdr->ul_left) {
        ul_ret = memp_alloc_another((Memp)ps_memp);/* alloce another mem_hdr */
        FR_CRET(ul_ret, T_NULL);
    }

    ps_hdr   = ps_memp->pc_mem_addr;
    ps_hdr->ul_left -= ul_size; /* refresh left memory size */
    p_ret = (T_VOID*)(ps_hdr->pc_curr);    /* return pointer */
    ps_hdr->pc_curr += ul_size;
    ps_memp->ul_size += ul_size;
    return p_ret;
}

/* void memp_delete memp */
T_VOID memp_delete
(
    Memp *pps_memp_in
)
{
    Memp_p  *ps_memp     = T_NULL;
    Mem_hdr *ps_hdr      = T_NULL;
    Mem_hdr *ps_hdr_next = T_NULL;

    PN_RET_N(pps_memp_in);
    ps_memp = (Memp_p*)(*pps_memp_in);

    F_CHK_MAGIC_N(ps_memp);

    ps_hdr = ps_memp->pc_mem_addr;
    ps_hdr_next = ps_hdr;

    /* loop free mem hdr */
    while (ps_hdr) {
        ps_hdr_next = ps_hdr->pc_next_hdr;
        free(ps_hdr);
        ps_hdr = ps_hdr_next;
    }

    free(ps_memp);
    return;
}
/* void memp_dump memp */
T_VOID memp_dump
(
    Memp ps_memp_in
)
{
    Memp_p  *ps_memp     = T_NULL;
    Mem_hdr *ps_hdr      = T_NULL;
    Mem_hdr *ps_hdr_next = T_NULL;
    T_UINT32 ul_index    = 0;

    PN_RET_N(ps_memp_in);
    ps_memp = (Memp_p*)ps_memp_in;

    printf("*** Memp ***\n");
    printf("alloc size=[%d]\n", ps_memp->ul_size);
    printf("grow size=[%d]\n", ps_memp->ul_grow_size);

    ps_hdr = ps_memp->pc_mem_addr;
    ps_hdr_next = ps_hdr;
    ul_index = 0;
    /* loop free mem hdr */
    while (ps_hdr) {
        ps_hdr_next = ps_hdr->pc_next_hdr;
        printf("==>page[%d] size=[%d]\n", ul_index, ps_hdr->ul_size);
        printf("==>page[%d] left size=[%d]\n", ul_index, ps_hdr->ul_left);
        ps_hdr = ps_hdr_next;
        ul_index++;
    }
    return;
}
