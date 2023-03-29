/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpPutResponse.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhii <jhii@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 14:00:35 by schuah            #+#    #+#             */
/*   Updated: 2023/03/29 12:29:02 by jhii             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPPUTRESPONSE_HPP
# define HTTPPUTRESPONSE_HPP

# include "EuleeHand.hpp"

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
