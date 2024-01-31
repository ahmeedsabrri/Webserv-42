/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 05:02:15 by asabri            #+#    #+#             */
/*   Updated: 2024/01/31 05:39:28 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

int main(int ac, char **av)
{
    fstream file;
    stringstream ss;
    
    file.open("/home/asabri/Desktop/Webserv-42/Config/File.Conf");
    if (file.is_open())
    {
        string line;
        while (getline(file, line))
        {
            if (line.find("#") != string::npos) 
                continue;
            else 
                ss << line << endl;
        }
        cout << ss.str() << endl;
    }
    else
        cout << "Error" << endl;
    return 0;
}
