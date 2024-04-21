//
// Created by pjsmi 4/21/2024.
//
#include <iostream>
#include "gtest/gtest.h"

// The fixture for testing class Foo.
class FooTest : public ::testing::Test {
protected:
// You can remove any or all of the following functions if its body
// is empty.
    FooTest() {
// You can do set-up work for each test here.
    }
    virtual ~FooTest() {
// You can do clean-up work that doesn’t throw exceptions here.
    }
// If the constructor and destructor are not enough for setting up
// and cleaning up each test, you can define the following methods:
    virtual void SetUp() {
// Code here will be called immediately after the constructor (right
// before each test).
    }
    virtual void TearDown() {
// Code here will be called immediately after each test (right
// before the destructor).
    }
// Objects declared here can be used by all tests in the test case for Foo.
    std::string s1 = "test right";
    std::string s2 = "test wrong";
};

TEST(general, TESTSIMPLE) {
/** test the local strings **/
    std::string s3("test");
    std::string s4("test");
    ASSERT_EQ(s3, s4) << s3
                      << " and "
                      << s4
                      << " should match!";
}
TEST_F(FooTest, TESTFIXTURE) {
/** test the fixture strings **/
    ASSERT_EQ(s1, s2) << "These should match!";
}
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}




