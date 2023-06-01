#pragma once
#include <string>
#include <algorithm>
#include <exception>
#include <stdexcept>

enum class Cause : uint8_t
{
	nonOperator = 0,
	onlyOneNumber
};

struct InvalidInput : std::exception
{
public:
	InvalidInput(Cause cause): cause(cause) {}
	Cause cause = Cause::nonOperator;
private:
};

template <typename T>
class Calculator
{
public:
	T Execute(std::string action) const;
private:
	T AddNumbers(std::pair<T, T> values) const;
	T SubstractNumbers(std::pair<T, T> values) const;
	T Divide(std::pair<T, T> values) const;
	T Multiply(std::pair<T, T> values) const;
	std::pair<T, T> StringToInt(std::string& left, std::string& right) const;
};

template<typename T>
inline T Calculator<T>::AddNumbers(std::pair<T, T> values)  const
{
	
	return values.first + values.second;
}

template<typename T>
inline T Calculator<T>::SubstractNumbers(std::pair<T, T> values) const
{
	
	return values.first - values.second;
}

template<typename T>
inline T Calculator<T>::Divide(std::pair<T, T> values) const
{
	
	return values.first / values.second;
}

template<typename T>
inline T Calculator<T>::Multiply(std::pair<T, T> values) const
{
	
	return values.first * values.second;
}

template<typename T>
inline std::pair<T, T> Calculator<T>::StringToInt(std::string& left, std::string& right) const
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
		try
		{
			stoi(left);
			stoi(right);
		}
		catch (const std::invalid_argument&)
		{
			throw(InvalidInput(Cause::onlyOneNumber));
		}
		if (*it == '+')
		{
			return AddNumbers(StringToInt(left, right));
		}
		else if (*it == '-')
		{
			return SubstractNumbers(StringToInt(left, right));
		}
		else if (*it == '*')
		{
			return Multiply(StringToInt(left, right));
		}
		else if (*it == '/')
		{
			return Divide(StringToInt(left, right));
		}
	}
	else if (it == action.end())
	{
		throw(InvalidInput(Cause::nonOperator));
	}
	else if (it == action.begin() || it == (action.end()-1))
	{
		throw(InvalidInput(Cause::onlyOneNumber));
	}
}