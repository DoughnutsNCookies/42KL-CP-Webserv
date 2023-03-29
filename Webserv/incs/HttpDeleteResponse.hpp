/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpDeleteResponse.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhii <jhii@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 16:22:15 by schuah            #+#    #+#             */
/*   Updated: 2023/03/29 12:28:42 by jhii             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPDELETERESPONSE_HPP
# define HTTPDELETERESPONSE_HPP

# include "EuleeHand.hpp"

class HttpDeleteResponse
{
	public:
		HttpDeleteResponse(EuleeHand *database);
		~HttpDeleteResponse();
		void	handleDelete();

	private:
		EuleeHand	*_database;
};

#endif
