#include "footest.hpp"

int one();

TEST_F(FooTest, getOne)
{
    ASSERT_EQ(one(), 1);
}
