/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 15:28:26 by julcalde          #+#    #+#             */
/*   Updated: 2026/01/11 18:19:44 by julcalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <sstream>

BitcoinExchange::~BitcoinExchange() {}

BitcoinExchange::~BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange&) {}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange&)
{
	return (*this);
}

std::string BitcoinExchange::trim(const std::string& s) const
{
	std::string::size_type first = s.find_first_not_of(" \t");
	if (first == std::string::npos)
		return ("");
	std::string::size_type last = s.find_last_not_of(" \t");
	return (s.substr(first, last - first + 1));
}

bool BitcoinExchange::isValidDate(const std::string& date) const
{
	if (date.size() != 10 || date[4] != "-" || date[7] != "-")
		return (false);
	for (int i = 0; i < 10; ++i)
	{
		if (i == 4 || i == 7)
			continue ;
		else if (!isdigit(date[i]))
			return (false);
	}
	
	int year = atoi(date.substr(0, 4).c_str());
	int month = atoi(date.substr(5, 2).c_str());
	int day = atoi(date.substr(8, 2).c_str());

	if (year < 2009 || month < 1 || month > 12 || day < 1 || day > 31)
		return (false);
	return (true);
}

bool BitcoinExchange::isValidValue(const std::string& value, float& out) const
{
	char *end;
	out = std::strtof(value.c_str(), &end);
	
	if (*end != '\0')
		return (false);
	if (out < 0 || out > 1000)
		return (false);
	return (true);
}

bool BitcoinExchange::loadDatabase(const std::string& filename)
{
	std::ifstream file(filename.c_str());
	if (!file.is_open())
		return (false);
	std::string line;
	bool first = true;
	while (std::getline(file, line))
	{
		if (first)
		{
			first = false;
			continue ;
		}
		std::istringstream iss(line);
		std::string date, rateString;
		if (!std::getline(iss, date, ',') || !std::getline(iss, rateString))
			continue ;
		date = trim(date);
		rateString = trim(rateString);
		if (!isValidDate(date))
			continue ;
		float rate = std::strtof(rateString.c_str(),NULL);
		_database[date] = rate;
	}
	return (true);
}

