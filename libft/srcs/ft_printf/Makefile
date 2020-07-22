# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: guaubret <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/16 19:31:47 by guaubret          #+#    #+#              #
#    Updated: 2019/08/21 19:08:42 by guaubret         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libftprintf.a

CC		=	gcc

CFLAGS	=	-Wall -Werror -Wextra

DFLAG	=	-g

INCLUDES	=	../includes

S_DIR	=	src

O_DIR	=	obj

SRC		=	arg.c \
			char.c \
			float.c \
			xprintf.c \
			int.c \
			misc.c \
			misc2.c \
			read.c \
			uint.c \
			colors.c

OBJ		=	$(SRC:.c=.o)

SRCS	=	$(addprefix $(S_DIR)/,$(SRC))

OBJS	=	$(addprefix $(O_DIR)/,$(OBJ))

all: $(NAME)

set_dflag:
	$(eval CFLAGS += $(DFLAG))

$(O_DIR)/%.o: $(S_DIR)/%.c
	$(CC) $(CFLAGS) -c $? -I$(INCLUDES) -o $@

$(NAME): $(OBJS)
	ar -rc $(NAME) $(OBJS)
	ranlib $(NAME)

debug : set_dflag $(OBJS)
	ar -rc $(NAME) $(OBJS)
	ranlib $(NAME)

clean:
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY: clean fclean re all
