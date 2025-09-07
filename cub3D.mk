override SRCSDIR := srcs/
override MAINDIR := 
override PARSERDIR := parsing/
override UTILSDIR := utils/

SRC += $(addprefix $(MAINDIR), $(addsuffix .c, $(MAIN)))
SRC += $(addprefix $(PARSERDIR), $(addsuffix .c, $(PARSERSRC)))
SRC += $(addprefix $(UTILSDIR), $(addsuffix .c, $(UTILSSRC)))


override SRCS		= $(addprefix $(SRCSDIR), $(SRC))


override MAIN := main


override PARSERSRC := parsing \
					  parsing_file \
					  parsing_element \

override UTILSSRC := ft_strjoin \
					 ft_strlen