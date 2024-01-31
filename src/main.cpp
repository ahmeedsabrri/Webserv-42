/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 04:19:43 by asabri            #+#    #+#             */
/*   Updated: 2024/01/31 04:50:42 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ConfigFile.hpp"

int main(int ac, char **av)
{
    if (ac != 2)
        ConfigFile configFile("../Config/File.conf");
    else 
    {
        
        ConfigFile configFile(av[1]);
        try{
            configFile.parse();
        }
        catch(const std::exception& e){
            cerr << e.what() << endl;
        }
    }
    return 0;
}
