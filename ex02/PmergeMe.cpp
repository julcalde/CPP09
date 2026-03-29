/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 16:53:10 by julcalde          #+#    #+#             */
/*   Updated: 2026/03/29 15:44:45 by julcalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <iostream>
#include <algorithm>
#include <sys/time.h>

PmergeMe::PmergeMe() {}

PmergeMe::~PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe&) {}

PmergeMe& PmergeMe::operator=(const PmergeMe&)
{
	return (*this);
}

/* getTime()
	Helper function to get current time in microseconds.
	It returns the current time as a double representing the number of microseconds since the epoch.
*/
double PmergeMe::getTime()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1e6 + tv.tv_usec);
}

static void mergeInsertVector(std::vector<int>& vec, size_t left, size_t mid, size_t right)
{
	std::vector<int> tmp(right - left + 1);
	size_t i = left, j = mid + 1, k = 0;

	while (i <= mid && j <= right)
	tmp[k++] = (vec[i] <= vec[j]) ? vec[i++] : vec[j++];
	while (i <= mid)
		tmp[k++] = vec[i++];
	while (j <= right)
		tmp[k++] = vec[j++];
	for (k = 0; k < tmp.size(); ++k)
		vec[left + k] = tmp[k];
}

static void fordJohnsonVector(std::vector<int>& vec, size_t left, size_t right)
{
	if (right - left < 1)
		return ;
	if (right - left == 1)
	{
		if (vec[left] > vec[right])
			std::swap(vec[left], vec[right]);
		return ;
	}
	size_t mid = left + (right - left) / 2;
	fordJohnsonVector(vec, left, mid);
	fordJohnsonVector(vec, mid + 1, right);
	mergeInsertVector(vec, left, mid, right);
}

void PmergeMe::sortVector(std::vector<int>& vec)
{
	if (vec.size() <= 1)
		return ;
	fordJohnsonVector(vec, 0, vec.size() - 1);
}

static void mergeInsertList(std::list<int>::iterator left, std::list<int>::iterator mid, std::list<int>::iterator right)
{
	std::list<int> tmp;
	std::list<int>::iterator iter1 = left, iter2 = mid;
	
	while (iter1 != mid && iter2 != right)
	{
		if (*iter1 <= *iter2)
			tmp.push_back(*iter1++);
		else
			tmp.push_back(*iter2++);
	}
	while (iter1 != mid)
		tmp.push_back(*iter1++);
	while (iter2 != right)
		tmp.push_back(*iter2++);
	std::list<int>::iterator dst = left;
	std::list<int>::iterator src = tmp.begin();
	for (; src != tmp.end(); ++src, ++dst)
		*dst = *src;
}

static void fordJohnsonList(std::list<int>::iterator left, std::list<int>::iterator right)
{
	size_t len = std::distance(left, right);
	if (len <= 1)
		return ;
	if (len == 2)
	{
		std::iter_swap(left, std::prev(right));
		return ;
	}
	std::list<int>::iterator mid = left;
	std::advance(mid, len / 2);
	fordJohnsonList(left, mid);
	std::list<int>::iterator next = mid;
	fordJohnsonList(next, right);
	mergeInsertList(left, mid, right);
}

void PmergeMe::sortList(std::list<int>& lst)
{
	if (lst.size() <= 1)
		return ;
	std::list<int>::iterator begin = lst.begin();
	std::list<int>::iterator end = lst.end();
	fordJohnsonList(begin, --end);
}

void PmergeMe::printTime(const std::string& cont, size_t size, double us)
{
	std::cout << "Time to process a range of " << size
			<< " elements with std::" << cont << " : "
			<< us << " us" << std::endl;
}