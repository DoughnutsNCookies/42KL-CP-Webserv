/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EuleeWallet.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 15:12:18 by jhii              #+#    #+#             */
/*   Updated: 2023/03/29 15:54:37 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "EuleeWallet.hpp"

EuleeWallet::EuleeWallet() : cgi(), _location() {}

EuleeWallet::EuleeWallet(value_type location) : cgi(), _location(location) {}

EuleeWallet::mapped_type	&EuleeWallet::operator[](const key_type &key)
{
	return (this->_location[key]);
}

EuleeWallet::~EuleeWallet() {}


EuleeWallet::iterator	EuleeWallet::begin()
{
	return (this->_location.begin());
}

EuleeWallet::iterator	EuleeWallet::end()
{
	return (this->_location.end());
}
