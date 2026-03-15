/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 16:53:04 by julcalde          #+#    #+#             */
/*   Updated: 2026/03/15 15:02:57 by julcalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
# define RPN_HPP

# include <stack>
# include <string>

class RPN
{
	public:
		RPN();
		~RPN();
		RPN(const RPN&);
		RPN& operator=(const RPN&);

		static bool evaluate(const std::string& expr, int& result);
};

#endif