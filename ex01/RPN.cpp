/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 16:53:02 by julcalde          #+#    #+#             */
/*   Updated: 2026/03/15 15:51:51 by julcalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <iostream>
#include <sstream>
#include <cctype>

RPN::RPN() {}

RPN::~RPN() {}

RPN::RPN(const RPN&) {}

RPN& RPN::operator=(const RPN&)
{
	return (*this);
}

bool RPN::evaluate(const std::string& expr, int& result)
{
	std::stack<int> intStack;
	std::istringstream iss(expr);
	std::string token;

	while (iss >> token)
	{
		if (token.size() == 1 && std::isdigit(token[0]))
		{
			int n = token[0] - '0';
			intStack.push(n);
			// std::cout << "Pushed: " << n << std::endl; // Debugging output
		}
		else if (token.size() == 1 && (token[0] == '+' || token[0] == '-' || token[0] == '*' || token[0] == '/'))
		{
			if (intStack.size() < 2)
			{
				std::cerr << "Error: not enough operands for operator '" << token[0] << "'." << std::endl;
				return (false);
			}
			int b = intStack.top();
			// std::cout << "Popped b: " << b << std::endl; // Debugging output
			intStack.pop();
			int a = intStack.top();
			// std::cout << "Popped a: " << a << std::endl; // Debugging output
			intStack.pop();
			if (token[0] == '+')
			{
				
				// std::cout << "Applying operator: " << a << " + " << b << std::endl; // Debugging output
				intStack.push(a + b);
			}
			else if (token[0] == '-')
			{
				// std::cout << "Applying operator: " << a << " - " << b << std::endl; // Debugging output
				intStack.push(a - b);
			}
			else if (token[0] == '*')
			{
				// std::cout << "Applying operator: " << a << " * " << b << std::endl; // Debugging output
				intStack.push(a * b);
			}
			else
			{
				// std::cout << "Applying operator: " << a << " / " << b << std::endl; // Debugging output
				if (b == 0)
				{
					std::cerr << "Error: division by zero." << std::endl;
					return (false);
				}
				intStack.push(a / b);
			}
		}
		else
		{
			std::cerr << "Error: invalid operator '" << token[0] << "'." << std::endl;
			return (false);
		}
	}
	if (intStack.size() != 1)
	{
		std::cerr << "Error: invalid expression, expected exactly one result but got " << intStack.size() << "." << std::endl;
		return (false);
	}
	result = intStack.top();
	return (true);
}