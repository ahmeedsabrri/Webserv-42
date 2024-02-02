/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 22:20:50 by asabri            #+#    #+#             */
/*   Updated: 2024/02/02 19:48:00 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Server.hpp"
#include <netinet/in.h>
Server::Server()
{
    this->serverName = "";
}
string Server::getServerName()
{
    return (this->serverName);
}

map<string,int> Server::getPort()
{
    return (this->port);
}

void Server::setServerName(string serverName)
{
    if (serverName.back() != ';')
        throw runtime_error("Error: missing semicolon");
    serverName.pop_back();
    this->serverName = serverName;
}

void Server::setPort(string port)
{
    int port_ = 0;
    string ip_;
    if (port.back() != ';')
        throw runtime_error("Error: missing semicolon listen directive");
    if (port.find(':') == string::npos)
        throw runtime_error("Error: wrong syntax listen directive");
    port.pop_back();
    int i = 0;
    if (port[0] == ':')
        ip_ = "localhost";
    else {
        while (port[i++] && port[i] != ':')
            ip_ = port.substr(0,i + 1);
    }
    i++;
    if (port[i] == '\0')
        throw runtime_error("Error: no port specified in listen directive");
    while (port[i])
    {
        if (!isdigit(port[i]))
            throw runtime_error("Error: wrong port");
        port_ = port_ * 10 + (port[i] - '0');
        i++;
    }
    if (port_ < 0 || port_ > 65535)
        throw runtime_error("Error: wrong port1");
    cout << "ip: " << ip_ << " port: " << port_ << endl;
    this->port.insert(pair<string,int>(ip_,port_));
}
// void LocationContext::checkLocationPath(string locationPath)
// {
    
// }
void Server::setLocationContexts(string path,std::vector<std::string> param)
{
    LocationContext locationContext;
    locationContext.setPath(path);
    bool methodes = false;
    bool index = false;
    bool autoindex = false;
    for (size_t i = 0; i < param.size(); i++)
    {
        if (param[i] == "root")
            locationContext.setRoot(param[i + 1]);
        else if (param[i] == "allow_methodes" && !methodes)
        {
            stringstream allow;
            while (++i < 3)
            {
                if (param[i].back() == ';')
                {
                    param[i].pop_back();
                    allow << param[i];
                    locationContext.setAllowMethodes(allow);
                    break ;
                }
                allow << param[i] << " ";
            }
            methodes = true;
        }
        else if (param[i] == "index" && !index)
        {
            while (++i < param.size())
            {
                if (param[i].back() == ';')
                {
                    param[i].pop_back();
                    locationContext.setIndex(param[i]);
                    break ;
                }
                locationContext.setIndex(param[i]);
            }
            index = true;
        }
        else if (param[i] == "autoindex" && !autoindex)
        {
            locationContext.setAutoIndex(param[i + 1]);
            autoindex = true;
        }
        else if (param[i] == "client_max_body_size")
        {
            locationContext.setBodySize(param[i + 1]);
        }
        else if (param[i] == "error_page")
        {
            stringstream errorPage;
            while (++i < param.size())
            {
                if (param[i].back() == ';')
                {
                    param[i].pop_back();
                    errorPage << param[i];
                    locationContext.setErrorPage(errorPage);
                    break ;
                }
                errorPage << param[i] << " ";
            }
        }
        else if (param[i] == "cgi")
        {
            stringstream cgi;
            while (++i < param.size())
            {
                if (param[i].back() == ';')
                {
                    cgi << param[i];
                    locationContext.setCgi(cgi);
                    break ;
                }
                cgi << param[i] << " ";
            }
        }
        else if (param[i] == "return")
        {
            stringstream return_;
            while (++i < param.size())
            {
                if (param[i].back() == ';')
                {
                    return_ << param[i];
                    locationContext.setRedir(return_);
                    break ;
                }
                return_ << param[i] << " ";
            }
           
        }
    }
    if (locationContext.getPath() == "" && this->getRoot() != "")
        locationContext.setRoot(this->getRoot());
    
    this->locationContexts.push_back(locationContext);
    while (this->locationContexts.size() > 1)
    {
        if (this->locationContexts[this->locationContexts.size() - 1].getPath() == this->locationContexts[this->locationContexts.size() - 2].getPath())
            throw runtime_error("Error: duplicate location path");
        this->locationContexts.pop_back();
    }
}