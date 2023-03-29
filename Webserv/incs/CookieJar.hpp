/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CookieJar.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 15:47:57 by schuah            #+#    #+#             */
/*   Updated: 2023/03/29 16:47:17 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COOKIEJAR_HPP
# define COOKIEJAR_HPP

# include "webserv.hpp"

struct Cookie
{
	Cookie() {};
	Cookie(std::string key, std::string value, std::string expireDate) : key(key), value(value), expireDate(expireDate) {}
	~Cookie() {}

	std::string	key;
	std::string	value;
	std::string	expireDate;
};


class CookieJar 
{
	public:
		CookieJar();
		~CookieJar();

		Cookie		&operator[](int socket);
		Cookie		generateCookie(int socket);
		bool		checkCookie(std::string cookieRequest);

	private:
		tm 			*_generateExpirationTime(int expireTimeSeconds);
		std::string	_generateExpirationStr(tm *expiry_time);
		std::string	_generateHash();

		std::map<int, Cookie>	_jar;

		// std::unordered_map<std::string, Cookie>	getCookieDB() const;
		// std::string sendCookie() const;
		// std::string	generateHash();

		// long int 	generateExpirationTime(int expireTimeSeconds);
		// std::string generateExpirationStr(tm *expiryTime);

		// Cookie	&operator[](const std::string& name);
		// bool	checkExpiration(time_t time) const;
		// bool	checkClientCookie(std::string key, std::string value);
		// void	addCookie(const Cookie& cookie);
		// void	insertCookie(const std::string& name);
		// const	std::vector<Cookie>& getCookies() const;
		// std::string dataResponse() const;

		// std::string clientCookieName;
		// std::string clientCookieHash;

		// private:
    	// 	std::unordered_map<std::string, Cookie> _cookieDB;
};

#endif
