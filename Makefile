# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: msuter <msuter@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/15 11:05:43 by msuter            #+#    #+#              #
#    Updated: 2026/06/09 16:01:48 by msuter           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror -Ilibft
LFLAGS = -lreadline -lncurses

LEXER_SRCS = all_lexer/count_token.c all_lexer/lexer.c all_lexer/utils_lexer.c \
				all_lexer/each_case/case_in_or_hapend.c all_lexer/each_case/case_word.c \

PARSER_SRCS = all_parser/chained_list/redir_chained.c \
				all_parser/chained_list/t_parser_chained.c \
				all_parser/parser.c all_parser/utils_parser.c

EXPANDER_SRCS = all_expander/expander.c all_expander/filter_dup.c \
					all_expander/utils_expander.c all_expander/utils_var.c

EXEC_SRCS = all_exec/exec_cmd.c all_exec/exec_heredoc.c all_exec/exec_redir.c \
				all_exec/exec_utils.c all_exec/path_cmd.c all_exec/free.c all_exec/sigint.c\
				all_exec/utils_heredoc.c

BUILTIN_SRCS = builtin/builtin_utils.c builtin/builtin.c builtin/ft_cd.c builtin/ft_echo.c \
				builtin/ft_env.c builtin/ft_exit.c builtin/ft_export.c builtin/ft_pwd.c \
				builtin/ft_unset.c
				
MAIN_SRCS = main/main.c main/gestion_shlvl.c main/call.c main/syntaxe.c

SRCS = $(addprefix sources/, $(MAIN_SRCS)) $(addprefix sources/, $(LEXER_SRCS)) $(addprefix sources/, $(PARSER_SRCS))\
					$(addprefix sources/, $(EXEC_SRCS)) $(addprefix sources/, $(EXPANDER_SRCS))\
					$(addprefix sources/, $(BUILTIN_SRCS))

OBJS = $(addprefix objects/,  $(notdir $(SRCS:.c=.o)))

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

INCLUDES = -I. -I$(LIBFT_DIR)

all: $(LIBFT) $(NAME)
	clear

dir:
	mkdir -p objects

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): dir $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LFLAGS) -o $(NAME)

VPATH = $(shell find sources/ -type d)

objects/%.o : %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

val: $(NAME)
	valgrind --suppressions=readline.supp --leak-check=full --show-leak-kinds=all --track-fds=all ./minishell

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -rf objects
	clear

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean
	clear

re: fclean all