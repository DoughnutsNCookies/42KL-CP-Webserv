/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpptest.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:47:44 by schuah            #+#    #+#             */
/*   Updated: 2023/03/13 15:48:08 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

int main () {
	std::cout << "HTTP/1.1 200 OK\n";
	std::cout << "Content-type:text/html\r\n\r\n";
	std::cout << "<!DOCTYPE html>\n";
	std::cout << "<html lang=\"en\">\n";
	std::cout << "<head>\n";
	std::cout << "	<meta charset=\"UTF-8\">\n";
	std::cout << "	<meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">\n";
	std::cout << "	<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n";
	std::cout << "	<title>Document</title>\n";
	std::cout << "</head>\n";
	std::cout << "<body>\n";
	std::cout << "Hello World 2 \n";
	std::cout << "	<img src=\"2mb.jpg\" alt=\"Image\" height=\"500px\">\n";
	std::cout << "	<img src=\"south.png\" alt=\"Image\" height=\"500px\">\n";
	std::cout << "	<img src=\"south.png\" alt=\"Image\" height=\"500px\">\n";
	std::cout << "	<img src=\"south.png\" alt=\"Image\" height=\"500px\">\n";
	std::cout << "	<img src=\"south.png\" alt=\"Image\" height=\"500px\">\n";
	std::cout << "	<img src=\"south.png\" alt=\"Image\" height=\"500px\">\n";
	std::cout << "	<img src=\"south.png\" alt=\"Image\" height=\"500px\">\n";
	std::cout << "	<video src=\"test.mp4\" controls></video>\n";
	std::cout << "	<video src=\"rickroll.mp4\" controls></video>\n";
	std::cout << "	<video src=\"rickroll.mp4\" controls></video>\n";
	std::cout << "	<video src=\"rickroll.mp4\" controls></video>\n";
	std::cout << "	<video src=\"rickroll.mp4\" controls></video>\n";
	std::cout << "	<video src=\"rickroll.mp4\" controls></video>\n";
	std::cout << "	<iframe src=\"https://www.youtube.com/embed/AbIU2g50cqc\"></iframe>";
	std::cout << " <video width=\"500px\" height=\"500px\" controls=\"controls\"> <source src=\"test.mp4\" type=\"video/mp4\"></video>";
	std::cout << "	<script src=\"./javascript.js\"></script>\n";
	std::cout << "</body>\n";
	std::cout << "</html>\n";
   
   return (0);
}
