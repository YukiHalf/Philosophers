NAME := philo

SRC_DIR := src
SRC := 	helper_func.c \
        monitor.c \
        routine.c \
        philo.c \
		special_case.c \
		utils.c

SRCS := $(addprefix $(SRC_DIR)/, $(SRC))
OBJ_DIR := obj
OBJ := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o, $(SRCS))

CC := cc
CFLAGS := -Wall -Wextra -Werror -g

all: $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(NAME): $(OBJ_DIR) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@ -pthread

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(SRC_DIR)/philo.h | $(OBJ_DIR)
	$(CC) -c $(CFLAGS) -I$(SRC_DIR) $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all
.PHONY: all clean fclean re
