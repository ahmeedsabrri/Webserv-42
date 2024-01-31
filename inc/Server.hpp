/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 04:11:28 by asabri            #+#    #+#             */
/*   Updated: 2024/01/31 04:31:18 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <vector>
#include <utility>

#include "ServerDirectives.hpp"
#include "LocationContext.hpp"

using namespace std;

class Server : public ServerDirectives
{
    private :
        string  serverName;
        int     port;
        vector<LocationContext> locationContexts;
    public :
        void getServerName();
        void getPort();
        void getLocationContexts();
        void setServerName(string serverName);
        void setPort(int port);
        void setLocationContexts(vector<LocationContext> locationContexts);

};