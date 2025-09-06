override SRCSDIR := srcs/
override MAIN := main
SRC += $(MAIN)
override SRCS := $(addprefix $(SRCSDIR), $(addsuffix .c, $(SRC)))