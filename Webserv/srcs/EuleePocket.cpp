/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EuleePocket.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhii <jhii@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 17:51:53 by jhii              #+#    #+#             */
/*   Updated: 2023/03/17 14:03:04 by jhii             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "EuleePocket.hpp"

EuleePocket::EuleePocket(void) : vectorLocation(), location(), portIndex(-1), _server() {}

EuleePocket::EuleePocket(EuleeWallet server, std::vector<EuleeWallet> vectorLocation) : vectorLocation(vectorLocation), location(), portIndex(-1), _server(server) {}

EuleePocket::~EuleePocket(void) {}

EuleePocket::mapped_type	&EuleePocket::operator[](key_type key)
{
	return (this->_server[key]);
}

EuleePocket::iterator	EuleePocket::begin(void)
{
	return (this->_server.begin());
}

EuleePocket::iterator	EuleePocket::end(void)
{
	return (this->_server.end());
}
