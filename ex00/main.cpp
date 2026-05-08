/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 15:28:22 by julcalde          #+#    #+#             */
/*   Updated: 2026/05/08 18:01:59 by julcalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <iostream>

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "Error: could not open file." << std::endl;
		return (1);
	}
	BitcoinExchange exchanger;
	if (!exchanger.loadDatabase("data.csv"))
	{
		std::cerr << "Error: could not load database." << std::endl;
		return (1);
	}
	exchanger.processInput(argv[1]);
	return (0);
}
