/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpHeadResponse.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 17:41:20 by schuah            #+#    #+#             */
/*   Updated: 2023/03/13 18:39:21 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPHEADRESPONE_HPP
# define HTTPHEADRESPONE_HPP

# include "WebServer.hpp"

class HttpHeadResponse
{
	public:
		HttpHeadResponse(int socket, std::string path);
		~HttpHeadResponse();
		void	handleHead();

	private:
		int		_socket;
		std::string	_path;
};

#endif
