##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## base
##

NAME	=	libclib.a

SRCS	=	$(wildcard *.c)

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
