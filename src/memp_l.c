#include "pub.h"
#include "memp_l.h"

F_RET memp_l_create_list(Memp_l **list)
{
    PN_RET(list, NULL_PTR);

    F_MEM_ALLOC(*list, sizeof(**list), Memp_l);

    (*list)->size = 0;
    (*list)->head = T_NULL;
    return T_OK;
}

F_RET memp_l_create_node(Memp_n **node)
{
    PN_RET(node, NULL_PTR);
    F_MEM_ALLOC(*node, sizeof(**node), Memp_n);

    (*node)->list = T_NULL;
    (*node)->next = T_NULL;
    /* (*node)->memp.alloc = T_NULL; */
    /* (*node)->memp.free  = T_NULL; */

    return T_OK;
}

F_RET memp_l_create_mem_list(Memp_n *node, Memp_mem_l **list)
{
    PN_RET(node, NULL_PTR);
    PN_RET(list, NULL_PTR);

    F_MEM_ALLOC(*list, sizeof(**list), Memp_mem_l);

    PN_RET(*list, NULL_PTR);

    (*list)->size = 0;
    (*list)->head = T_NULL;
    node->list = *list;
    return T_OK;
}

F_RET memp_l_create_mem_node(Memp_mem_n **node, T_UINT32 size, T_UINT32 tag)
{
    PN_RET(node, NULL_PTR);
    F_MEM_ALLOC(*node, sizeof(**node) + size, Memp_mem_n);

    (*node)->size = size;
    (*node)->tag  = tag;
    (*node)->next = T_NULL;

    return T_OK;
}

F_RET memp_l_insert_list(Memp_l *list, Memp_n *node)
{
    Memp_n *head = T_NULL;
    PN_RET(list, NULL_PTR);
    PN_RET(node, NULL_PTR);

    head = list->head;

    /* list is empty */
    if(!head)
    {
        list->head = node;
        list->size++;
        return T_OK;
    }

    /* insert into head */
    node->next = head;
    list->head = node;
    list->size++;
    return T_OK;
}

F_RET memp_l_insert_mem_list(Memp_mem_l *list, Memp_mem_n *node)
{
    Memp_mem_n *head = T_NULL;
    PN_RET(list, NULL_PTR);
    PN_RET(node, NULL_PTR);

    head = list->head;

    /* list is empty */
    if(!head)
    {
        list->head = node;
        list->size++;
        return T_OK;
    }

    /* insert into head */

    node->next = head;
    list->head = node;
    list->size++;
    return T_OK;
}

F_RET memp_l_remove_list(Memp_l *list, Memp_n *node)
{
    Memp_n *head = T_NULL;
    Memp_n *tmp  = T_NULL;
    PN_RET(list, NULL_PTR);
    PN_RET(node, NULL_PTR);

    head = list->head;
    PN_RET(head, NULL_PTR);

    if(head == node)
    {
        tmp = head;
        list->head = head->next;
        F_MEM_FREE(tmp);
        list->size--;
        return T_OK;
    }

    /* find the same node */
    while(head->next != node)
    {
        tmp = head->next;
        head = tmp;
    }
    head->next = tmp->next->next;
    F_MEM_FREE(tmp->next);

    return T_OK;
}

F_RET memp_l_remove_mem_list_all(Memp_mem_l *list)
{
    Memp_mem_n *head = T_NULL;
    Memp_mem_n *tmp = T_NULL;
    PN_RET(list, NULL_PTR);

    /* list size is 0 is ok */
    F_CHK_RET(list->size, 0, T_OK);

    head = list->head;

    /* remove all nodes */
    while (T_NULL != head) {
        tmp = head->next;
        memp_l_remove_mem_list(list, head);
        head = tmp;
    }

    return T_OK;
}

F_RET memp_l_remove_mem_list(Memp_mem_l *list, Memp_mem_n *node)
{
    Memp_mem_n *head = T_NULL;
    Memp_mem_n *tmp  = T_NULL;
    PN_RET(list, NULL_PTR);
    PN_RET(node, NULL_PTR);

    F_CHK_RET(list->size, 0, MEMP_LIST_EMPTY);

    head = list->head;
    tmp  = head;
    PN_RET(head, NULL_PTR);

    if(head == node)
    {
        tmp = head;
        list->head = head->next;
        F_MEM_FREE(tmp);
        list->size--;
        return T_OK;
    }

    /* find the same node */
    while(head->next != node)
    {
        tmp = head->next;
        head = tmp;
    }
    head->next = tmp->next->next;
    F_MEM_FREE(tmp->next);

    list->size--;

    return T_OK;
}

F_RET memp_l_create_memp(Memp_l *list, Memp_n **node)
{
    T_UINT32 ret = NULL_UINT32;
    Memp_mem_l *mem_list = T_NULL;
    PN_RET(node, NULL_PTR);

    do
    {
        ret = memp_l_create_node(node);
        FR_BRK(ret);

        ret = memp_l_create_mem_list(*node, &mem_list);
        FR_BRK(ret);

        ret = memp_l_insert_list(list, *node);
        FR_BRK(ret);
    }while(0);

    F_IFN_OK(ret)
    {
        F_MEM_FREE(*node);
        F_MEM_FREE(mem_list);
        return MEM_ALLOC_FAIL;
    }

    return T_OK;
}

F_RET memp_l_create_insert_memp_mem_list(Memp_mem_l *list, T_UINT32 size, T_UINT32 tag)
{
    Memp_mem_n *node = T_NULL;
    T_UINT32    ret  = NULL_UINT32;
    PN_RET(list, NULL_PTR);
    ret = memp_l_create_mem_node(&node, size, tag);
    FR_RET(ret);

    ret = memp_l_insert_mem_list(list, node);
    FR_RET(ret);

    return T_OK;
}
