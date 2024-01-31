/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigFile.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 03:46:59 by asabri            #+#    #+#             */
/*   Updated: 2024/01/31 05:00:17 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <utility>

#include "Server.hpp"
extern vector<string> ServerDirective = {
    "body_size",
    "root",
    "autoindex",
    "allow_methods",
    "index",
    "error_page",
};
extern vector<string> ServerContext = {
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
        ConfigFile(string path);
        void parse();
        void getServers();
        void setServers(vector<Server> servers);
};