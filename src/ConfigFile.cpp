/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigFile.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 07:39:34 by asabri            #+#    #+#             */
/*   Updated: 2024/02/01 05:10:26 by asabri           ###   ########.fr       */
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
    else
        cout << "File opened successfully" << endl;
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
    (void)server    ;
    stringstream ss(line);
    string config;
    while (ss >> config)
        cout << config << endl;
}
void ConfigFile::parse()
{
    string line;
    string config;
    getline(this->file, line, '\0');
    if (line.empty())
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
        // this->servers.push_back(srv);
        i++;
    }
    // if (nbServer > 1)
    //     checkServers();
    cout << "nbServer : " << this->nbServer << endl;
}