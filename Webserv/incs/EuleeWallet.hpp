/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EuleeWallet.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhii <jhii@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 15:10:48 by jhii              #+#    #+#             */
/*   Updated: 2023/03/10 17:00:11 by jhii             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EULEEWALLET_HPP
# define EULEEWALLET_HPP

# include <string>
# include <iostream>

enum	RegularExpression
{
	NOT_SPECIFIED,		// everything else
	CASE_SENSITIVE,		// ~
	CASE_INSENSITIVE,	// ~*
	IGNORE_OTHERS,		// ^~
	EXACT_MATCH			// =
};

// location block
struct EuleeWallet
{
	EuleeWallet(void);
	EuleeWallet(RegularExpression priority, std::string valuePath, std::string root, std::string index, std::string include, std::string cgiPass, std::string cgiIndex, std::string cgiParam);
	~EuleeWallet(void);

	RegularExpression	priority;
	std::string			valuePath, root, index, include;
	std::string			cgiPass, cgiIndex, cgiParam;
};

#endif
