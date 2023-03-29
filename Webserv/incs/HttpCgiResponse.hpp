/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpCgiResponse.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhii <jhii@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 10:54:29 by schuah            #+#    #+#             */
/*   Updated: 2023/03/29 12:28:34 by jhii             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPCGIRESPONSE_HPP
# define HTTPCGIRESPONSE_HPP

# include "EuleeHand.hpp"

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
