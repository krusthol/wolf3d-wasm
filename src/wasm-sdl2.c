#include "wolf3d.h"

double      			time_ms_double(void)
{
#ifdef __EMSCRIPTEN__
	return emscripten_get_now();
#else
	return (double)SDL_GetTicks();
#endif
}

void    				prepare_gpu(t_view *view)
{
	if (SDL_MUSTLOCK(view->surf))
		SDL_LockSurface(view->surf);
}

void    				update_gpu(t_view *view)
{
	if (SDL_MUSTLOCK(view->surf))
		SDL_UnlockSurface(view->surf);
	view->tex = SDL_CreateTextureFromSurface(view->ren, view->surf);
	SDL_RenderCopy(view->ren, view->tex, NULL, NULL);
	SDL_RenderPresent(view->ren);
	SDL_DestroyTexture(view->tex);
}

void					quit_cleanly(int code)
{
    SDL_Quit();
    exit(code);
}

void					quit_error(const char *error)
{
	printf("%s\n", error);
	quit_cleanly(1);
}

void					quit_error_code(const char *error, int code)
{
	printf("%s\n", error);
	quit_cleanly(code);
}