NAME =	libgfx.a
FLAGS =	-Wall -Wextra -Werror -O3
CC = 	gcc
ODIR =	bin/
IDIR =
SRC =
OBJ =	$(SRC:.c=.o)
EXT =	$(IDIR)$(NAME:.a=.h)

EXT +=	Makefile

SRC	+=	matrix_math.c \
		transform_matrix.c \
		initializers.c \
		put_pixel.c \
		vector_math.c \
		vect_math2.c

O =		$(addprefix $(ODIR), $(OBJ))

MLXINC	= -I../minilibx
LFTINC	= -I../libft

all: $(NAME)

love: all

norm:
	norminette $(S)

$(NAME): $(O) $(EXT)
	@ar rc $(NAME) $(O)
	@ranlib $(NAME)

$(ODIR)%.o: %.c $(EXT)
	@echo "-> Compiling $<..."
	@$(CC) $(FLAGS) $(MLXINC) $(LFTINC) -c $< -o $@

$(O): | ./bin

./bin:
	@mkdir $(ODIR)

clean:
	@echo "-> Cleaning libgfx object files..."
	@rm -f bin/*.o

fclean: clean
	@echo "-> Cleaning $(NAME)..."
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re norm
