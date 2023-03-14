/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpGetResponse.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 15:20:41 by schuah            #+#    #+#             */
/*   Updated: 2023/03/14 15:22:16 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPGETRESPONSE_HPP
# define HTTPGETRESPONSE_HPP

# include "WebServer.hpp"

class HttpGetResponse
{
	public:
		HttpGetResponse(EuleeHand database);
		~HttpGetResponse();
		void		handleGet();

	private:
		EuleeHand	_database;
};

#endif
