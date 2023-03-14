/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpDeleteResponse.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 16:22:15 by schuah            #+#    #+#             */
/*   Updated: 2023/03/14 15:21:35 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPDELETERESPONSE_HPP
# define HTTPDELETERESPONSE_HPP

# include "WebServer.hpp"

class HttpDeleteResponse
{
	public:
		HttpDeleteResponse(EuleeHand database);
		~HttpDeleteResponse();
		void	handleDelete();

	private:
		EuleeHand	_database;
};

#endif
