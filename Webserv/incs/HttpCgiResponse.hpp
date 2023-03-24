/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpCgiResponse.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 10:54:29 by schuah            #+#    #+#             */
/*   Updated: 2023/03/24 16:01:44 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPCGIRESPONSE_HPP
# define HTTPCGIRESPONSE_HPP

# include "WebServer.hpp"

class HttpCgiResponse
{
	public:
		HttpCgiResponse(EuleeHand *database);
		~HttpCgiResponse();
		void		handleCgi();

	private:
		EuleeHand	*_database;
};

#endif
