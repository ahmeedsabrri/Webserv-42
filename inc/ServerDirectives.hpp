/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerDirectives.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 03:49:09 by asabri            #+#    #+#             */
/*   Updated: 2024/02/03 14:19:30 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <vector>
#include <utility>
#include <map>
#include <sstream>
#include <array>
using namespace std;


class ServerDirectives 
{
    protected :
        size_t  bodySize;
        string  root;
        bool  autoIndex;
        vector<string> allowMethodes;
        vector<string>  index;
        map<short,string> errorPage;
        
    public :
        array<string,11> __directives;
        ServerDirectives();
        size_t getBodySize();
        string getRoot();
        bool getAutoIndex();
        vector<string> getAllowMethodes();
        int validDirective(string token);
        vector<string> getIndex();
        map<short,string> getErrorPage();
        void setBodySize(string bodySize);
        void setRoot(string root);
        void setAutoIndex(string autoIndex);
        void setAllowMethodes(stringstream& allowMethodes);
        void setIndex(string index);
        void setErrorPage(stringstream& errorPage);
};