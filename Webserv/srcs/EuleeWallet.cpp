/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EuleeWallet.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhii <jhii@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 15:12:18 by jhii              #+#    #+#             */
/*   Updated: 2023/03/13 19:31:12 by jhii             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "EuleeWallet.hpp"

EuleeWallet::EuleeWallet(void) : _location() {}

EuleeWallet::EuleeWallet(value_type location) : _location(location) {}

EuleeWallet::mapped_type	&EuleeWallet::operator[](const key_type &key)
{
	return (this->_location[key]);
}

EuleeWallet::~EuleeWallet(void) {}


EuleeWallet::iterator	EuleeWallet::begin(void)
{
	return (this->_location.begin());
}

EuleeWallet::iterator	EuleeWallet::end(void)
{
	return (this->_location.end());
}
