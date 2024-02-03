/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LocationContext.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 04:13:45 by asabri            #+#    #+#             */
/*   Updated: 2024/02/03 15:38:50 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <vector>
#include <utility>
#include "ServerDirectives.hpp"
#include <map>
#include <sstream>
using namespace std;

class LocationContext : public ServerDirectives 
{
    private :
        string  path;
        map<string, string>   cgi;
        map<short,string>   redir;
    public :
        LocationContext();
        string getPath();
        map<string, string> getCgi();
        map<short,string> getRedir();
        void setPath(string path);
        void setRedirect(string redirect);
        void setCgi(stringstream& cgi);
        void setRedir(stringstream& redir);
        void checkLocationPath(string locationPath);
};