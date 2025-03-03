/*
 * @Author: LeiJiulong
 * @Date: 2025-03-03 09:27:55
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-03-03 09:44:26
 * @Description: 夹具测试
 */

// 夹具生命周期 构造夹具对象 → SetUp() → 测试代码 → TearDown() → 析构夹具对象

#include "TestOBJ.hpp"
#include <gtest/gtest.h>

using namespace TestOBJ;

class FixtureTest : public ::testing::Test
{
protected:
    //  测试开始前执行一次
    void SetUp() override
    {
        // 初始化夹具
        obj = OBJ01("obj1", true);
    }
    // 完成测试后执行一次
    void TearDown() override
    {
        // 清理夹具
        std::cout << "TearDown()" << std::endl;
    }

    OBJ01 obj;
    
};

TEST_F(FixtureTest, Test01)
{
    // EXPECT_* 失败可以继续执行
    EXPECT_EQ(obj.name(), "obj");
    // ASSERT_* 失败会终止测试
    ASSERT_TRUE(obj.flag());
}

/**
必须使用 public 继承：class MyFixture : public testing::Test
避免在 SetUp 中抛出异常：使用 ASSERT_* 会直接终止测试
夹具成员变量自动重置：每个 TEST_F 都会创建新的夹具实例
优先使用 TEST_F 而非全局变量：保证测试隔离性
 */

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
