/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpHeadResponse.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhii <jhii@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 17:41:20 by schuah            #+#    #+#             */
/*   Updated: 2023/03/29 12:28:53 by jhii             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPHEADRESPONE_HPP
# define HTTPHEADRESPONE_HPP

# include "EuleeHand.hpp"

class HttpHeadResponse
{
	public:
		HttpHeadResponse(EuleeHand *database);
		~HttpHeadResponse();
		void	handleHead();

	private:
		EuleeHand	*_database;
};

#endif
