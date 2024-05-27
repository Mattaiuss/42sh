##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## base
##

NAME	=	liblinked_lists.a

SRCS	=	table.c \
			table_add_common.c \
			table_add_back.c \
			table_add_front.c \
			table_delete.c \
			table_functions.c \
			table_token_function.c \

OBJS	=	$(SRCS:.c=.o)

CFLAGS	=	-Werror  -Wextra -Wpedantic

all:	$(NAME)

$(NAME):	$(OBJS)
	@ar rc $(NAME) $(OBJS)
	@cp $(NAME) ../

clean:
	@$(RM) $(OBJS)
	@$(RM) *.log
	@$(RM) *~
	@$(RM) #*#
	@$(RM) *.o
	@$(RM) *.a
	@$(RM) *.out
	@$(RM) *.gcno
	@$(RM) *.gcda

fclean:	clean
	@$(RM) $(NAME)
	@$(RM) ../$(NAME)

re: fclean all
