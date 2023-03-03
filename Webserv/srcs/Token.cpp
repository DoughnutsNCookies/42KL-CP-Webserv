/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Token.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 10:39:00 by schuah            #+#    #+#             */
/*   Updated: 2023/03/03 10:50:40 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Token.hpp"

Token::Token(const std::string &context, Type type, int lineNum) : _context(context), _lineNum(lineNum), _type(type) {}

Token::~Token() {}

std::string	Token::getContext()
{
	return (this->_context);
}

int	Token::getLineNum()
{
	return (this->_lineNum);
}

Token::Type	Token::getType()
{
	return (this->_type);
}
