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
					  parsing_file \
					  parsing_rgb \
					  parsing_texture \
					  parsing_element \
					  parsing_map \

override UTILSSRC := ft_atoi \
					 ft_strjoin \
					 ft_strlen \
					 get_next_line \
					 get_next_line_utils

override DEBUGSRC := print_struct_set