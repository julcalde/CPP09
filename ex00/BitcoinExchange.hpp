/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 15:28:24 by julcalde          #+#    #+#             */
/*   Updated: 2026/01/11 17:50:32 by julcalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <map>
#include <string>

#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <cstdlib>

class BitcoinExchange
{
	private:
		std::map<std::string, float> _database;
		
		std::string trim(const std::string& s) const;
		bool isValidDate(const std::string& date) const;
		bool isValidValue(const std::string& value, float& out) const;
		float getRate(const std::string& date) const;
		
	public:
		BitcoinExchange();
		~BitcoinExchange();
		BitcoinExchange(const BitcoinExchange&);
		BitcoinExchange& operator=(const BitcoinExchange&);

		bool loadDatabase(const std::string& filename);
		void processInput(const std::string& filename);
};

#endif