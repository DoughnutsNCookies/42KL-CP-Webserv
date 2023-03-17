/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 18:13:23 by schuah            #+#    #+#             */
/*   Updated: 2023/03/13 20:37:22 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/webserv.hpp"

int	main(int ac, char **av)
{
	std::string configFile = DEFAULT_CONFIG_PATH;

	if (ac > 2)
	{
		std::cout << YELLOW "Usage: ./webserv <config_file>" RESET << std::endl;
		return (EXIT_FAILURE);
	}
	else if (ac == 2)
		configFile = av[1];
	std::cout << GREEN "Reading config file : " CYAN << configFile << RESET << std::endl;
	try {
		WebServer	webserver(configFile);
		webserver.runServer();
	}
	catch (std::exception &e) {
		std::cout << e.what() << std::endl;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
	// (void)ac;
	// (void)av;
	// EuleeHand hand;

	// hand.sendHttp(404, "./html/error.html");
}
