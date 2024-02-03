/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigFile.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 03:46:59 by asabri            #+#    #+#             */
/*   Updated: 2024/02/03 15:35:15 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <utility>
#include <sstream>
#include <stdlib.h>

#include "Server.hpp"
using namespace std;
class ConfigFile 
{
    private :
        ifstream   file;
        vector<Server> servers;
        vector<string> configServers;
        size_t      nbServer;
    public :
        ConfigFile(string path);
        void parse();
        void parseServer(string& line,Server& server);
        void getServers();
        void setServers(vector<Server> servers);
        void ServerContextToSplite(string& line);
        void printServers();
};