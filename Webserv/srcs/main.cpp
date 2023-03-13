/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 18:13:23 by schuah            #+#    #+#             */
/*   Updated: 2023/03/13 18:35:45 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/webserv.hpp"

int	main(int ac, char **av)
{
	std::string configFile = DEFAULT_CONFIG_PATH;

	if (ac > 2)
	{
		std::cout << "Usage: ./webserv <configFile>" << std::endl;
		return (EXIT_FAILURE);
	}
	else if (ac == 2)
		configFile = av[1];
	std::cout << "Using config file: " << configFile << std::endl;
	try {
		WebServer	webserver(configFile);
		webserver.runServer();
	}
	catch (std::exception &e) {
		std::cout << e.what() << std::endl;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
