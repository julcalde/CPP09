/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 16:53:12 by julcalde          #+#    #+#             */
/*   Updated: 2026/03/31 18:45:24 by julcalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include <vector> // Dynamic array with random access
#include <list>	// Doubly linked list with bidirectional access
#include <string>

class PmergeMe
{
	public:
		PmergeMe();
		~PmergeMe();
		PmergeMe(const PmergeMe&);
		PmergeMe& operator=(const PmergeMe&);

		static void sortVector(std::vector<int>& vec);
		static void sortList(std::list<int>& lst);
		static void printTime(const std::string& containerType, size_t size, double us);
		static double getTime();
};

#endif