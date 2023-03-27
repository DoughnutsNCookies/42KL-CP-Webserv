/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpPutResponse.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 14:00:35 by schuah            #+#    #+#             */
/*   Updated: 2023/03/24 16:06:27 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPPUTRESPONSE_HPP
# define HTTPPUTRESPONSE_HPP

# include "WebServer.hpp"

class HttpPutResponse
{
	public:
		HttpPutResponse(EuleeHand *database);
		~HttpPutResponse();
		void		handlePut();

	private:
		EuleeHand	*_database;
};

#endif
