/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpPostResponse.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 15:22:30 by schuah            #+#    #+#             */
/*   Updated: 2023/03/24 16:18:42 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPPOSTRESPONSE_HPP
# define HTTPPOSTRESPONSE_HPP

# include "WebServer.hpp"

class HttpPostResponse
{
	public:
		HttpPostResponse(EuleeHand *database);
		~HttpPostResponse();
		void		handlePost();

	private:
		void		_normalSave();
		void		_saveFile();

		EuleeHand	*_database;
		size_t		_contentLength;
		int 		_contentLengthSpecified;
};

#endif
