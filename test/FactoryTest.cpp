#include "gtest/gtest.h"
#include "Factory.h"


TEST(Factory, simpleTest) {

    Factory myFactory(0, OWNER::ME, 0, 3);

    int expectedProduction(3);

    EXPECT_EQ(expectedProduction, myFactory.getProduction());
}
