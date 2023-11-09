# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: whendrik <whendrik@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/30 16:08:21 by whendrik          #+#    #+#              #
#    Updated: 2023/11/09 17:52:13 by whendrik         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#FLAGS
CC = gcc
C_FLAGS = -Wall -Wextra -Werror -g -o3
S_FLAGS = -g -fsanitize=address,undefined

#commands
RM = rm -rf
AR = ar rc

#Targlib name and dirs
NAME = philo
SRC_DIR =src
SRC_FILES= main.c init.c mallocer.c routine.c utilities.c  

OBJ_DIR = obj
INC_DIR = includes
INCS = -I$(INC_DIR)

# Sources, objects and dependencies
SOURCES = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJECTS = $(SOURCES:$(SRC_DIR)%.c=$(OBJ_DIR)/%.o)

# Default target, build the library
all: $(NAME)

# Object file build rule
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(C_FLAGS) -c $< -o $@


$(NAME): $(OBJECTS) 
	$(CC) $^  $(INCS) -o $(NAME)

# Clean object files
clean:
	$(RM) $(OBJ_DIR)

# Clean object files and target library
fclean: clean
	$(RM) $(NAME)

re: fclean all

# Check code style
norm:
	@norminette -R CheckForbiddenSourceHeader $(SRC_DIR)/*.c ;
	@norminette -R CheckDefine $(INC_DIR)/*.h ;

# Phony targets
.PHONY: clean all fclean re norm
