/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpDefaultResponse.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 15:38:49 by schuah            #+#    #+#             */
/*   Updated: 2023/03/13 18:39:30 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPDEFAULTRESPONSE_HPP
# define HTTPDEFAULTRESPONSE_HPP

# include "WebServer.hpp"

class HttpDefaultResponse
{
	public:
		HttpDefaultResponse(int socket);
		~HttpDefaultResponse();
		void	handleDefault();

	private:
		int		_socket;
};

#endif
