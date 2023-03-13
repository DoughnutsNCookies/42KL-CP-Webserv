/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EuleeWallet.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhii <jhii@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 15:12:18 by jhii              #+#    #+#             */
/*   Updated: 2023/03/13 13:06:42 by jhii             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "EuleeWallet.hpp"

EuleeWallet::EuleeWallet(void) : priority(), readPath(), root(), index(), include(), cgiPass(), cgiIndex(), cgiParam() {}

EuleeWallet::EuleeWallet(RegularExpression priority, std::string readPath, std::string root, std::string index, std::string include, std::string cgiPass, std::string cgiIndex, std::string cgiParam) : priority(), readPath(), root(), index(), include(), cgiPass(), cgiIndex(), cgiParam()
{
	this->readPath = readPath;
	this->priority = priority;
	this->root = root;
	this->index = index;
	this->include = include;
	this->cgiPass = cgiPass;
	this->cgiIndex = cgiIndex;
	this->cgiParam = cgiParam;
}

EuleeWallet::~EuleeWallet(void) {}
