/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Token.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 10:39:00 by schuah            #+#    #+#             */
/*   Updated: 2023/03/08 14:23:37 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/Token.hpp"

Token::Token(std::string token, Type type, int lineNum) : _token(token), _lineNum(lineNum), _type(type) {}

Token::~Token() {}

std::string	Token::getToken()
{
	return (this->_token);
}

int	Token::getLineNum()
{
	return (this->_lineNum);
}

Type	Token::getType()
{
	return (this->_type);
}
