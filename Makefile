
#= Vars =#

NAME = cub3D
SRCS :=	main.c \
		parser/parsing.c \
		parser/map_parse.c \
		parser/map_checks.c \

SRCSDIR = srcs
OBJDIR = obj
OBJ := $(addprefix $(OBJDIR)/,$(SRCS:.c=.o))
CFLAGS := #-Wall -Werror -Wextra -g
LIBMLX := ./libs/MLX42
LIBFT := ./libs/libft
LIBS :=  -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit $(LIBMLX)/libmlx42.a $(LIBFT)/libft.a
INCLUDES := -I includes/ -I libs/mlx42/include/MLX42/ -I $(LIBFT)

#= COLORS =#

GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

#= Targets=#

all: $(NAME)

libft:
	@echo "$(GREEN)Building LIBFT ...$(RESET)"
	@$(MAKE) -C $(LIBFT) WITH_BONUS=1

mlx:
	@echo "$(GREEN)Building MLX ...$(RESET)"
	@$(MAKE) -C $(LIBMLX) DEBUG=1

$(NAME): $(OBJDIR) $(OBJ)
	@$(CC) $(OBJ) $(LIBS) $(INCLUDES) -o $(NAME)
	@echo "$(GREEN)Building cub3D ...$(RESET)"

$(OBJDIR)/%.o: $(addprefix $(SRCSDIR)/, %.c)
	@$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@

$(OBJDIR):
	@mkdir -p $(OBJDIR)
	@mkdir -p $(OBJDIR)/parser

clean:
	@echo "$(RED)Cleaning $< $(RESET)"
	@$(MAKE) -C $(LIBFT) clean
	@rm -rf $(OBJDIR)

fclean: clean
	@rm -rf $(NAME) $(OBJDIR)

re: fclean all

.DEFAULT_GOAL := all
.PHONY: all clean fclean re