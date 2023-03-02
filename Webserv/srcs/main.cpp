/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 18:13:23 by schuah            #+#    #+#             */
/*   Updated: 2023/03/02 13:32:48 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

int	main(int ac, char **av)
{
	std::string config_file = DEFAULT_CONFIG_PATH;

	if (ac > 2)
	{
		std::cout << "Usage: ./webserv <config_file>" << std::endl;
		return (EXIT_FAILURE);
	}
	else if (ac == 2)
		config_file = av[1];
	std::cout << "Using config file: " << config_file << std::endl;
	WebServer	webserver(config_file);
	return (EXIT_SUCCESS);
}
