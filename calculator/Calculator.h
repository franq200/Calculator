#pragma once
#include <string>
#include <iostream>


template <typename T>
class Calculator
{
public:
	T AddNumbers(std::string left, std::string right);
	T SubstractNumbers(std::string left, std::string right);
	T Execute(std::string action);
private:
};

template<typename T>
inline T Calculator<T>::AddNumbers(std::string left, std::string right)
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
	return leftValue + rightValue;
}

template<typename T>
inline T Calculator<T>::SubstractNumbers(std::string left, std::string right)
{
	return stoi(left) - stoi(right);
}

template<typename T>
inline T Calculator<T>::Execute(std::string action)
{
	auto it = std::find(action.begin(), action.end(), '+');
	if (it != action.end())
	{
		int64_t pos = std::distance(action.begin(), it);
		std::string left = action.substr(0, pos);
		std::string right = action.substr(pos + 1, action.size() - (pos + 1));
		return AddNumbers(left, right);
	}
	it = std::find(action.begin(), action.end(), '-');
	if (it != action.end())
	{
		int64_t pos = std::distance(action.begin(), it);
		std::string left = action.substr(0, pos);
		std::string right = action.substr(pos + 1, action.size() - (pos + 1));
		return SubstractNumbers(left, right);
	}
}