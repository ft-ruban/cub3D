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


override PARSERSRC := check_the_map \
					  get_the_map \
					  parsing_element \
					  parsing_file \
					  parsing_map \
					  parsing_rgb \
					  parsing_texture \
					  parsing \

override UTILSSRC := error \
					 free_map \
					 ft_atoi \
					 ft_isnum \
					 ft_strdup \
					 ft_strjoin \
					 ft_strlen \
					 get_next_line_utils \
					 get_next_line

override DEBUGSRC := print_struct_set