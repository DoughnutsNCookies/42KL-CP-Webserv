/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpDefaultResponse.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 15:38:49 by schuah            #+#    #+#             */
/*   Updated: 2023/03/13 20:50:46 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPDEFAULTRESPONSE_HPP
# define HTTPDEFAULTRESPONSE_HPP

# include "WebServer.hpp"

class HttpDefaultResponse
{
	public:
		HttpDefaultResponse(int socket, EuleeHand database);
		~HttpDefaultResponse();
		void	handleDefault();

	private:
		EuleeHand	_database;
		int			_socket;
};

#endif
