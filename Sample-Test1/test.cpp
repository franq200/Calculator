#include "gtest/gtest.h"
#include "..\calculator\Calculator.h"

TEST(CalculatorTests, Given1And3__WhenAddNumbersFunctionIsCalled__ThenItShouldReturn4)
{
	Calculator<int> calculator;
	EXPECT_EQ(calculator.Execute("3+1"), 4);
}

TEST(CalculatorTests, Given2_1And3_44__WhenAddNumbersFunctionIsCalled__ThenItShouldReturn5_54)
{
	Calculator<float> calculator;
	EXPECT_NEAR(5.54, calculator.Execute("2.1+3.44"), 0.01);
}

TEST(CalculatorTests, Given3And1__WhenSubstractNumbersFunctionIsCalled__ThenItShouldReturn2)
{
	Calculator<int> calculator;
	EXPECT_NEAR(2, calculator.Execute("3-1"), 0.01);
}