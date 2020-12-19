#include "wolf3d.h"

SDL_Window				*g_win;
SDL_Renderer			*g_ren;
SDL_Surface				*g_surf;
SDL_Texture				*g_tex;
Uint32					*g_pix;
int						g_pix_limit;
int						g_quit;
TTF_Font				*f_ibm;
SDL_Surface				*f_surf;
SDL_Color				color_white = {255, 255, 255, 255};
SDL_Event				event;

void					init_systems(void)
{
	if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_EVENTS) < 0)
        quit_error("Could not initialize SDL base systems");
	if (TTF_Init() != 0)
		quit_error("Could not initialize SDL_ttf extension");
	if (IMG_Init(IMG_INIT_PNG) == 0)
		quit_error("Could not initialize SDL_image extension");
    SDL_CreateWindowAndRenderer(640, 480, 0, &g_win, &g_ren);
    g_surf = SDL_CreateRGBSurface(0, 640, 480, 32, 0, 0, 0, 0);
	if (g_win == NULL || g_ren == NULL || g_surf == NULL)
		quit_error("Could not initialize window, surface and renderer.");
}

void					init_memory(void)
{
	f_ibm = TTF_OpenFont("assets/ibm_bios.ttf", 12);
	if (!f_ibm)
		quit_error("Fatal Error: TTF_OpenFont failed.");
	f_surf = TTF_RenderText_Solid(f_ibm, "Kimpsut ja Kampsut", color_white);
	if (!f_surf)
		quit_error("Fatal Error: TTF_RenderText_Solid failed.");
	g_pix = g_surf->pixels;
	g_pix_limit = (g_surf->h * g_surf->w);
 }

void					hello_kimkam(void)
{
	prepare_gpu();
	SDL_FillRect(g_surf, NULL, 0xff00ff00);
	SDL_BlitSurface(f_surf, NULL, g_surf, NULL);
	update_gpu();
}

void					main_loop(void)
{
	while (SDL_PollEvent(&event) != 0)
	{
		if (event.type == SDL_QUIT)
			g_quit = 1;
		hello_kimkam();
	}
}

int			main(int argc, char *argv[])
{
	//t_view	view;
	//int		not_file;
	//int		is_bad;

	if (argc == 1 && argv[0] != NULL)
	{
		init_systems();
		init_memory();
	}

#ifdef __EMSCRIPTEN__
	emscripten_set_main_loop(main_loop, 0, 1);
#else
	while (!g_quit)
		main_loop();
#endif
	SDL_Quit();
	return (0);
	/*
	view.g = &(view.grid);
	view.p = &(view.player);
	if (argc != 2)
		print_usage_and_exit(1);
	if ((not_file = open(argv[1], O_RDONLY | O_DIRECTORY, 0)) > 0)
		close_and_exit(not_file, MAP_DIRECTORY);
	is_bad = check_mapfile(argv[1], &view);
	if (!(is_bad))
		print_intro(argv[1]);
	else
		return (print_error(is_bad));
	initialize_view(&view, "wolf3d by [krusthol]");
	initialize_states(&view);
	cast_walls(-1, view.g, view.p, &view);
	mlx_loop_hook(view.mlx, calc_movements, &view);
	mlx_loop(view.mlx);
	return (0);
	 */
}