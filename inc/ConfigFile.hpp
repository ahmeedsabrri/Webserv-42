/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigFile.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 03:46:59 by asabri            #+#    #+#             */
/*   Updated: 2024/01/31 04:33:23 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <utility>

#include "Server.hpp"

extern array<string, 9> ServerDirectives = {
    "body_size",
    "root",
    "autoindex",
    "allow_methods",
    "index",
    "error_page",
};
extern array<string,3> Server = {
    "server_name",
    "port",
    "location"
};

using namespace std;
class ConfigFile 
{
    private :
        ifstream   file;
        vector<Server> servers;
    public :
        void parse();
        void setfile(string file);
};