/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 04:11:28 by asabri            #+#    #+#             */
/*   Updated: 2024/02/03 18:06:10 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <vector>
#include <utility>
#include <map>
#include "ServerDirectives.hpp"
#include "LocationContext.hpp"

using namespace std;

class Server : public ServerDirectives
{
    private :
        string  serverName;
        map<string,int>     port;
        map<string,LocationContext> locationContexts;
    public :
        Server();
        string getServerName();
        map<string,int>  getPort();
        map<string,LocationContext> getLocationContexts();
        void setServerName(string serverName);
        void setPort(string port);
        void setLocationContexts(string path,std::vector<std::string> param);

};