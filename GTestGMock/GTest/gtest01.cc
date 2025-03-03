/*
 * @Author: LeiJiulong
 * @Date: 2025-03-03 09:06:16
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-03-03 09:23:45
 * @Description:
 */
#include <gtest/gtest.h>

int Add(int a, int b) { return a + b; }

TEST(AddTest, HandlePositive)
{
    EXPECT_EQ(Add(1, 1), 2);
    EXPECT_EQ(Add(2, 3), 5);
    EXPECT_EQ(Add(5, 5), 10);
}

TEST(AddTest, HandleNegative)
{
    EXPECT_EQ(Add(2, 3), 5); // 期望值等于
    ASSERT_NE(Add(0, 0), 1); // 断言不等于（失败会终止当前测试）
}

// 测试夹具（共享配置）
class MyFixture : public ::testing::Test
{
protected:
    void SetUp() override { /* 初始化代码 */ }
    void TearDown() override { /* 清理代码 */ }
};

/**
EXPECT_*： 非致命断言，测试继续执行
EXPECT_EQ, EXPECT_TRUE, EXPECT_THROW
ASSERT_*： 致命断言，失败立即终止当前测试
ASSERT_EQ, ASSERT_FALSE, ASSERT_NO_THROW
 */
TEST_F(MyFixture, Test1)
{
    ASSERT_TRUE(true);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}