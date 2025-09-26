override SRCSDIR := srcs/
override MAINDIR := 
override PARSERDIR := parsing/
override UTILSDIR := utils/
override DEBUGDIR := debug/

SRC += $(addprefix $(MAINDIR), $(addsuffix .c, $(MAIN)))
SRC += $(addprefix $(PARSERDIR), $(addsuffix .c, $(PARSERSRC)))
SRC += $(addprefix $(UTILSDIR), $(addsuffix .c, $(UTILSSRC)))
SRC += $(addprefix $(DEBUGDIR), $(addsuffix .c, $(DEBUGSRC)))


override SRCS		= $(addprefix $(SRCSDIR), $(SRC))


override MAIN := main

override PARSERSRC := parsing \
					  parsing_collect_elements \
					  parsing_rgb \
					  parsing_texture \
            		  map_check \
            		  map_collect \
            		  parsing_map \

override UTILSSRC := element_check_utils \
					 error \
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
					 get_the_map_utils

override DEBUGSRC := print_struct_set