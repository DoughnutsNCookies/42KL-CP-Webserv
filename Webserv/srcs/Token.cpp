/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Token.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhii <jhii@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 10:39:00 by schuah            #+#    #+#             */
/*   Updated: 2023/03/10 17:37:59 by jhii             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Token.hpp"

Token::Token(std::string token, Type type, int lineNum): type(type), token(token), lineNum(lineNum) {}

Token::~Token(void) {}
