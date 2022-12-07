# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tberube- <tberube-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/08 09:52:10 by tberube-          #+#    #+#              #
#    Updated: 2022/12/07 11:36:27 by tberube-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Werror -Wextra -g #-fsanitize=thread
CC = gcc
HEADER = philo/

NAME = philo
SRCS = parsing.c philo.c init_philo.c get_time.c routine.c print_states.c \
		Boucle_main_check.c
# create_thread.c init_philo.c print_state.c

OBJS = ${SRCS:.c=.o}

$(NAME):	$(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

.c.o:
	${CC} $(CFLAGS) -I$(HEADER) -c $< -o $(<:.c=.o)

all:	$(NAME)

debug:	CFLAGS += -g
debug:	$(NAME)

clean:
	rm -f $(OBJS)

fclean:		clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
