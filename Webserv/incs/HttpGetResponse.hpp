/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpGetResponse.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 15:20:41 by schuah            #+#    #+#             */
/*   Updated: 2023/03/10 17:50:23 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPGETRESPONSE_HPP
# define HTTPGETRESPONSE_HPP

# include <fstream>
# include <iostream>
# include <string>
# include <unistd.h>
# include <sys/socket.h>

# define RED		"\033[1;31m"
# define RESET		"\033[0m"
# define WS_TIMEOUT	3

class HttpGetResponse
{
	public:
		HttpGetResponse(std::string path, int socket);
		~HttpGetResponse();
		void	handleGet();

	private:
		int			_socket;
		std::string	_path;
};

#endif
