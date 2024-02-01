/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 04:19:43 by asabri            #+#    #+#             */
/*   Updated: 2024/01/31 07:46:33 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ConfigFile.hpp"

int main(int ac, char **av)
{
    if (ac == 2)
        ConfigFile configFile(av[1]);
    else 
    {
        try{
            ConfigFile configFile("/Users/asabri/Desktop/Webserv/Config/File.Conf");
            configFile.parse();
        }
        catch(const std::exception& e){
            cerr << e.what() << endl;
        }
    }
    return 0;
}
