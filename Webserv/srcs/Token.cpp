/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Token.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhii <jhii@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 10:39:00 by schuah            #+#    #+#             */
/*   Updated: 2023/03/07 16:31:49 by jhii             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Token.hpp"

Token::Token(std::string token, Type type, int lineNum): _type(type), _token(token), _lineNum(lineNum) {}

Token::~Token(void) {}

std::string	Token::getToken(void)
{
	return (this->_token);
}

int	Token::getLineNum(void)
{
	return (this->_lineNum);
}

Type	Token::getType(void)
{
	return (this->_type);
}
