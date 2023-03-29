/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EuleePocket.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 17:51:53 by jhii              #+#    #+#             */
/*   Updated: 2023/03/29 15:54:37 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "EuleePocket.hpp"

EuleePocket::EuleePocket() : vectorLocation(), location(), portIndex(-1), _server() {}

EuleePocket::EuleePocket(EuleeWallet server, std::vector<EuleeWallet> vectorLocation) : vectorLocation(vectorLocation), location(), portIndex(-1), _server(server) {}

EuleePocket::~EuleePocket() {}

EuleePocket::mapped_type	&EuleePocket::operator[](key_type key)
{
	return (this->_server[key]);
}

EuleePocket::iterator	EuleePocket::begin()
{
	return (this->_server.begin());
}

EuleePocket::iterator	EuleePocket::end()
{
	return (this->_server.end());
}
