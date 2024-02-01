/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LocationContext.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 04:13:45 by asabri            #+#    #+#             */
/*   Updated: 2024/01/31 08:19:58 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <vector>
#include <utility>
#include "ServerDirectives.hpp"
using namespace std;

class LocationContext : public ServerDirectives 
{
    private :
        string  path;
        string  redirect;
        pair<string, string>   cgi;
    public :
        void getPath();
        void setLocationName(string locationName);
        void setPath(string path);
        void setRedirect(string redirect);
        void setCgi(pair<string, string> cgi);
};