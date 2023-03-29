/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpPostResponse.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhii <jhii@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 15:22:30 by schuah            #+#    #+#             */
/*   Updated: 2023/03/29 12:28:57 by jhii             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPPOSTRESPONSE_HPP
# define HTTPPOSTRESPONSE_HPP

# include "EuleeHand.hpp"

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
