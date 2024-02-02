/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LocationContext.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 05:36:35 by asabri            #+#    #+#             */
/*   Updated: 2024/02/02 17:30:47 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/LocationContext.hpp"

LocationContext::LocationContext()
{
    this->path = "";
    this->redirect = "";
}

string LocationContext::getPath(){return (this->path);}

void LocationContext::setPath(string path)
{
    this->path = path;
}

void LocationContext::setCgi(stringstream& cgi)
{
    string temp;
    string key;
    string value;

    while (cgi >> temp)
    {
        if (temp != ".php" && temp != ".py")
            throw runtime_error("Error: wrong cgi extension");
        key = temp;
        cgi >> value;
        if (value.back() != ';')
            throw runtime_error("Error: missing semicolon3333797");
        value.pop_back();
        this->cgi.insert(pair<string,string>(key,value));
        break;
    }
}

void LocationContext::setRedir(stringstream& redir)
{
    short redircode;
    string path;
    string temp;
    while (redir >> temp)
    {
        for (size_t i = 0; i < temp.size(); i++){
            if (!isdigit(temp[i]))
                throw runtime_error("Error: wrong redir format");
        }
        if (temp.size() != 3)
            throw runtime_error("Error: wrong redir format");
        redircode = atoi(temp.c_str());
        if (redircode < 100 || redircode > 599)
            throw runtime_error("Error: wrong redir code");
        redir >> path;
        if (path.back() != ';' || path.size() < 2)
            throw runtime_error("Error: missing semicolon baaaaa3");
        path.pop_back();
        //TODO: check if path exists
        this->redir.insert(pair<short,string>(redircode,path));
        break;
    }
}