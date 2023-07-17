NAME        = minishell

LIBS        := ft readline
LIBS_TARGET := libft/libft.a
READLINE_DIR := $(HOME)/.brew/opt/readline

INCS        := include libft/include $(READLINE_DIR)/include

SRC_DIR     := src
SRCS        := src/main.c		\
		src/utils/get_data.c	\
		src/utils/free.c		\
		src/free/free_tree.c	\
		src/env/env.c			\
		src/builtins/test.c		\
		src/builtins/cd.c		\

BUILD_DIR   := .build
OBJS        := $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

CC          := gcc
CFLAGS      := -Wall -Wextra -Werror -fsanitize=address -g3
CPPFLAGS    := $(addprefix -I,$(INCS))
LDFLAGS     := -L$(READLINE_DIR)/lib
LDLIBS      := -lreadline -L$(READLINE_DIR)/lib -Wl,-rpath,$(READLINE_DIR)/lib -Llibft -lft

RM          := rm -rf
MAKEFLAGS   += --silent --no-print-directory
DIR_DUP     = mkdir -p $(@D)

all: $(NAME)

$(NAME): $(OBJS) $(LIBS_TARGET)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) $(LDLIBS) -o $(NAME)
	$(info CREATED $(NAME))

$(LIBS_TARGET):
	$(MAKE) -C libft

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(DIR_DUP)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<
	$(info CREATED $@)

clean:
	$(MAKE) -C libft clean
	$(RM) $(OBJS) $(BUILD_DIR)

fclean: clean
	$(MAKE) -C libft fclean
	$(RM) $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: all clean fclean re
.SILENT: