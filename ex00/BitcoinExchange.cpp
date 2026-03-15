/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 15:28:26 by julcalde          #+#    #+#             */
/*   Updated: 2026/03/15 14:19:06 by julcalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <sstream>

BitcoinExchange::BitcoinExchange() {}

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
	if (date.size() != 10 || date[4] != '-' || date[7] != '-')
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
	std::ifstream file(filename.c_str()); // we use c_str() to ensure compatibility with older std::string implementations
	if (!file.is_open())
		return (false);
	std::string line;
	bool first = true;
	while (std::getline(file, line))
	{
		if (first) // skip header line
		{
			first = false;
			continue ;
		}
		std::istringstream iss(line); // we use a stringstream to parse the line and handle errors gracefully
		std::string date, rateString;
		if (!std::getline(iss, date, ',') || !std::getline(iss, rateString))
			continue ;
		date = trim(date);
		rateString = trim(rateString);
		if (!isValidDate(date))
			continue ;
		float rate = std::strtof(rateString.c_str(), NULL);
		_database[date] = rate;
	}
	return (true);
}

float BitcoinExchange::getRate(const std::string& date) const
{
	std::map<std::string, float>::const_iterator it = _database.find(date);
	if (it != _database.end())
		return (it->second);
	/* lower_bound returns the first element that is not less than the given date
		and we want the greatest element that is less than or equal to the given date */
	it = _database.lower_bound(date);
	if (it == _database.begin())
		return (0.0f); // before the first date in the database
	if (it == _database.end() || it->first != date) // if the date is not found, we need to step back to get the last valid rate
		--it;
	return (it->second);
}

void BitcoinExchange::processInput(const std::string& filename) const
{
	std::ifstream file(filename.c_str());
	if (!file.is_open())
	{
		std::cerr << "Error: could not open file." << std::endl;
		return ;
	}
	std::string line;
	bool first = true;
	while (std::getline(file, line)) // we read the file line by line to handle errors gracefully
	{
		if (first) // skip the header line
		{
			first = false;
			continue ;
		}
		std::istringstream iss(line); // we use a stringstream to parse the line and handle errors gracefully
		std::string date, valueString;
	/*
	date:		we expect a date in the format YYYY-MM-DD, followed by a pipe character, followed by a value.
				We will trim the date and value to handle extra spaces, and we will validate both the date and
				the value before processing them. 
				If any of these steps fail, we will print an error message and skip the line.
	valueString:we will read the value as a string first, trim it, and then validate it as a float before using it.
				This allows us to handle cases where the value is not a valid float
				and print an appropriate error message.
	*/
		if (!std::getline(iss, date, '|') || !std::getline(iss, valueString))
		{
			std::cerr << "Error: bad format input: " << trim(line) << std::endl;
			continue ;
		}
		date = trim(date);
		valueString = trim(valueString);
		if (!isValidDate(date))
		{
			std::cerr << "Error: bad date input: " << date << std::endl;
			continue ;
		}
		float value;
		if (!isValidValue(valueString, value))
		{
			if (value < 0)
				std::cerr << "Error: not a positive number." << std::endl;
			else
				std::cerr << "Error: too large of a number." << std::endl;
			continue ;
		}
		float rate = getRate(date);
		std::cout << date << " => " << value << " = " << (value * rate) << std::endl;
	}
}