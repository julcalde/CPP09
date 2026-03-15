/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 16:52:59 by julcalde          #+#    #+#             */
/*   Updated: 2026/03/15 15:19:26 by julcalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <iostream>

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		std::cerr << " Error: usage: " << argv[0] << " \"expression\"" << std::endl;
		return (1);
	}
	int result;
	if (!RPN::evaluate(argv[1], result))
	{
		std::cerr << "Error: invalid expression." << std::endl;
		return (1);
	}
	std::cout << result << std::endl;
	return (0);
}
