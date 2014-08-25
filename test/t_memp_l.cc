#include "pub.h"
#include "memp_l.h"
#include "gtest/gtest.h"

F_RET T_PUB_CHK(T_UINT32 s, T_UINT32 d, T_UINT32 ret)
{
    F_NCHK_RET(s, d, ret);
    F_CHK_RET(s, d, ret);

    return T_OK;
}

F_RET T_PUB_NULL(T_UINT32 *s, T_UINT32 ret)
{
    PN_RET(s, ret);
    return T_OK;
}

TEST(G_TEST, GENERAL_01)
{
    T_UINT32 s = 0;
    T_UINT32 d = 0;
    T_UINT32 magic = 0xFFFFFFFE;
    T_UINT32 ret = 0;

    ret = T_PUB_CHK(s, d, magic);
    ASSERT_EQ(ret, magic);
    ret = T_PUB_CHK(s, d + 1, magic + 1);
    ASSERT_EQ(ret, magic + 1);
}

TEST(G_TEST, GENERAL_02)
{
    T_UINT32 *s = T_NULL;
    T_UINT32 magic = 0xFFFFFFFE;
    T_UINT32 ret = 0;

    ret = T_PUB_NULL(s, magic);
    ASSERT_EQ(ret, magic);
}

/*

extern F_RET memp_l_create_list(Memp_l **list);
extern F_RET memp_l_create_node(Memp_n **node);
extern F_RET memp_l_create_mem_list(Memp_n *node, Memp_mem_l **list);
extern F_RET memp_l_create_mem_node(Memp_mem_n **node, T_UINT32 size, T_UINT32 tag);
extern F_RET memp_l_insert_list(Memp_l *list, Memp_n *node);
extern F_RET memp_l_insert_mem_list(Memp_mem_l *list, Memp_mem_n *node);
extern F_RET memp_l_remove_list(Memp_l *list, Memp_n *node);
extern F_RET memp_l_remove_mem_list(Memp_mem_l *list, Memp_mem_n *node);
*/

TEST(MEMP_L, MEMP_L_001)
{
    T_VOID *t_void = T_NULL;
    Memp_l *list = T_NULL;
    Memp_n *node = T_NULL;
    Memp_mem_l *mem_list = T_NULL;
    Memp_mem_n *mem_node = T_NULL;
    T_UINT32 ret = NULL_UINT32;
    ret = memp_l_create_list(&list);
    /* change to assert */
    EXPECT_EQ(ret, T_OK);
    EXPECT_NE(list, t_void);
    EXPECT_EQ(list->size, 0);
    EXPECT_EQ(list->head, t_void);

    ret = memp_l_create_node(&node);
    EXPECT_EQ(ret, T_OK);
    EXPECT_NE(node, t_void);
    EXPECT_EQ(node->next, t_void);
    EXPECT_EQ(node->list, t_void);

    ret = memp_l_insert_list(list, node);
    EXPECT_EQ(ret, T_OK);
    EXPECT_EQ(list->size, 1);
    EXPECT_EQ(list->head, node);

    ret = memp_l_create_mem_list(node, &mem_list);
    EXPECT_EQ(ret, T_OK);
    EXPECT_NE(mem_list, t_void);
    EXPECT_EQ(mem_list->size, 0);
    EXPECT_EQ(mem_list->head, t_void);

    EXPECT_NE(list->head->list, t_void);
    EXPECT_EQ(list->head->list->head, t_void);
    EXPECT_EQ(list->head->list->size, 0);

    ret = memp_l_create_mem_node(&mem_node, 10, 1);
    EXPECT_EQ(ret, T_OK);
    EXPECT_NE(mem_node, t_void);
    EXPECT_EQ(mem_node->size, 10);
    EXPECT_EQ(mem_node->tag, 1);
    EXPECT_EQ(mem_node->next, t_void);
}

TEST(MEMP_L, MEMP_L_002)
{
    Memp_l *list = T_NULL;
    Memp_n *node = T_NULL;

    Memp_mem_l *mem_list1 = T_NULL;

    Memp_mem_n *mem_node1 = T_NULL;
    Memp_mem_n *mem_node2 = T_NULL;
    Memp_mem_n *mem_node3 = T_NULL;

    T_UINT32 ret = NULL_UINT32;

    ret = memp_l_create_list(&list);
    EXPECT_EQ(ret, T_OK);

    ret = memp_l_create_node(&node);
    EXPECT_EQ(ret, T_OK);

    ret = memp_l_create_mem_list(node, &mem_list1);
    EXPECT_EQ(ret, T_OK);

    ret = memp_l_create_mem_node(&mem_node1, 11, 1);
    EXPECT_EQ(ret, T_OK);
    ASSERT_TRUE(mem_node1 != T_NULL);
    ASSERT_EQ(mem_node1->size, 11);
    ASSERT_EQ(mem_node1->tag, 1);

    ret = memp_l_create_mem_node(&mem_node2, 12, 1);
    EXPECT_EQ(ret, T_OK);
    ASSERT_TRUE(mem_node2 != T_NULL);
    ASSERT_TRUE(mem_node2 != T_NULL);
    ASSERT_EQ(mem_node2->size, 12);

    ret = memp_l_create_mem_node(&mem_node3, 13, 1);
    EXPECT_EQ(ret, T_OK);
    ASSERT_TRUE(mem_node3 != T_NULL);
    ASSERT_TRUE(mem_node3 != T_NULL);
    ASSERT_EQ(mem_node3->size, 13);

    ret = memp_l_insert_list(list, node);
    EXPECT_EQ(ret, T_OK);
    ASSERT_EQ(list->head, node);
    ASSERT_EQ(list->size, 1);

    ret = memp_l_insert_mem_list(mem_list1, mem_node1);
    EXPECT_EQ(ret, T_OK);
    ASSERT_EQ(mem_list1->head, mem_node1);
    ASSERT_EQ(mem_list1->size, 1);
    ASSERT_TRUE(mem_list1->head->next == T_NULL);

    ret = memp_l_insert_mem_list(mem_list1, mem_node2);
    EXPECT_EQ(ret, T_OK);
    ASSERT_EQ(mem_list1->head, mem_node2);
    ASSERT_EQ(mem_list1->head->next, mem_node1);
    ASSERT_EQ(mem_list1->size, 2);

    ret = memp_l_insert_mem_list(mem_list1, mem_node3);
    EXPECT_EQ(ret, T_OK);
    ASSERT_EQ(mem_list1->head, mem_node3);
    ASSERT_EQ(mem_list1->size, 3);
    ASSERT_EQ(mem_list1->head->next, mem_node2);
    ASSERT_EQ(mem_list1->head->next->next, mem_node1);

    ret = memp_l_remove_mem_list(mem_list1, mem_node3);
    EXPECT_EQ(ret, T_OK);
    ASSERT_EQ(mem_list1->head->next, mem_node1);
    ASSERT_TRUE(mem_list1->head->next->next == T_NULL);
    ASSERT_EQ(mem_list1->size, 2);
}
