#ifndef WASM_SDL2_H
# define WASM_SDL2_H

#if __EMSCRIPTEN__
# include           <emscripten/emscripten.h>
#endif

# include           "stdlib.h"
# include           "stdio.h"
# include           <SDL2/SDL.h>
# include           <SDL2/SDL_ttf.h>
# include           <SDL2/SDL_image.h>

typedef					struct s_view t_view;

double      			time_ms_double(void);
void    				prepare_gpu(t_view *view);
void    				update_gpu(t_view *view);
void				    quit_cleanly(int code);
void				    quit_error(const char *error);
void				    quit_error_code(const char *error, int code);

#endif