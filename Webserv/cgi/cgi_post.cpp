/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cgi_post.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 13:18:38 by schuah            #+#    #+#             */
/*   Updated: 2023/03/10 19:31:13 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>

using namespace std;

int main()
{
	cout << "HTTP/1.1 200 OK\n";
	cout << "Content-type:text/html\r\n\r\n";
	cout << "<!DOCTYPE html>\n";
	cout << "<html lang=\"en\">\n";
	cout << "<head>\n";
	cout << "	<meta charset=\"UTF-8\">\n";
	cout << "	<meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">\n";
	cout << "	<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n";
	cout << "	<title>Document</title>\n";
	cout << "</head>\n";
	cout << "<body>\n";
	cout << "Testing CGI POST \n";
    cout << "   <form method=\"post\" enctype=\"multipart/form-data\">\n";
    cout << "   <label for=\"outfile\">Select a file:</label>\n";
    cout << "   <input type=\"file\" name=\"outfile\" id=\"outfile\">\n";
    cout << "   <input type=\"submit\" value=\"Submit\">\n";
    cout << "   </form>\n";
	cout << "</body>\n";
	cout << "</html>\n";

    return 0;
}
