/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EuleeWallet.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 15:10:48 by jhii              #+#    #+#             */
/*   Updated: 2023/03/21 12:30:06 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EULEEWALLET_HPP
# define EULEEWALLET_HPP

# include <map>
# include <vector>
# include <string>
# include <iostream>

enum	Key
{
	LOCATION_READ_PATH, //USING
	LISTEN, //USING
	ROOT, //USING
	INDEX, //USING
	SERVER_NAME, //USING
	ERROR_PAGE,
	CLIENT_MAX_BODY_SIZE, //USING
	AUTO_INDEX,
	RETURN,
	CGI,
	INCLUDE,
	UPLOAD, //USING
	LIMIT_EXCEPT //USING
};

// location block
class EuleeWallet
{
	public:
		typedef Key									key_type;
		typedef std::vector<std::string>			mapped_type;
		typedef std::map<key_type, mapped_type>		value_type;
		typedef std::map<std::string, std::string>	cgi_type;
		typedef	value_type::iterator				iterator;

		EuleeWallet(void);
		EuleeWallet(value_type location);
		~EuleeWallet(void);

		mapped_type	&operator[](const key_type &key);

		iterator	begin(void);
		iterator	end(void);

		cgi_type	cgi;

	private:
		value_type	_location;
};

#endif
