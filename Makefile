# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: msuter <msuter@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/15 11:05:43 by msuter            #+#    #+#              #
#    Updated: 2026/03/20 16:20:24 by msuter           ###   ########.fr        #
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

SRCS = main.c $(LEXER_SRCS) $(PARSER_SRCS)

OBJS = $(SRCS:.c=.o)

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

INCLUDES = -I. -I$(LIBFT_DIR)

all: $(LIBFT) $(NAME)
	clear

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LFLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean
	clear

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean
	clear

re: fclean all