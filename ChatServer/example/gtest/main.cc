#include <iostream>
#include <gtest/gtest.h>

int Add(int num1, int num2)
{
    return num1 + num2;
}

TEST(测试名称1, 用例名称1)
{
    ASSERT_EQ(Add(1, 1), 2);
    ASSERT_LT(Add(1, 1), 3);
}

TEST(测试名称2, 用例名称2)
{
    std::string str = "Hello";
    EXPECT_EQ(str, "hELLO");
    printf("断言失败后的打印\n");
    EXPECT_EQ(str, "Hello");
}


int main(int argc, char *argv[])
{
    // 初始化
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}