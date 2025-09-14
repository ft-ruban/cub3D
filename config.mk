NAME            := cub3D
EXEC            := bin/$(NAME)
OBJS_DIR        := .objs/
EXEC_DIR        := bin/

CC              := cc
MAKE            := make
RM              := rm -f
RM_DIR          := rm -rf

CFLAGS          := -Wall -Wextra -Werror -g3
CPPFLAGS		:= -I $(MLX_DIR)/
INC             := -I./include
INCLUDE         := include/
MLXFLAGS	  	:=	-lX11 -lXext

PURPLE          := \033[1;35m
GREEN           := \033[1;32m
RED             := \033[1;31m
YELLOW          := \033[33m
BOLD_UNDERLINE  := \033[1;4m
RESET           := \033[0m