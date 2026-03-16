/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 16:53:10 by julcalde          #+#    #+#             */
/*   Updated: 2026/03/16 17:30:13 by julcalde         ###   ########.fr       */
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
static double getTime()
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
		vec[left + k] = tmp[left];
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