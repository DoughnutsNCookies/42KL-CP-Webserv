/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CookieJar.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 15:52:26 by schuah            #+#    #+#             */
/*   Updated: 2023/03/29 16:23:11 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CookieJar.hpp"

CookieJar::CookieJar() {}

CookieJar::~CookieJar() {}

tm *CookieJar::_generateExpirationTime(int expireTimeSeconds)
{
    time_t curr_time;
    curr_time = time(NULL);

    time_t expiry_time_t = curr_time + expireTimeSeconds;
    tm *gmt_time = gmtime(&expiry_time_t);
	return (gmt_time);
}

std::string CookieJar::_generateExpirationStr(tm *expiry_time)
{
	char	expiry_buf[32];

	std::memset(expiry_buf, 0, sizeof(expiry_buf));
    strftime(expiry_buf, sizeof(expiry_buf), "%a, %d %b %Y %H:%M:%S GMT", expiry_time);
    return (std::string(expiry_buf));
}

std::string	CookieJar::_generateHash()
{
    std::string hash;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, 35);
    const std::string characters = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    for (int i = 0; i < 32; i++)
        hash += characters[distrib(gen)];
	return (hash);
}

Cookie	CookieJar::generateCookie(int socket)
{
	this->_jar[socket] = Cookie("cookieId", this->_generateHash(), this->_generateExpirationStr(this->_generateExpirationTime(WS_COOKIE_EXPIRE_TIME)));
	return (this->_jar[socket]);
}

Cookie	&CookieJar::operator[](int socket)
{
	return (this->_jar[socket]);
}
