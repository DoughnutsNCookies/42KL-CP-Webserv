/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EuleePocket.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhii <jhii@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 17:51:51 by jhii              #+#    #+#             */
/*   Updated: 2023/03/09 12:28:01 by jhii             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EULEEPOCKET_HPP
# define EULEEPOCKET_HPP

# include <string>
# include <vector>
# include <iostream>

struct EuleePocket
{
	EuleePocket(void) {};
	~EuleePocket(void) {};

	// server block
	std::string					root;
	std::vector<std::string>	index;

	std::vector<std::string>	server_name;
	std::vector<std::string>	location_path;
};

#endif
