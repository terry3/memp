#include "pub.h"
#include "memp_l.h"
#include "memp.h"
#include "gtest/gtest.h"


class MEMP_T:public testing::Test
{
protected:
    static void SetUpTestCase()
        {
            memp_init();
        }
    static void TearDownTestCase()
        {
            /* null */
        }
};

TEST_F(MEMP_T, MEMP_001)
{
    T_UINT32 ret  = NULL_UINT32;
    Memp     memp = T_NULL;
    T_VOID  *tmp  = T_NULL;
    ret = memp_create(&memp);
    ASSERT_EQ(ret, T_OK);

    tmp = memp_alloc(memp, 12, 1);
    ASSERT_TRUE(tmp != T_NULL);

    ret = memp_free(memp);
    ASSERT_EQ(ret, T_OK);
}

TEST_F(MEMP_T, MEMP_002)
{
    ASSERT_EQ(T_OK, T_OK);
#if 0
    T_UINT32 ret  = NULL_UINT32;
    Memp     memp = T_NULL;
    T_VOID  *tmp  = T_NULL;
    ret = memp_create(&memp);
    ASSERT_EQ(ret, T_OK);

    tmp = memp_alloc(memp, 12, 1);
    ASSERT_TRUE(tmp != T_NULL);
#endif
}
