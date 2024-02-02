/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerDirectives.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 23:35:38 by asabri            #+#    #+#             */
/*   Updated: 2024/02/02 17:29:06 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ServerDirectives.hpp"
#include <sys/stat.h>

ServerDirectives::ServerDirectives()
{
    this->bodySize = 0;
    this->root = "";
    this->autoIndex = false;
}
size_t ServerDirectives::getBodySize(){return (this->bodySize);}
bool ServerDirectives::getAutoIndex(){return (this->autoIndex);}
string ServerDirectives::getRoot(){return (this->root);}
vector<string> ServerDirectives::getIndex(){return (this->index);}


void ServerDirectives::setErrorPage(stringstream& errorPage)
{
    short error_code;
    string path;
    string temp;
    while (errorPage >> temp)
    {
        for (size_t i = 0; i < temp.size(); i++){
            if (!isdigit(temp[i]))
                throw runtime_error("Error: wrong error page format");
        }
        if (temp.size() != 3)
            throw runtime_error("Error: wrong error page format");
        error_code = atoi(temp.c_str());
        if (error_code < 100 || error_code > 599)
            throw runtime_error("Error: wrong error code");
        errorPage >> path;
        if (path.back() != ';' || path.size() < 2)
            throw runtime_error("Error: missing semicolon212121");
        path.pop_back();
        //TODO: check if path exists
        
        this->errorPage.insert(pair<short,string>(error_code,path));
        break;
    }
    
}

void ServerDirectives::setAllowMethodes(stringstream& allowMethodes)
{
    string token;
    int get;
    int post;
    int dlt;
    get = post = dlt = 0;
    while (allowMethodes >> token)
    {
        if (token != "GET" && token != "POST" && token != "DELETE")
            throw runtime_error("Error: wrong methodes");
        if (token.back() == ';')
        {
            token.pop_back();
            this->allowMethodes.push_back(token);
            break ;
        }
        this->allowMethodes.push_back(token);
    }
    for (size_t i = 0; i < this->allowMethodes.size(); i++)
    {
        if (this->allowMethodes[i] == "GET")
            get++;
        else if (this->allowMethodes[i] == "POST")
            post++;
        else if (this->allowMethodes[i] == "DELETE")
            dlt++;
    }
    if (get > 1 || post > 1 || dlt > 1)
        throw runtime_error("Error: duplicate methodes");
}
void ServerDirectives::setIndex(string index)
{
    this->index.push_back(index);
}
void ServerDirectives::setRoot(string root)
{
    if (root.back() != ';')
        throw runtime_error("Error: missing semicolon666");
    root.pop_back();
    struct stat buffer;
    if (stat(root.c_str(), &buffer) == 0)
        throw runtime_error("Error: wrong root path");
    this->root = root;
}
void ServerDirectives::setAutoIndex(string autoIndex)
{
    if (autoIndex.back() != ';')
        throw runtime_error("Error: missing semicolon3");
    autoIndex.pop_back();
    if (autoIndex == "on")
        this->autoIndex = true;
    else if (autoIndex == "off")
        this->autoIndex = false;
    else
        throw runtime_error("Error: wrong autoindex format");
}
void ServerDirectives::setBodySize(string bodySize)
{
    if (bodySize.back() != ';')
        throw runtime_error("Error: missing semicolon5");
    bodySize.pop_back();
    int isNumber = ((bodySize.back() == 'B') * 1 ) +
                    ((bodySize.back() == 'K') * 2 ) +
                    ((bodySize.back() == 'M') * 3)  +
                    ((bodySize.back() == 'G') * 4);
    if (isNumber == 0)
        throw runtime_error("Error: wrong body size format");
    bodySize.pop_back();
    this->bodySize = atoi(bodySize.c_str());
    if (isNumber == 2)
        this->bodySize *= pow(1024, isNumber - 1);
    else if (isNumber == 3)
        this->bodySize *= pow(1024, isNumber - 1);
    else if (isNumber == 4)
        this->bodySize *= pow(1024, isNumber - 1);
}
