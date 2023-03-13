/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpDeleteResponse.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 16:22:15 by schuah            #+#    #+#             */
/*   Updated: 2023/03/13 16:37:13 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPDELETERESPONSE_HPP
# define HTTPDELETERESPONSE_HPP

# include <string>
# include <iostream>

# include <unistd.h>

# define RED		"\033[1;31m"
# define GREEN		"\033[1;32m"
# define RESET		"\033[0m"

class HttpDeleteResponse
{
	public:
		HttpDeleteResponse(int socket, std::string path);
		~HttpDeleteResponse();
		void	handleDelete();

	private:
		int		_socket;
		std::string	_path;
};

#endif
