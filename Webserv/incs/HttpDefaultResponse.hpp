/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpDefaultResponse.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 15:38:49 by schuah            #+#    #+#             */
/*   Updated: 2023/03/09 20:36:11 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPDEFAULTRESPONSE_HPP
# define HTTPDEFAULTRESPONSE_HPP

# include <string>
# include <iostream>
# include <unistd.h>
# include <poll.h>
# include <sys/select.h>

# include "webserv.hpp"

class HttpDefaultResponse
{
	public:
		HttpDefaultResponse(pollfd (&fds)[1], int socket);
		~HttpDefaultResponse();
		void	handleDefault();

	private:
		pollfd	(&_fds)[1];
		int		_socket;
};

#endif
