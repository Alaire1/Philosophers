# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akaraban <akaraban@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/13 17:34:54 by akaraban          #+#    #+#              #
#    Updated: 2023/09/21 03:10:02 by akaraban         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Color variables for text
CYAN = \033[0;96m
BLUE = \033[34m
YELLOW = \033[33m
ORANGE = \033[38;2;255;146;3m
RED = \033[38;2;255;0;0m
MAGENTA = \033[35m
GREEN = \033[38;2;0;255;0m
WHITE = \033[37m
BLACK = \033[30m
RESET = \033[0m

# Color variables of background
BG_RESET = \033[49m
BG_BLACK = \033[40m
BG_RED = \033[41m
BG_GREEN = \033[42m
BG_YELLOW = \033[43m
BG_BLUE = \033[44m
BG_MAGENTA = \033[45m
BG_CYAN = \033[46m
BG_WHITE = \033[47m

# Variables
NAME		=	philo
HEADER		=	./include/
CC			=	gcc
CFLAGS		=	-Werror -Wall -Wextra  -g -I $(HEADER) -pthread
SOURCE_DIR 	= 	srcs

SRCS		=	srcs/activity.c \
				srcs/args.c \
				srcs/init.c \
				srcs/main.c \
				srcs/philo.c \
				srcs/utils_libft.c \
				srcs/utils.c \

			
OBJECT_DIR = obj
OBJECT_FILES = $(patsubst $(SOURCE_DIR)/%.c, $(OBJECT_DIR)/%.o, $(SRCS))

# Rules
all: $(NAME)

$(NAME): $(OBJECT_FILES) $(HEADER)
	@echo "$(YELLOW)$$BANNER$(RESET)"
	@$(CC) $(CFLAGS) $(OBJECT_FILES) -o $(NAME)
	@echo "$(GREEN)✅ Compilation went succesfull$(RESET)"
	@echo "$(ORANGE)To run program, type: ./philo <number_of_philosophers> <time_to_die> \
	<time_of_eating> <time_of_sleeping> optional: <number_of_times_each_philosopher_must_eat>$(RESET)"

$(OBJECT_DIR)/%.o: $(SOURCE_DIR)/%.c | $(OBJECT_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@
	
$(OBJECT_DIR):
	@mkdir -p $(OBJECT_DIR)

clean:
	@rm -rf $(OBJECT_DIR)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re

define BANNER

--------------------------------------------------------------------------------------------------------------------
ooooooooo.   oooo         o8o  oooo                                          oooo                                    
`888   `Y88. `888         `"'  `888                                          `888                                    
 888   .d88'  888 .oo.   oooo   888   .ooooo.   .oooo.o  .ooooo.  oo.ooooo.   888 .oo.    .ooooo.  oooo d8b  .oooo.o 
 888ooo88P'   888P"Y88b  `888   888  d88' `88b d88(  "8 d88' `88b  888' `88b  888P"Y88b  d88' `88b `888""8P d88(  "8 
 888          888   888   888   888  888   888 `"Y88b.  888   888  888   888  888   888  888ooo888  888     `"Y88b.  
 888          888   888   888   888  888   888 o.  )88b 888   888  888   888  888   888  888    .o  888     o.  )88b 
o888o        o888o o888o o888o o888o `Y8bod8P' 8""888P' `Y8bod8P'  888bod8P' o888o o888o `Y8bod8P' d888b    8""888P' 
                                                                   888                                               
------------------------------------------------------------------o8888----------------------------------------------
endef
export BANNER                                                                                                                  