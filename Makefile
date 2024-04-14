# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rileone <rileone@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/16 15:17:14 by rileone           #+#    #+#              #
#    Updated: 2024/04/14 12:49:00 by rileone          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
LIBFT_DIR = ./libft
PRINTF_DIR = ./libft/printf
GNL_DIR = ./libft/gnl
SRCDIR = ./src
INCLUDES = ./includes
HELPERS = $(SRCDIR)/helpers
EVERY_INCLUDES=-I. -I$(LIBFT_DIR) -I$(PRINTF_DIR) -I$(GNL_DIR) -I$(INCLUDES)

RM = rm -f
CC = cc
CFLAGS = -Wall -Wextra -Werror -g 
COMPILE = $(CC) $(CFLAGS)
ARCHIVE = ar rcs

SRC =	$(addprefix $(SRCDIR)/, main.c) \
		$(addprefix $(HELPERS)/, ft_init_room.c helpers.c) \


OBJ = ${SRC:.c=.o}


all: $(NAME)

$(NAME): $(OBJ)
	@$(MAKE) -C $(LIBFT_DIR)
	@$(COMPILE) $(CFLAGS) -I. -I$(EVERY_INCLUDES) $(OBJ) -L$(INCLUDES) -L$(LIBFT_DIR) -lft -L$(GNL_DIR) -lgnl -L$(PRINTF_DIR) -lftprintf -pthread -o $(NAME) 


clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(RM) $(OBJ)

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@$(RM) $(NAME)

VALGRIND = valgrind --leak-check=full --show-leak-kinds=all -s

valgrind: all
	$(VALGRIND) ./$(NAME) "2" "200" "200" "200" "200"

GDB = gdb 

gdb: all
	$(GDB) ./$(NAME)


re: fclean all

.PHONY: all clean fclean re