/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EuleeWallet.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhii <jhii@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 15:10:48 by jhii              #+#    #+#             */
/*   Updated: 2023/03/10 16:18:13 by jhii             ###   ########.fr       */
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
	~EuleeWallet(void);

	RegularExpression	priority;
	std::string			valuePath, root, index, include;
	std::string			cgiPass, cgiIndex, cgiParam;
};

#endif
