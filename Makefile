# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: krusthol <krusthol@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/03 16:09:47 by krusthol          #+#    #+#              #
#    Updated: 2020/02/26 03:35:27 by krusthol         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d
SRC = $(wildcard src/*.c)
SRC += $(wildcard src/ft_str/*.c)
OBJ = $(subst .c,.o,$(SRC))
CFLAGS = -Wall -Wextra -O3 -Iinclude
LIBS = -lSDL2 -lSDL2_ttf -lSDL2_image
LINUX_LINKS = -lm -lXext -lX11 -lpthread
ASSETS = assets
EM_TEMPLATE = html_template/minimal.html
EM_FLAGS = -s ALLOW_MEMORY_GROWTH=1 -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='["png"]' -s USE_SDL_TTF=2 --preload-file $(ASSETS)
EM_PROD = --shell-file $(EM_TEMPLATE)
EM_NAME = index.html
EM_OUT_DIR = out

all: $(NAME)

emcc: fclean
	-emmake make
	@emcc $(EM_FLAGS) $(OBJ) -o $(EM_OUT_DIR)/$(EM_NAME)

prod: fclean
	-emmake make
	@emcc $(EM_FLAGS) $(EM_PROD) $(OBJ) -o $(EM_OUT_DIR)/$(EM_NAME)

serve:
	python3 -m http.server & google-chrome-stable http://0.0.0.0:8000/$(EM_OUT_DIR)/$(EM_NAME)

web: emcc
	python3 -m http.server & google-chrome-stable http://0.0.0.0:8000/$(EM_OUT_DIR)/$(EM_NAME)

linux: fclean $(NAME)
	./wolf3d

$(NAME): $(OBJ)
	@gcc $(CFLAGS) $(OBJ) $(LIBS) -o $(NAME) $(LINUX_LINKS)
	@echo "$(MSG)Compiled for Linux!$(END)"

clean: 
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
	rm -f ./out/*

re: fclean web

.PHONY: all run clean fclean re
