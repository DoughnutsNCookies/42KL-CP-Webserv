/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EuleeWallet.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 15:10:48 by jhii              #+#    #+#             */
/*   Updated: 2023/03/16 20:02:20 by schuah           ###   ########.fr       */
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
	CLIENT_MAX_BODY_SIZE,
	AUTO_INDEX,
	RETURN, //TBR
	CGI,
	INCLUDE,
	UPLOAD, //USING
	LIMIT_EXCEPT //USING
};

// location block
class EuleeWallet
{
	public:
		typedef Key								key_type;
		typedef std::vector<std::string>		mapped_type;
		typedef std::map<key_type, mapped_type>	value_type;
		typedef	value_type::iterator			iterator;

		EuleeWallet(void);
		EuleeWallet(value_type location);
		~EuleeWallet(void);

		mapped_type	&operator[](const key_type &key);

		iterator	begin(void);
		iterator	end(void);

	private:
		value_type	_location;
};

#endif
