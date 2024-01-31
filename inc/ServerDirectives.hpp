/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerDirectives.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 03:49:09 by asabri            #+#    #+#             */
/*   Updated: 2024/01/31 04:11:03 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <vector>
#include <utility>
using namespace std;

struct AllowMethodes{
    bool Get;
    bool Post;
    bool Delete;    
};

class ServerDirectives 
{
    protected :
        size_t  bodySize;
        string  root;
        bool  autoIndex;
        vector<AllowMethodes> allowMethodes;
        vector<string>  index;
        pair<int,string> errorPage;
    public :
        void getBodySize();
        void getRoot();
        void getAutoIndex();
        void getAllowMethodes();
        void getIndex();
        void getErrorPage();
        void setBodySize(size_t bodySize);
        void setRoot(string root);
        void setAutoIndex(bool autoIndex);
        void setAllowMethodes(vector<AllowMethodes> allowMethodes);
        void setIndex(vector<string> index);
        void setErrorPage(pair<int,string> errorPage);
        
        
        
    
};