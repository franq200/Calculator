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
	EXPECT_EQ(2, calculator.Execute("3-1"));
}

TEST(CalculatorTests, Given3WithSpaceBeforeItAnd1__WhenSubstractNumbersFunctionIsCalled__ThenItShouldReturn2)
{
	Calculator<int> calculator;
	EXPECT_EQ(2, calculator.Execute(" 3-1"));
}

TEST(CalculatorTests, Given4And2__WhenDivideFunctionIsCalled__ThenItShouldReturn2)
{
	Calculator<int> calculator;
	EXPECT_EQ(2, calculator.Execute("4/2"));
}

TEST(CalculatorTests, Given4_2And2_1__WhenDivideFunctionIsCalled__ThenItShouldReturn2)
{
	Calculator<float> calculator;
	EXPECT_NEAR(2, calculator.Execute("4.2/2.1"), 0.01);
}

TEST(CalculatorTests, Given4_2And2__WhenDivideFunctionIsCalled__ThenItShouldReturn2_1)
{
	Calculator<float> calculator;
	EXPECT_NEAR(2.2, calculator.Execute("4.4/2"), 0.01);
}

TEST(CalculatorTests, Given4And2__WhenMultiplyFunctionIsCalled__ThenItShouldReturn8)
{
	Calculator<int> calculator;
	EXPECT_EQ(8, calculator.Execute("4*2"));
}

TEST(CalculatorTests, Given4_2And2_1__WhenMultiplyFunctionIsCalled__ThenItShouldReturn9_24)
{
	Calculator<float> calculator;
	EXPECT_NEAR(9.24, calculator.Execute("4.4*2.1"), 0.01);
}

TEST(CalculatorTests, Given4_2And2__WhenMultiplyFunctionIsCalled__ThenItShouldReturn8_8)
{
	Calculator<float> calculator;
	EXPECT_NEAR(8.8, calculator.Execute("4.4*2"), 0.01);
}

TEST(CalculatorTests, Given4And2_2__WhenMultiplyFunctionIsCalled__ThenItShouldReturn8_8)
{
	Calculator<float> calculator;
	EXPECT_NEAR(8.8, calculator.Execute("4*2.2"), 0.01);
}

TEST(CalculatorTests, GivenInputWithoutOperator__WhenExecuteFunctionIsCalled__ThenItShouldThrowInvalidInputWithCauseNonOperator)
{
	Calculator<int> calculator;
	try
	{
		calculator.Execute("31.323");
	}
	catch (const InvalidInput& e)
	{
		EXPECT_EQ(e.cause, Cause::nonOperator);
	}
}

TEST(CalculatorTests, GivenInputWithNothingBehindOperator__WhenExecuteFunctionIsCalled__ThenItShouldThrowInvalidInputWithCauseOnlyOneNumber)
{
	Calculator<int> calculator;
	try
	{
		calculator.Execute("31+");
	}
	catch (const InvalidInput& e)
	{
		EXPECT_EQ(e.cause, Cause::onlyOneNumber);
	}
}

TEST(CalculatorTests, GivenInputWithNothingBeforeOperator__WhenExecuteFunctionIsCalled__ThenItShouldThrowInvalidInputWithCauseOnlyOneNumber)
{
	Calculator<int> calculator;
	try
	{
		calculator.Execute("+31");
	}
	catch (const InvalidInput& e)
	{
		EXPECT_EQ(e.cause, Cause::onlyOneNumber);
	}
}

TEST(CalculatorTests, GivenInputWithNothingBeforeNumber__WhenExecuteFunctionIsCalled__ThenItShouldThrowInvalidInputWithCauseNonOperator)
{
	Calculator<int> calculator;
	try
	{
		calculator.Execute(" 31");
	}
	catch (const InvalidInput& e)
	{
		EXPECT_EQ(e.cause, Cause::nonOperator);
	}
}

TEST(CalculatorTests, GivenInputWithNothingAfterNumber__WhenExecuteFunctionIsCalled__ThenItShouldThrowInvalidInputWithCauseNonOperator)
{
	Calculator<int> calculator;
	try
	{
		calculator.Execute("31 ");
	}
	catch (const InvalidInput& e)
	{
		EXPECT_EQ(e.cause, Cause::nonOperator);
	}
}

TEST(CalculatorTests, GivenInputWithTwoOperatorsBeforeNumber__WhenExecuteFunctionIsCalled__ThenItShouldThrowInvalidInputWithCauseOnlyOneNumber)
{
	Calculator<int> calculator;
	try
	{
		calculator.Execute("++31");
	}
	catch (const InvalidInput& e)
	{
		EXPECT_EQ(e.cause, Cause::onlyOneNumber);
	}
}

TEST(CalculatorTests, GivenInputWithTwoOperatorsBehindNumber__WhenExecuteFunctionIsCalled__ThenItShouldThrowInvalidInputWithCauseOnlyOneNumber)
{
	Calculator<int> calculator;
	try
	{
		calculator.Execute("31++");
	}
	catch (const InvalidInput& e)
	{
		EXPECT_EQ(e.cause, Cause::onlyOneNumber);
	}
}

TEST(CalculatorTests, GivenInputWithSpaceBeforeOperators__WhenExecuteFunctionIsCalled__ThenItShouldThrowInvalidInputWithCauseOnlyOneNumber)
{
	Calculator<int> calculator;
	try
	{
		calculator.Execute(" +31");
	}
	catch (const InvalidInput& e)
	{
		EXPECT_EQ(e.cause, Cause::onlyOneNumber);
	}
}

TEST(CalculatorTests, GivenInputWithTwoPointsBetweenOneNumber__WhenExecuteFunctionIsCalled__ThenItShouldThrowInvalidInputWithCauseOnlyOneNumber)
{
	Calculator<int> calculator;
	try
	{
		calculator.Execute("1..2+31");
	}
	catch (const InvalidInput& e)
	{
		EXPECT_EQ(e.cause, Cause::onlyOneNumber);
	}
}

TEST(CalculatorTests, Given4Minus3AllMultipledBy5__WhenExecuteFunctionIsCalled__ThenItShouldReturn5)
{
	Calculator<int> calculator;
	EXPECT_EQ(5, calculator.Execute("(4-3)*5"));
}

TEST(CalculatorTests, Given4Minus3AllMultipledBy5__WhenExecuteFunctionIsCalled__ThenItShouldReturn6)
{
	Calculator<int> calculator;
	EXPECT_EQ(6, calculator.Execute("5+(4-3)"));
}

TEST(CalculatorTests, Given4Minus3AllMultipledBy5__WhenExecuteFunctionIsCalled__ThenItShouldReturn2)
{
	Calculator<int> calculator;
	EXPECT_EQ(2, calculator.Execute("3-(1*1)"));
}

TEST(CalculatorTests, Given2Minus4AllDividedBy4__WhenExecuteFunctionIsCalled__ThenItShouldReturn2)
{
	Calculator<int> calculator;
	EXPECT_EQ(2, calculator.Execute("(2*4)/4"));
}