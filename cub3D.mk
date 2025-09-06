override SRCSDIR := srcs/
override MAINDIR := 
override PARSERDIR := parsing/

SRC += $(addprefix $(MAINDIR), $(addsuffix .c, $(MAIN)))
SRC += $(addprefix $(PARSERDIR), $(addsuffix .c, $(PARSERSRC)))

override SRCS		= $(addprefix $(SRCSDIR), $(SRC))


override MAIN := main


override PARSERSRC := parsing