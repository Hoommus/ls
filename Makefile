# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vtarasiu <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/24 10:11:17 by vtarasiu          #+#    #+#              #
#    Updated: 2018/07/09 19:16:00 by vtarasiu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

FLAGS = -std=c99 -Wall -Wextra -Werror

HEADER = include
SRC_DIR = ./src/
OBJ_DIR = ./obj/

LIB_DIR = ./printf
LIB_NAME = libftprintf.a

LS_SRC = ft_ls.c errors.c modes.c print.c util.c traverse.c sorts.c lists.c \
         memory.c parsing.c

OBJ = $(addprefix $(OBJ_DIR), $(LS_SRC:.c=.o))

$(NAME): $(OBJ)
	make -C $(LIB_DIR)
	@mkdir -p $(OBJ_DIR)
	cp $(LIB_DIR)/$(LIB_NAME) ./$(LIB_NAME)
	gcc $(FLAGS) -o $(NAME) -g $(OBJ) -I $(HEADER) $(LIB_NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	gcc $(FLAGS) -I $(HEADER) -o $@ -c $<

all: $(NAME)

clean:
	make -C libft clean
	@echo "rm -rf $(OBJ_DIR)*.o"
	@/bin/rm -rf $(OBJ)
	/bin/rm -rf $(OBJ_DIR)

norme:
	norminette $(wildcard $(SRC_DIR)*.c)
	norminette $(HEADER)
	norminette $(wildcard $(LIB_DIR)/*.c)
	norminette $(wildcard $(LIB_DIR)/*.h)

fclean: clean
	make -C $(LIB_DIR) fclean
	/bin/rm -f $(NAME)

re: fclean all

check:
	gcc -c ft_*.c -std=c99 -Wall -Wextra -Werror && norminette ft_*.c *.h

love:
	@echo "Not all."

.PHONY: clean all fclean re check love norme