NAME        = minishell

LIBS        := ft readline
LIBS_TARGET := libft/libft.a
READLINE_DIR := /opt/homebrew/opt/readline

INCS        := include libft/include $(READLINE_DIR)/include

SRC_DIR     := src
SRCS        := 							\
		src/main.c						\
		src/signals/signals.c			\
		src/utils/get_data.c			\
		src/utils/free.c				\
		src/utils/termios.c				\
		src/utils/tabs.c				\
		src/utils/utils1.c				\
		src/env/init_env.c				\
		src/builtins/builtins.c			\
		src/builtins/cd.c				\
		src/builtins/echo.c				\
		src/builtins/pwd.c				\
		src/builtins/env.c				\
		src/builtins/export_utils.c		\
		src/builtins/export.c			\
		src/builtins/unset.c			\
		src/builtins/exit.c				\
		src/tokenizer/tokenizer.c		\
		src/tokenizer/tokenizer_utils.c	\
		src/parsing/parser.c			\

BUILD_DIR   := .build
OBJS        := $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

CC          := gcc
CFLAGS      := -Wall -Wextra -Werror -fsanitize=address -g3
CPPFLAGS    := $(addprefix -I,$(INCS))
# -------  GARDER POUR ECOLE ------- 
LDLIBS		:= -lreadline -L ${HOME}/.brew/opt/readline/lib -I ${HOME}/.brew/opt/readline/include -Llibft -lft
# -------  GARDER POUR ECOLE -------
# LDLIBS      := -lreadline -L$(READLINE_DIR)/lib -I $(READLINE_DIR)/include -Wl,-rpath,$(READLINE_DIR)/lib -Llibft -lft

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