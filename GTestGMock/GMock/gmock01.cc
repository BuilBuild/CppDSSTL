/*
 * @Author: LeiJiulong
 * @Date: 2025-03-03 10:14:11
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-03-03 11:48:06
 * @Description: 
 */
#include "TestOBJ.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>


using namespace MockOBJ;
using ::testing::_;


class MockUserService : public UserService 
{
public:
    // 参数列表：返回值类型, (参数列表), 修饰符（可选）
    MOCK_METHOD(bool, Login, (const std::string&, const std::string&), (override));
    MOCK_METHOD(int, GetUserAge, (const std::string&), (override));
    
};

TEST(UserTest, LoginTest) {
    MockUserService mock_service;

    // 预期调用 Login 方法，参数为 ("admin", "123456")，返回 true，且至少调用一次
    EXPECT_CALL(mock_service, Login(_, _))
        .Times(testing::AtLeast(2))
        .WillOnce(testing::Return(true))
        .WillOnce(testing::Return(true));
    // 测试
    EXPECT_TRUE([&]{return mock_service.Login("admin", "123456");}());
    EXPECT_TRUE([&]{return mock_service.Login("admin", "654321");}());

}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}