#pragma once
#include <string>
#include <algorithm>
#include <exception>
#include <stdexcept>
#include <regex>
#include <map>
#include <functional>

enum class Cause : uint8_t
{
	nonOperator = 0,
	onlyOneNumber,
	wrongAmountOfBrackets,
	wrongAmountOfOperators
};

enum class Side : uint8_t
{
	left,
	right
};

struct InvalidInput : std::exception
{
public:
	InvalidInput(Cause cause) : cause(cause) {}
	Cause cause = Cause::nonOperator;
private:
};

template <typename T>
class Calculator
{
public:
	T Execute(const std::string& action) const;
private:
	bool IsCorrectBracketsExpression(const std::string& action) const;
	T ExecuteWithBrackets(const std::string& action) const;
	T ExecuteWithoutBrackets(const std::string& action) const;
	std::pair<char, int> GetOperator(const std::string& action) const;
	Side SideOfBracket(const int open, const int close, const std::string& action) const;
	T AddNumbers(const std::pair<T, T>& values) const;
	T SubstractNumbers(const std::pair<T, T>& values) const;
	T Divide(const std::pair<T, T>& values) const;
	T Multiply(const std::pair<T, T>& values) const;
	bool IsStringCorrectNumber(std::string& string) const;
	T StringToT(std::string string) const;
	std::map<char, std::function<T(const Calculator&, const std::pair<T, T>&)>> m_operatorsMap = {
		{'+', &Calculator::AddNumbers}, {'-', &Calculator::SubstractNumbers}, {'*', &Calculator::Multiply}, {'/', &Calculator::Divide} };
};

template<typename T>
inline std::pair<char, int> Calculator<T>::GetOperator(const std::string& action) const
{
	auto it = std::find_first_of(action.begin(), action.end(), m_operatorsMap.begin(), m_operatorsMap.end(), [](const auto& el1, const auto& el2) {return el1 == el2.first; });

	if (it != action.end() && it != action.begin() && it != (action.end() - 1))
	{
		return { *it, std::distance(action.begin(), it) };
	}
	else if (it == action.end())
	{
		throw(InvalidInput(Cause::nonOperator));
	}
	throw(InvalidInput(Cause::onlyOneNumber));
}

template<typename T>
inline Side Calculator<T>::SideOfBracket(const int open, const int close, const std::string& action) const
{
	if (close == action.size() - 1)
	{
		return Side::right;
	}
	return Side::left;
}

template<typename T>
inline T Calculator<T>::AddNumbers(const std::pair<T, T>& values)  const
{
	return values.first + values.second;
}

template<typename T>
inline T Calculator<T>::SubstractNumbers(const std::pair<T, T>& values) const
{
	return values.first - values.second;
}

template<typename T>
inline T Calculator<T>::Divide(const std::pair<T, T>& values) const
{
	return values.first / values.second;
}

template<typename T>
inline T Calculator<T>::Multiply(const std::pair<T, T>& values) const
{
	return values.first * values.second;
}

template<typename T>
inline bool Calculator<T>::IsStringCorrectNumber(std::string& string) const
{
	string.erase(std::remove_if(string.begin(), string.end(), isspace), string.end());
	std::regex regexCheck("[+-]?([0-9]*[.])?[0-9]+");
	return std::regex_search(string.begin(), string.end(), regexCheck);
}

template<typename T>
inline T Calculator<T>::StringToT(std::string string) const
{
	T leftValue = 0;
	auto pos = std::find(string.begin(), string.end(), '.');
	if (pos != string.end())
	{
		return std::stof(string);
	}
	return std::stoi(string);
}

template<typename T>
inline T Calculator<T>::Execute(const std::string& action) const
{
	if (IsCorrectBracketsExpression(action))
	{
		return ExecuteWithBrackets(action);
	}
	return ExecuteWithoutBrackets(action);
}

template<typename T>
inline bool Calculator<T>::IsCorrectBracketsExpression(const std::string& action) const
{
	int openAmount = std::count_if(action.begin(), action.end(), [](const auto& el) {return el == '('; });
	int closeAmount = std::count_if(action.begin(), action.end(), [](const auto& el) {return el == ')'; });
	if (openAmount >= 2 || closeAmount >= 2)
	{
		throw(InvalidInput(Cause::wrongAmountOfBrackets));
	}
	else if (openAmount != closeAmount)
	{
		throw(InvalidInput(Cause::wrongAmountOfBrackets));
	}
	return openAmount == 1 && closeAmount == 1;
}

template<typename T>
inline T Calculator<T>::ExecuteWithBrackets(const std::string& action) const
{
	if (std::count_if(action.begin(), action.end(), [](const auto& el) {return el == '+' || el == '-' || el == '*' || el == '/'; }) != 2)
	{
		throw(InvalidInput(Cause::wrongAmountOfOperators));
	}
	int closePos = action.find(')', 0);
	int openPos = action.find('(', 0);
	std::string expression = action.substr(openPos + 1, closePos - (openPos + 1));
	if (!IsStringCorrectNumber(expression))
	{
		throw(InvalidInput(Cause::onlyOneNumber));
	}
	T value = Execute(action.substr(openPos + 1, closePos - (openPos + 1)));
	Side bracketSide = SideOfBracket(openPos, closePos, action);
	std::pair<T, T> values;
	if (bracketSide == Side::left)
	{
		values.first = value;
		values.second = StringToT(action.substr(closePos + 2));
	}
	else if (bracketSide == Side::right)
	{
		values.first = StringToT(action.substr(0, openPos - 1));
		values.second = value;
	}
	auto [mathOperator, pos] = bracketSide == Side::right ? GetOperator(action) : GetOperator(action.substr(closePos));
	return m_operatorsMap.at(mathOperator)(*this, values);
}

template<typename T>
inline T Calculator<T>::ExecuteWithoutBrackets(const std::string& action) const
{
	auto [mathOperator, pos] = GetOperator(action);
	std::string left = action.substr(0, pos);
	std::string right = action.substr(pos + 1, action.size() - (pos + 1));

	if (!IsStringCorrectNumber(left) || !IsStringCorrectNumber(right))
	{
		throw(InvalidInput(Cause::onlyOneNumber));
	}
	std::pair<T, T> pair(StringToT(left), StringToT(right));
	return m_operatorsMap.at(mathOperator)(*this, pair);
	return T();
}
