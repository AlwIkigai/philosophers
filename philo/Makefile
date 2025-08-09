# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asyed <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/25 18:54:24 by asyed             #+#    #+#              #
#    Updated: 2025/07/27 17:51:42 by asyed            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

FLAGS = -Wall -Wextra -Werror -g -pthread

INCLUDES = -Iincludes

SANITIZER_FLAGS = -fsanitize=thread

SANITIZER_ADDRESS = -fsanitize=address

RM = rm -rf

SRCSPATH = srcs/

SRCS = main_utils.c\
		philo.c \
		routine.c\
		main.c \
		validate_args.c \
		utils.c \
		print_utils.c\
		simulation.c\
		init_utils.c\
		monitor.c\
		test.c

OBJS = $(addprefix $(SRCSPATH), $(SRCS:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
	@cc $(FLAGS) $(OBJS) -o $(NAME)

$(SRCSPATH)%.o: $(SRCSPATH)%.c
	cc $(FLAGS) $(INCLUDES) -c $< -o $@

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.phony: all clean fclean re
