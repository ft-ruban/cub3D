.SILENT:
.PHONY: all init clean fclean re test FORCE

include config.mk
include cub3D.mk

OBJS :=	$(patsubst $(SRCSDIR)%.c, $(OBJS_DIR)%.o, $(SRCS))
DEPS := $(OBJS:.o=.d)

all: $(NAME)

$(NAME): Makefile $(OBJS) | $(EXEC_DIR)
	echo "$(PURPLE)Compiling $(NAME) in progress...$(RESET)"

		$(CC) $(CFLAGS) $(CPPFLAGS) -o $(EXEC) $(OBJS) $(RLFLAGS)

	echo "$(GREEN)$(EXEC) completed successfully!$(RESET)"

	echo "$(GREEN)"
	echo "┌───────────────────────────────────────────────────────────┐"
	echo "│      Compilation finished successfully! ᕕ(⌐■_■)ᕗ ♪♬       │"
	echo "└───────────────────────────────────────────────────────────┘"

	echo "$(GREEN) $(NAME) is now ready to run ／人◕ ‿‿ ◕人＼ "
	echo "$(RESET)"


$(OBJS_DIR)%.o: $(SRCSDIR)%.c | $(OBJS_DIR)
	mkdir -p $(dir $@)
	echo "$(PURPLE)Compiling $<...$(RESET)"

		$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

	echo "$(GREEN)$< completed successfully!$(RESET)"

$(OBJS_DIR):
	echo "$(YELLOW)Creating directory $(OBJS_DIR)...$(RESET)"
		
		mkdir -p $(OBJS_DIR)

$(EXEC_DIR):
	echo "$(YELLOW)Creating $(EXEC_DIR) directory...$(RESET)"

		mkdir -p $(EXEC_DIR)

clean:
	$(RM_DIR) $(OBJS_DIR)
	echo "$(RED)Cleaning of  and .d files completed successfully! ／人◕ ‿‿ ◕人＼$(RESET)"

fclean: clean
	$(RM_DIR) $(EXEC_DIR)
	echo "$(GREEN)"
	echo "┌──────────────────────────────────────────────────────────┐"
	echo "│      Deletion finished successfully! ( ◔ ω ◔) ノシ       │"
	echo "└──────────────────────────────────────────────────────────┘"
	echo "                           ╱|、"
	echo "                         (˚ˎ 。7"
	echo "                          |、˜|"
	echo "                         じしˍ,)ノ"
	echo "$(RESET)"

re: fclean all

FORCE:

-include $(DEPS)