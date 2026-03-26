NAME=./solve_maze
SRCS_DIR=./srcs
OBJS_DIR=./objs
INCS_DIR=./includes

SRCS=$(wildcard $(SRCS_DIR)/*.c)
OBJS=$(subst $(SRCS_DIR),$(OBJS_DIR),$(SRCS:.c=.o))

DIRECTION="{ UP, DOWN, LEFT, RIGHT }"
CFLAGS=-I$(INCS_DIR) -DDIRECTION=$(DIRECTION) -DDIRECTION_STR='$(DIRECTION)'
RM=rm -rf

all: $(NAME)

$(NAME): $(OBJS_DIR) $(OBJS)
	echo $(SRCS)
	$(LINK.c) $(OBJS) -o $@

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	$(COMPILE.c) $< -o $@

clean:
	$(RM) $(OBJS_DIR)

fclean:
	$(MAKE) clean
	$(RM) $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: all clean fclean re
