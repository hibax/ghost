#include "gtest/gtest.h"
#include "Factory.h"


TEST(Factory, simpleTest) {

    Factory myFactory(0, OWNER::ME, 3, 0);

    int expectedProduction(3);

    EXPECT_EQ(expectedProduction, myFactory.getProduction());
}
