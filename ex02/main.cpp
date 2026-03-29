/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 16:53:07 by julcalde          #+#    #+#             */
/*   Updated: 2026/03/29 15:53:08 by julcalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <iostream>
#include <vector>
#include <list>
#include <cstdlib>
#include <sstream>

static void printSequence(const std::string& title, const std::vector<int>& v)
{
	std::cout << title;
	for (size_t i = 0; i < v.size(); ++i)
	{
		std::cout << v[i];
		if (i + 1 < v.size())
			std::cout << ' ';
	}
	std::cout << std::endl;
}

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
	std::vector<int> vecCopy(vec);
	std::list<int> lst(vec.begin(), vec.end());
	
	printSequence("Before: ", vecCopy);

	double start = PmergeMe::getTime();
	PmergeMe::sortVector(vecCopy);
	double end = PmergeMe::getTime();
	double timeVec = end - start;
	
	start = PmergeMe::getTime();
	PmergeMe::sortList(lst);
	end = PmergeMe::getTime();
	double timeLst = end - start;

	printSequence("After: ", vecCopy);
	PmergeMe::printTime("vector", vecCopy.size(), timeVec);
	PmergeMe::printTime("list", lst.size(), timeLst);
	
	return (0);
}

/* For testing with a lot of number use the following command:
	./PmergeMe `jot -r 3000 1 100000 | tr '\n' ' '`

	jot			:stands for "just another output tool" and is used to generate random numbers.
	-r			:option is used to specify that the output should be random numbers.
	3000		:is the number of random numbers to generate.
	1			:is the minimum value of the random numbers.
	100000		:is the maximum value of the random numbers.
	tr '\n' ' '	:is used to replace the newline characters with spaces, so that the
				numbers are passed as separate arguments to the program.
*/