/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhii <jhii@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 18:13:23 by schuah            #+#    #+#             */
/*   Updated: 2023/03/07 16:30:33 by jhii             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

int	main(int ac, char **av)
{
	std::string config_file = DEFAULT_CONFIG_PATH;

	if (ac > 2)
	{
		std::cout << YELLOW "Usage: ./webserv <config_file>" RESET << std::endl;
		return (EXIT_FAILURE);
	}
	else if (ac == 2)
		config_file = av[1];
	std::cout << GREEN "Reading config file : " CYAN << config_file << RESET << std::endl;
	try {
		WebServer	webserver(config_file);
		webserver.runServer();
	}
	catch (std::exception &e) {
		std::cout << e.what() << std::endl;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
