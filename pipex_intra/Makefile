# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marubio- <marubio-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/12 11:42:25 by marubio-          #+#    #+#              #
#    Updated: 2024/09/17 11:51:13 by marubio-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SRC		=  pipex.c  utils_pipex.c ft_split.c pipex_utils.c \

NAME 	= pipex

CC		= gcc

CFLAGS = -Wall -Werror -Wextra #-g3 -fsanitize=address

OBJS = $(SRC:.c=.o)

${NAME}: ${OBJS}
	$(CC) $(CFLAGS) ${OBJS}  -o ${NAME} 

all: ${NAME}

# debug: ${OBJS}
# 	@make -C ./libft
# 	$(CC) $(CFLAGS) $(LIB) ${OBJS}  -o ${NAME} -g3

clean:
	@rm -f ${OBJS} 

fclean: clean
	@rm -f $(NAME)
	
re: fclean all

.PHONY: all clean fclean re
