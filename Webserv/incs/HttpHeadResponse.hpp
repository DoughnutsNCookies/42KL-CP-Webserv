/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpHeadResponse.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 17:41:20 by schuah            #+#    #+#             */
/*   Updated: 2023/03/14 15:11:48 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPHEADRESPONE_HPP
# define HTTPHEADRESPONE_HPP

# include "WebServer.hpp"

class HttpHeadResponse
{
	public:
		HttpHeadResponse(EuleeHand database);
		~HttpHeadResponse();
		void	handleHead();

	private:
		EuleeHand	_database;
};

#endif
