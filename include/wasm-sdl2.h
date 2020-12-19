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

double			    time_now();
void			    prepare_gpu(void);
void		    	update_gpu(void);
void			    quit_cleanly(int code);
void			    quit_error(const char *error);
void			    quit_error_code(const char *error, int code);

extern SDL_Window	*g_win;
extern SDL_Renderer	*g_ren;
extern SDL_Surface	*g_surf;
extern SDL_Texture	*g_tex;
extern Uint32		*g_pix;
extern int			g_pix_limit;
extern int			g_quit;
extern TTF_Font		*f_ibm;
extern SDL_Surface	*f_surf;
extern SDL_Color	color_white;
extern SDL_Event	event;

#endif