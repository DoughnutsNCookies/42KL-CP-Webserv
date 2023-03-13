/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EuleeWallet.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhii <jhii@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 15:10:48 by jhii              #+#    #+#             */
/*   Updated: 2023/03/13 19:46:53 by jhii             ###   ########.fr       */
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
	LOCATION_READ_PATH,
	LISTEN,
	ROOT,
	INDEX,
	SERVER_NAME,
	ERROR_PAGE,
	CLIENT_MAX_BODY_SIZE,
	AUTO_INDEX,
	RETURN,
	CGI,
	INCLUDE,
	UPLOAD,
	LIMIT_EXCEPT
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
