# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/08/13 19:52:44 by vbrazas           #+#    #+#              #
#    Updated: 2019/02/05 17:03:29 by akupriia         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re mclean mfclean mre

NAME := corewar

SRC_PATH := src/
OP_PATH := $(SRC_PATH)operations/
V_PATH := $(SRC_PATH)visualizer/
INC_PATH := includes/
LIB_PATH := ../ft_printf/
OBJ_PATH := .obj/

CC := clang
CFLAGS := -g -Wall -Werror -Wextra
IFLAGS := -I $(INC_PATH) -I $(LIB_PATH)
LFLAGS := -lncurses

HFILES :=		vm op infargsop music ncurses typedefs
OPERATIONS :=	add aff and ld ldi lfork live lld lldi op_fork or st sti sub xor zjmp
FILES :=		vm errors utils args_parsing fill_the_map carriage carriage2 carriage_utils carriage_utils2 main_cycle_funcs
VISUALIZER :=	v_main v_init v_print v_widgets v_deinit v_print_stat v_music
LIB :=			$(LIB_PATH)libftprintf.a

HDRS := $(addprefix $(INC_PATH), $(addsuffix .h, $(HFILES)))
SRCS := $(addprefix $(SRC_PATH), $(addsuffix .c, $(FILES)))
SRCS += $(addprefix $(OP_PATH), $(addsuffix .c, $(OPERATIONS)))
SRCS += $(addprefix $(V_PATH), $(addsuffix .c, $(VISUALIZER)))
OBJS := $(addprefix $(OBJ_PATH), $(SRCS:%.c=%.o))


all: $(NAME)

$(NAME): $(LIB) $(OBJ_PATH) $(OBJS)
	@ sed -i "" -e 's|"afplay .*"|"afplay $(shell pwd)/music/"|g' src/visualizer/v_music.c
	$(CC) $(CFLAGS) $(IFLAGS) $(LFLAGS) $(OBJS) $(LIB) -o $(NAME)
$(LIB):
	make -C $(LIB_PATH)

$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)$(OP_PATH)
	mkdir -p $(OBJ_PATH)$(V_PATH)
$(OBJ_PATH)%.o: %.c $(HDRS)
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

clean: mclean
	make clean -C $(LIB_PATH)
fclean: mfclean
	make fclean -C $(LIB_PATH)
re: fclean all

mclean:
	rm -f $(OBJS) $(DEPS)
mfclean:
	rm -f $(NAME)
	rm -rf $(OBJ_PATH)
mre: mfclean all
