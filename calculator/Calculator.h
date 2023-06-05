#pragma once
#include <string>
#include <algorithm>
#include <exception>
#include <stdexcept>
#include <regex>

enum class Cause : uint8_t
{
	nonOperator = 0,
	onlyOneNumber
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
	T Execute(std::string action) const;
private:
	T AddNumbers(const std::pair<T, T>& values) const;
	T SubstractNumbers(const std::pair<T, T>& values) const;
	T Divide(const std::pair<T, T>& values) const;
	T Multiply(const std::pair<T, T>& values) const;
	bool IsStringCorrectNumber(std::string& string) const;
	std::pair<T, T> StringToT(std::string& left, std::string& right) const;
};

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
	std::remove_if(string.begin(), string.end(), isspace);
	std::regex regexCheck("[+-]?([0-9]*[.])?[0-9]+");
	bool m = false;
	std::regex_constants::match_flag_type flags = std::regex_constants::match_default;
	std::regex_search(string.begin(), string.end(), regexCheck, flags);
	return !m;
}

template<typename T>
inline std::pair<T, T> Calculator<T>::StringToT(std::string& left, std::string& right) const
{
	bool leftCheck = false;
	bool rightCheck = false;
	T leftValue = 0;
	T rightValue = 0;
	auto pos = std::find(left.begin(), left.begin(), '.');
	if (pos != left.end())
	{
		leftValue = std::stof(left);
		leftCheck = true;
	}
	pos = std::find(right.begin(), right.begin(), '.');
	if (pos != right.end())
	{
		rightValue = std::stof(right);
		rightCheck = true;
	}
	if (leftCheck == false)
	{
		leftValue = std::stoi(left);
	}
	if (rightCheck == false)
	{
		rightValue = std::stoi(right);
	}
	return std::pair<T, T>(leftValue, rightValue);
}

template<typename T>
inline T Calculator<T>::Execute(std::string action) const
{
	std::string operators = "+-/*";
	auto it = std::find_first_of(action.begin(), action.end(), operators.begin(), operators.end());
	if (it != action.end() && it != action.begin() && it != (action.end() - 1))
	{
		int64_t pos = std::distance(action.begin(), it);
		std::string left = action.substr(0, pos);
		std::string right = action.substr(pos + 1, action.size() - (pos + 1));
		
		if (!IsStringCorrectNumber(left) || !IsStringCorrectNumber(right))
		{
			throw(InvalidInput(Cause::onlyOneNumber));
		}

		if (*it == '+')
		{
			return AddNumbers(StringToT(left, right));
		}
		else if (*it == '-')
		{
			return SubstractNumbers(StringToT(left, right));
		}
		else if (*it == '*')
		{
			return Multiply(StringToT(left, right));
		}
		else if (*it == '/')
		{
			return Divide(StringToT(left, right));
		}
	}
	else if (it == action.end())
	{
		throw(InvalidInput(Cause::nonOperator));
	}
	else
	{
		throw(InvalidInput(Cause::onlyOneNumber));
	}
}