# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asabri <asabri@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/31 04:38:17 by asabri            #+#    #+#              #
#    Updated: 2024/02/02 07:09:59 by asabri           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = webserv
CC              = c++
FLAGS           = -Wall -Wextra -Werror -std=c++98
OBJDIR          = .obj
FILES           = src/main src/ConfigFile src/Server src/ServerDirectives src/LocationContext
SRC             = $(FILES:=.cpp)
OBJ             = $(addprefix $(OBJDIR)/, $(FILES:=.o))
HEADER          = inc/ConfigFile.hpp inc/Server.hpp inc/ServerDirectives.hpp  inc/LocationContext.hpp

all: $(NAME)

$(NAME):$(OBJ) $(HEADER)
		$(CC) $(OBJ) -o $(NAME)


$(OBJDIR)/%.o: %.cpp $(HEADER)
		mkdir -p $(dir $@)
		$(CC) $(FLAGS) -c $< -o $@


clean:
		rm -rf $(OBJDIR) $(OBJ)


fclean: clean
		rm -rf  $(NAME)


re: fclean all
.PHONY: all clean fclean re