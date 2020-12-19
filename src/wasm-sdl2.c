#include "wolf3d.h"

double      			time_now()
{
#ifdef __EMSCRIPTEN__
	return emscripten_get_now();
#else
	return (double)SDL_GetTicks();
#endif
}

void    				prepare_gpu(void)
{
	if (SDL_MUSTLOCK(g_surf))
		SDL_LockSurface(g_surf);
}

void    				update_gpu(void)
{
	if (SDL_MUSTLOCK(g_surf))
		SDL_UnlockSurface(g_surf);
	g_tex = SDL_CreateTextureFromSurface(g_ren, g_surf);
	SDL_RenderCopy(g_ren, g_tex, NULL, NULL);
	SDL_RenderPresent(g_ren);
	SDL_DestroyTexture(g_tex);
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