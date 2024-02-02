/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigFile.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 07:39:34 by asabri            #+#    #+#             */
/*   Updated: 2024/02/02 19:53:16 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ConfigFile.hpp"
#include "../inc/Server.hpp"
#include <algorithm>
ConfigFile::ConfigFile(string path)
{
    this->nbServer = 0;
    this->file.open(path);
    if (!this->file.is_open())
        throw runtime_error("Error opening file");
}
void skipwhitespaces(string& line)
{
    int i = 0;

    while (line[i] && isspace(line[i]))
        i++;
    line = line.substr(i);
    i = line.length() - 1;
    while (i > 0 && isspace(line[i]))
        i--;
    line = line.substr(0,i + 1);
}
void skipComments(string& line)
{
    string config;
    for (size_t i = 0; i < line.size(); i++)
    {
        if (line[i] == '#')
        {
            size_t j = 0;
            while (line[i + j] != '\n'){j++;}
            i += j + 1;
        }
        config += line[i];
    }
    line = config;
}
size_t findStart(string& line, size_t start)
{
    size_t i;

	for (i = start; line[i]; i++)
	{
		if (line[i] == 's')
			break ;
		if (!isspace(line[i]))
			throw  runtime_error("Wrong character out of server scope{}1");
	}
	if (!line[i])
		return (start);
	if (line.compare(i, 6, "server") != 0)
		throw runtime_error("Wrong character out of server scope{}2");
	i += 6;
	while (line[i] && isspace(line[i])){i++;}
	if (line[i] == '{')
        return (i);
	throw  runtime_error("Wrong character out of server scope{}3");
}
size_t findEnd(string& line, size_t start)
{
    size_t	i;
	size_t	scope;
	
	scope = 0;
	for (i = start + 1; line[i]; i++)
	{
		if (line[i] == '{')
			scope++;
		if (line[i] == '}')
		{
			if (!scope)
				return (i);
			scope--;
		}
	}
	return (start);
}
void ConfigFile::ServerContextToSplite(string& line)
{
    size_t start = 0;
    size_t end = 1;
    
    if (line.find("server",0) == string::npos)
        throw runtime_error("Error : server directive not found");
    while (start != end && start < line.length())
    {
        start = findStart(line, start);
        end = findEnd(line, start);
        if (start == end)
            throw runtime_error("Error : missing bracket");
        this->configServers.push_back(line.substr(start, end - start + 1));
        this->nbServer++;
        start = end + 1;
    }
    
}
void ConfigFile::parseServer(string& line,Server& server)
{
    (void)server;

    stringstream ss(line);
    string token;
    bool serverName = false;
    ss >> token;
    if (token != "{")
        throw runtime_error("Error : server directive not found");
    while (ss >> token)
    {
        if (token == "listen")
        {
            ss >> token;
            if (server.getPort().size() != 0)
                throw runtime_error("Error : multiple listen directive");
            server.setPort(token);
        }
        else if (token == "server_name")
        {
            if (server.getServerName() != "")
                throw runtime_error("Error : multiple server_name directive");
            ss >> token;
            server.setServerName(token);
            serverName = true;
        }
        else if (token == "client_max_body_size")
        {
            if (server.getBodySize() != 0)
                throw runtime_error("Error : multiple client_max_body_size directive");
            ss >> token;
            server.setBodySize(token);

        }
        else if (token == "autoindex")
        {
            ss >> token;
            server.setAutoIndex(token);
        }
        else if (token == "location")
        {
            ss >> token;
            if (token == "{")
                throw runtime_error("Error : location directive not found");
            string locationPath;
            locationPath = token;
            vector<string> locationDirectives;
            ss >> token;
            while (token != "}")
            {
                locationDirectives.push_back(token);
                ss >> token;
            }
            server.setLocationContexts(locationPath, locationDirectives);
            if (token != "}")
                throw runtime_error("Error : missing bracket");
        }
        else if (token == "root")
        {
            ss >> token;
            server.setRoot(token);
        }
        else if (token == "index")
        {
            ss >> token;
            while (ss >> token)
            {
                if (token.back() == ';')
                {
                    token.pop_back();
                    server.setIndex(token);
                    break ;
                }
                server.setIndex(token);
            }
            server.setIndex(token);
        }
        else if (token == "allow")
        {
            stringstream allow; 
            while (ss >> token)
            {
                if (token.back() == ';')
                {
                    token.pop_back();
                    allow << token;
                    server.setAllowMethodes(allow);
                    break ;
                }
                allow << token << " ";
            }
        }
        else if (token == "error_page")
        {
            server.setErrorPage(ss);
        }
        else if (token == "{" || token == "server")
            throw runtime_error("Error : unknown directive");
    }
    if (!serverName)
        throw runtime_error("Error : at least one server_name directive is required");
}
void ConfigFile::parse()
{
    string line;
    string config;
    getline(this->file, line, '\0');
    if (line.size() == 0)
        throw runtime_error("Error : empty file");
    skipComments(line);
    skipwhitespaces(line);
    ServerContextToSplite(line);
    if (this->configServers.size() != this->nbServer)
        throw runtime_error("Error : in size of configServers");
    size_t i = 0;
    while (i < nbServer)
    {
        Server srv;
        parseServer(this->configServers[i], srv);
        this->servers.push_back(srv);
        i++;
    }
}