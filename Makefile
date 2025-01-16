# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/07 20:13:23 by rbaticle          #+#    #+#              #
#    Updated: 2025/01/16 12:31:26 by rbaticle         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CL = client
SRV = server
CLB = client_bonus
SRVB = server_bonus
CC = cc
CFLAGS = -Wall -Werror -Wextra

LFT_DIR = ./libft/
LFT = $(LFT_DIR)libft.a

INCLUDES = ./includes/
HEADERS_FILES = minitalk.h
HEADERS = $(addprefix $(INCLUDES), $(HEADERS_FILES))

SRC_DIR = ./srcs/
SRC_FILES_SRV = server.c utils.c
SRC_FILES_CL = client.c
SRCS_SRV = $(addprefix $(SRC_DIR), $(SRC_FILES_SRV))
SRCS_CL = $(addprefix $(SRC_DIR), $(SRC_FILES_CL))
OBJS_SRV = $(SRCS_SRV:.c=.o)
OBJS_CL = $(SRCS_CL:.c=.o)
SRCS_SRV_BONUS = ./srcs/server_bonus.c ./srcs/utils.c
SRCS_CL_BONUS = ./srcs/client_bonus.c
OBJS_SRV_BONUS = ./srcs/server_bonus.o ./srcs/utils.o
OBJS_CL_BONUS = ./srcs/client_bonus.o

all: $(CL) $(SRV)

$(CL): $(LFT) $(OBJS_CL)
	$(CC) $(CFLAGS) $(OBJS_CL) -L $(LFT_DIR) -lft -I $(INCLUDES) -o $(CL)

$(SRV): $(LFT) $(OBJS_SRV)
	$(CC) $(CFLAGS) $(OBJS_SRV) -L $(LFT_DIR) -lft -I $(INCLUDES) -o $(SRV)

$(CLB): $(LFT) $(OBJS_CL_BONUS)
	$(CC) $(CFLAGS) $(OBJS_CL_BONUS) -L $(LFT_DIR) -lft -I $(INCLUDES) -o $(CLB)

$(SRVB): $(LFT) $(OBJS_SRV_BONUS)
	$(CC) $(CFLAGS) $(OBJS_SRV_BONUS) -L $(LFT_DIR) -lft -I $(INCLUDES) -o $(SRVB)

bonus: $(CLB) $(SRVB)

$(LFT):
	@make printf -C $(LFT_DIR)

fsanitize: $(LFT)
	$(CC) -g -fsanitize=address $(CFLAGS) $(SRCS_SRV) -L $(LFT_DIR) -lft -I $(INCLUDES) -o $(SRV)
	$(CC) -g -fsanitize=address $(CFLAGS) $(SRCS_CL) -L $(LFT_DIR) -lft -I $(INCLUDES) -o $(CL)
	$(CC) -g -fsanitize=address $(CFLAGS) $(SRCS_SRV_BONUS) -L $(LFT_DIR) -lft -I $(INCLUDES) -o $(SRVB)
	$(CC) -g -fsanitize=address $(CFLAGS) $(SRCS_CL_BONUS) -L $(LFT_DIR) -lft -I $(INCLUDES) -o $(CLB)

debug: $(LFT)
	$(CC) -g $(CFLAGS) $(SRCS_SRV) -L $(LFT_DIR) -lft -I $(INCLUDES) -o $(SRV)
	$(CC) -g $(CFLAGS) $(SRCS_CL) -L $(LFT_DIR) -lft -I $(INCLUDES) -o $(CL)
	$(CC) -g $(CFLAGS) $(SRCS_SRV_BONUS) -L $(LFT_DIR) -lft -I $(INCLUDES) -o $(SRVB)
	$(CC) -g $(CFLAGS) $(SRCS_CL_BONUS) -L $(LFT_DIR) -lft -I $(INCLUDES) -o $(CLB)

clean:
	@make clean -C $(LFT_DIR)
	rm -fr $(OBJS_SRV) $(OBJS_CL) $(OBJS_CL_BONUS) $(OBJS_SRV_BONUS)

fclean: clean
	@make fclean -C $(LFT_DIR)
	rm -fr $(CL) $(SRV) $(CLB) $(SRVB)

re: fclean all

.PHONY: clean fclean re
