/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Token.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 10:18:53 by schuah            #+#    #+#             */
/*   Updated: 2023/03/29 15:53:53 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_HPP
# define TOKEN_HPP

# include "webserv.hpp"

enum Type
{
    CONTEXT,
    KEY,
    VALUE,
    SEMICOLON,
    OPEN_BRACE,
    CLOSE_BRACE
};

struct Token
{
	Token(std::string context, Type type, int lineNum);
	~Token();

	Type		type;
	std::string	token;
	int			lineNum;
};

#endif
