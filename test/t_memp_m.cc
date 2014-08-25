#include "pub.h"
#include "memp_l.h"
#include "memp_v.h"
#include "gtest/gtest.h"

typedef struct
{
    int  a;
    int *p;
    char s[10];
}Temp_Doller;


TEST(MEMP_C, MEMP_C_001)
{
    Temp_Doller td = {0};
    Temp_Doller *p = T_NULL;
    p = F_GETSP(&(td.s), Temp_Doller, s);

    ASSERT_TRUE(p == &td);
}

TEST(MEMP_C, MEMP_C_002)
{
    Memp_n *node  = T_NULL;
    Memp_n *tmp   = T_NULL;
    Memp   *memp = T_NULL;
    T_UINT32 ret = NULL_UINT32;
    ret = memp_l_create_list(&g_memp_list);
    ASSERT_EQ(ret, T_OK);

    ret = memp_l_create_memp(g_memp_list, &node);
    ASSERT_EQ(ret, T_OK);

    memp = &(node->memp);

    tmp = F_GETSP(memp, Memp_n, memp);
    ASSERT_TRUE(tmp == node);
}
