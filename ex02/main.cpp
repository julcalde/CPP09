/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 16:53:07 by julcalde          #+#    #+#             */
/*   Updated: 2026/03/16 17:37:20 by julcalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <iostream>
#include <vector>
#include <list>
#include <cstdlib>
#include <sstream>

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		std::cerr << "Error: No input provided" << std::endl;
		return (1);
	}
	std::vector<int> vec;
	for (int i = 1; i < argc; ++i)
	{
		std::istringstream iss(argv[i]);
		int num;
		if (!(iss >> num) || num < 0)
		{
			std::cerr << "Error: invalid input: " << argv[i] << std::endl;
			return (1);
		}
		vec.push_back(num);
	}
	std::vector<int> vecCopy(vec); // placeholder for the list version of the input

	// ...
	
	return (0);
}