#ifndef MEMP_PRIVATE_H
#define MEMP_PRIVATE_H

typedef struct _mem_hdr Mem_hdr;
struct _mem_hdr
{
    Mem_hdr   *pc_next_hdr;     /* next mem_hdr, if have no next will be NULL */
    T_UINT32   ul_size;         /* total size */
    T_UINT32   ul_left;         /* left size */
    T_CHAR    *pc_curr;         /* curr pointer to alloc */
};

typedef struct _memp_p
{
    Mem_hdr  *pc_mem_addr;      /* mem_hdr address */
    T_UINT32  ul_size;          /* alloced memory size */
    T_UINT32  ul_grow_size;     /* alloced grow size */
    T_UINT32  ul_magic;         /* magic verification */
}Memp_p;

#endif /* MEMP_PRIVATE_H */
