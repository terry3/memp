#ifndef MEMP_L_H
#define MEMP_L_H

#include "memp.h"

#ifdef __cplusplus
extern "C"{
#endif
/* memp node */
typedef struct _Memp_nln
{
    T_UINT32  size;
    T_UINT32  tag;
    struct _Memp_nln *next;
    T_UINT8   p[0];
}Memp_mem_n;

/* memp node list */
typedef struct
{
    T_UINT32     size;
    Memp_mem_n  *head;
}Memp_mem_l;

/* memp list node */
typedef struct _Memp_ln
{
    Memp_mem_l      *list;
    struct _Memp_ln *next;
    Memp             memp;
}Memp_n;

/* memp list */
typedef struct
{
    T_UINT32  size;
    Memp_n  *head;
}Memp_l;

/* function declare */

extern F_RET memp_l_create_list(Memp_l **list);
extern F_RET memp_l_create_node(Memp_n **node);
extern F_RET memp_l_create_mem_list(Memp_n *node, Memp_mem_l **list);
extern F_RET memp_l_create_mem_node(Memp_mem_n **node, T_UINT32 size, T_UINT32 tag);
extern F_RET memp_l_insert_list(Memp_l *list, Memp_n *node);
extern F_RET memp_l_insert_mem_list(Memp_mem_l *list, Memp_mem_n *node);
extern F_RET memp_l_remove_list(Memp_l *list, Memp_n *node);
extern F_RET memp_l_remove_mem_list(Memp_mem_l *list, Memp_mem_n *node);
extern F_RET memp_l_create_memp(Memp_l *list, Memp_n **node);
extern F_RET memp_l_create_insert_memp_mem_list(Memp_mem_l *list, T_UINT32 size, T_UINT32 tag);
extern F_RET memp_l_remove_mem_list_all(Memp_mem_l *list);

#ifdef __cplusplus
}
#endif
#endif /* MEMP_L_H */
