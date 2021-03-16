NAME = cube3d
PROJECT_NAME = cube3d

SOURCES_FOLDER = ./
INCLUDES_FOLDER = includes/libft
OBJECTS_FOLDER = ./

LIBS = libft

SOURCES = \
		./includes/gnl/get_next_line.c \
		./sources/parse/parser.c \
		./sources/parse/param.c \
		./sources/parse/color.c \
		./sources/parse/parse_map.c \
		./sources/parse/parse_utils.c \
		./sources/utils/error.c \
		./sources/utils/touch.c \
		./sources/utils/init.c \
		./sources/utils/utils.c \
		./sources/texture/texture_init.c \
		./sources/vector.c \
		./sources/bitmap.c \
		./sources/raycasting/raycast.c \
		./sources/raycasting/raycast_utils.c \
		./sources/sprite/sprite.c \
		./sources/sprite/sprite_utils.c \
		cube3d.c


OBJECTS = $(SOURCES:.c=.o)

FSANITIZE = -fsanitize=address
FLAGS = -fsanitize=address -g3
CC = clang

NO_COLOR =		\033[38;5;15m
OK_COLOR =		\033[38;5;2m
ERROR_COLOR =	\033[38;5;1m
WARN_COLOR =	\033[38;5;3m
SILENT_COLOR =	\033[38;5;245m
INFO_COLOR =	\033[38;5;140m

.PHONY: all re clean fclean libft force doclean

all: $(NAME)

$(LIBS):
	@printf "$(NO_COLOR)All objects for $(INFO_COLOR)$(PROJECT_NAME) $(NO_COLOR)where successfully created.\n"
	@printf "\n$(NO_COLOR)-------- $(INFO_COLOR)Libft $(NO_COLOR)--------\n"
	@make -C includes/$(@)
	@printf "$(NO_COLOR)-----------------------\n\n"

$(NAME): $(OBJECTS) $(LIBS)
	@$(CC) $(FLAGS) -I$(INCLUDES_FOLDER)  -o $(NAME)  -L includes/libft/ -lft $(OBJECTS) -L includes/minilibx/ -lmlx -framework OpenGL -framework Appkit
	@printf "$(INFO_COLOR)$(NAME) $(NO_COLOR)successfully compiled. $(OK_COLOR)✓$(NO_COLOR)\n"

force: $(OBJECTS)
	@printf "$(NO_COLOR)All objects for $(INFO_COLOR)$(PROJECT_NAME) $(NO_COLOR)where successfully created.\n"
	@$(CC) $(FLAGS) -I$(INCLUDES_FOLDER) -o $(NAME) $(OBJECTS) -L  libft/ -lft
	@printf "$(INFO_COLOR)$(NAME) $(NO_COLOR)successfully compiled. $(OK_COLOR)✓$(NO_COLOR)\n"

%.o: %.c
	@$(CC) $(FLAGS) -I$(INCLUDES_FOLDER) -c $< -o $@
	@printf "$(NO_COLOR)Creating $(INFO_COLOR)%-30s $(OK_COLOR)✓$(NO_COLOR)\r" "$@"

clean:
	@make -C includes/$(LIBS) clean
	@rm -f $(OBJECTS)
	@printf "$(INFO_COLOR)$(PROJECT_NAME) $(NO_COLOR)Removed all objects$(NO_COLOR).\n"

fclean: clean
	@make -C includes/$(LIBS) fclean
	@rm -f $(NAME)
	@printf "$(INFO_COLOR)$(PROJECT_NAME) $(NO_COLOR)Removed $(INFO_COLOR)$(NAME)$(NO_COLOR).\n"

doclean: all clean

re: fclean all
