# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/07 20:13:23 by rbaticle          #+#    #+#              #
#    Updated: 2025/01/08 12:09:31 by rbaticle         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CL = client
SRV = server
CC = cc
CFLAGS = -Wall -Werror -Wextra

LFT_DIR = ./libft/
LFT = $(LFT_DIR)libft.a

INCLUDES = ./includes/
HEADERS_FILES = minitalk.h
HEADERS = $(addprefix $(INCLUDES), $(HEADERS_FILES))

SRC_DIR = ./srcs/
SRC_FILES_SRV = server.c
SRC_FILES_CL = client.c
SRCS_SRV = $(addprefix $(SRC_DIR), $(SRC_FILES_SRV))
SRCS_CL = $(addprefix $(SRC_DIR), $(SRC_FILES_CL))
OBJS_SRV = $(SRCS_SRV:.c=.o)
OBJS_CL = $(SRCS_CL:.c=.o)

all: $(CL) $(SRV)

$(CL): $(LFT) $(OBJS_CL)
	$(CC) $(CFLAGS) $(OBJS_CL) -L $(LFT_DIR) -lft -I $(INCLUDES) -o $(CL)

$(SRV): $(LFT) $(OBJS_SRV)
	$(CC) $(CFLAGS) $(OBJS_SRV) -L $(LFT_DIR) -lft -I $(INCLUDES) -o $(SRV)

$(LFT):
	@make printf -C $(LFT_DIR)

clean:
	@make clean -C $(LFT_DIR)
	rm -fr $(OBJS_SRV) $(OBJS_CL)

fclean: clean
	@make fclean -C $(LFT_DIR)
	rm -fr $(CL) $(SRV)

re: fclean all

.PHONY: clean fclean re
