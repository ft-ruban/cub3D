override SRCSDIR := srcs/
override MAINDIR := 
override PARSERDIR := parsing/
override UTILSDIR := utils/
override DEBUGDIR := debug/
override MLX_DIR := minilibx-linux/
override MLXSETDIR := mlx/
override EXECDIR := exec/

SRC += $(addprefix $(MAINDIR), $(addsuffix .c, $(MAIN)))
SRC += $(addprefix $(PARSERDIR), $(addsuffix .c, $(PARSERSRC)))
SRC += $(addprefix $(UTILSDIR), $(addsuffix .c, $(UTILSSRC)))
SRC += $(addprefix $(DEBUGDIR), $(addsuffix .c, $(DEBUGSRC)))
SRC += $(addprefix $(MLXSETDIR), $(addsuffix .c, $(MLXSETSRC)))
SRC += $(addprefix $(EXECDIR), $(addsuffix .c, $(EXECSRC)))

#MLX_LIB := $(MLX_DIR)/libmlx.a

override SRCS		= $(addprefix $(SRCSDIR), $(SRC))


override MAIN := main \
				 main_utils

override PARSERSRC := parsing \
					  element_collect_parsing \
					  element_collect_utils \
					  element_rgb_parsing \
					  element_texture_parsing \
            map_check \
            map_collect \
            parsing_map \

override UTILSSRC := error \
					 find_map_size_utils \
					 free_map \
					 ft_atoi \
					 ft_bzero \
					 ft_isnum \
					 ft_strdup \
					 ft_strjoin \
					 ft_strlen \
					 get_next_line_utils \
					 get_next_line \
					 map_check_utils \
					 map_collect_utils

override DEBUGSRC := print_struct_set

override MLXSETSRC := commands \
					  mlx_utils \
					  texture \

override EXECSRC := draw_all_pixels \
					draw_column \
					draw_one_pixel \
					draw \
					exec \
					init_player_data \
					print_screen