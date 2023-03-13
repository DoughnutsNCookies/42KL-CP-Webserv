/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EuleePocket.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 17:51:53 by jhii              #+#    #+#             */
/*   Updated: 2023/03/13 20:41:14 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "EuleePocket.hpp"

EuleePocket::EuleePocket(void) : envp(), location(), serverFd(), serverAddr(), path(), method(), buffer(), socket(), contentLength(), valread(), _server() {}

EuleePocket::EuleePocket(EuleeWallet server, std::vector<EuleeWallet> location) : envp(), location(location), serverFd(), serverAddr(), path(), method(), buffer(), socket(), contentLength(), valread(), _server(server) {}

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
