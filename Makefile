##
## EPITECH PROJECT, 2023
## Makfile
## File description:
## make
##

NAME	=	42sh

SRCS 	=	srcs/main.c \
			srcs/concat_env.c \
			srcs/my_change_directory.c \
			srcs/execute_prog.c \
			srcs/env.c \
			srcs/get_inputs.c \
			srcs/sys_or_builtin.c \
			srcs/my_echo.c \
			srcs/create_tree.c \
			srcs/execute_tree.c \
			srcs/delete_tree.c \
			srcs/valid_tree.c \
			srcs/execute_separators.c \
			srcs/alias.c \
			srcs/alias_unset.c \
			srcs/alias_disp.c \
			srcs/exec_alias.c \
			srcs/print_pwd.c \
			srcs/history.c \
			srcs/local_variables.c	\

SRCS_DEBUG	=	$(wildcard srcs/*.c) \
				$(wildcard lib/clib/*.c) \
				$(wildcard lib/linked_lists/*.c) \

NAME_TESTS	=	unit_tests

TEST_SRCS	=	tests/tests.c

OBJS	=	$(SRCS:.c=.o)

CFLAGS	=	-Werror -Wextra

LIBS	=	-L./lib -lclib -L./lib -llinked_lists

all: $(NAME)

$(NAME):	$(OBJS)
	@$(MAKE) -C lib/clib -f Makefile
	@$(MAKE) -C lib/linked_lists -f Makefile
	@$(CC) -o $(NAME) $(OBJS) $(LIBS)

clean:
	@$(MAKE) -C lib/clib -f Makefile clean
	@$(MAKE) -C lib/linked_lists -f Makefile clean
	@$(RM) $(OBJS)
	@$(RM) *~

fclean: clean
	@$(MAKE) -C lib/clib -f Makefile fclean
	@$(MAKE) -C lib/linked_lists -f Makefile fclean
	@$(RM) $(NAME)
	@$(RM) $(NAME_TESTS)
	@$(RM) debug

re: fclean all

test: re
	@$(CC) -o $(NAME_TESTS) $(TEST_SRCS) $(LIBS) $(CFLAGS)

debug: re
	@$(CC) -o debug $(SRCS_DEBUG) $(CFLAGS) -g3
