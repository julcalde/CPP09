/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 15:28:24 by julcalde          #+#    #+#             */
/*   Updated: 2026/03/31 15:04:02 by julcalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <string>
#include <cstdlib>
#include <map>			//std::map for key-value (date - exchange rate) pairs
#include <fstream>		//std::ifstream for file handling/reading
#include <sstream>		//std::istringstream for parsing lines from the input files
#include <algorithm>	//std::find_if for trimming whitespace from strings

class BitcoinExchange
{
	private:
		/*	std::map database
			set to private to prevent external modifications and ensure encapsulation
			we use std::map because it automatically sorts the keys (dates) and allows for efficient lookups
				- key: date (string in "YYYY-MM-DD" format)
				- value: exchange rate (float)
		*/
		std::map<std::string, float> _database;
		
		std::string trim(const std::string& s) const;	// removes leading/trailing whitespace from a string
		bool isValidDate(const std::string& date) const;	// validates that date strings are correctly formatted and represent valid calendar dates
		bool isValidValue(const std::string& value, float& out) const;	// validates that value strings can be converted to floats and values are within 0 - 1000 range
		float getRate(const std::string& date) const;	// finds most recent rate <= given date, returns 0.0f if no valid rate is found
		
	public:
		BitcoinExchange();
		~BitcoinExchange();
		BitcoinExchange(const BitcoinExchange&);
		BitcoinExchange& operator=(const BitcoinExchange&);

		bool loadDatabase(const std::string& filename); // loads database from CSV file, returns true on success, false on failure
		void processInput(const std::string& filename) const; // reads input file, validates each string, outputs results
};

#endif