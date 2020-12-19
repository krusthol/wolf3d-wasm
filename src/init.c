#include "wolf3d.h"

void					init_systems(t_view *v)
{
	if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_EVENTS) < 0)
		quit_error("Could not initialize SDL base systems");
	if (TTF_Init() != 0)
		quit_error("Could not initialize SDL_ttf extension");
	if (IMG_Init(IMG_INIT_PNG) == 0)
		quit_error("Could not initialize SDL_image extension");
	SDL_CreateWindowAndRenderer(1280, 800, 0, &v->win, &v->ren);
	v->surf = SDL_CreateRGBSurface(0, 1280, 800, 32, 0, 0, 0, 0);
	if (v->win == NULL || v->ren == NULL || v->surf == NULL)
		quit_error("Could not initialize window, surface and renderer.");
}

void					init_memory(t_view *v)
{
	v->ibm_font = TTF_OpenFont("assets/ibm_bios.ttf", 12);
	if (!v->ibm_font)
		quit_error("Fatal Error: TTF_OpenFont failed.");
	v->font_surf = TTF_RenderText_Solid(v->ibm_font, "Kimpsut ja Kampsut", v->color_white);
	if (!v->font_surf)
		quit_error("Fatal Error: TTF_RenderText_Solid failed.");
	v->pix = v->surf->pixels;
	v->pix_limit = (v->surf->h * v->surf->w);
}

void		populate_color_tables(unsigned int wall_colors[600])
{
	int i;

	i = -1;
	while (i++ < 599)
	{
		if (i < 100)
			wall_colors[i] = color(i, 0x00FFFF);
		else if (i < 200)
			wall_colors[i] = color(i - 100, 0xFF0000);
		else if (i < 300)
			wall_colors[i] = color(i - 200, 0xFF00FF);
		else if (i < 400)
			wall_colors[i] = color(i - 300, 0xFFFF00);
		else if (i < 500)
			wall_colors[i] = color(i - 400, 0x484848);
		else if (i < 600)
			wall_colors[i] = color(i - 500, 0x888888);
	}
}

void		populate_doubles_tables(long double rads360[360], long double
rads7680[7680], long double tans7680[7680], long double fisheye1280[1280])
{
	int i;

	rads360[0] = 0.000001;
	rads7680[0] = 0.000001;
	tans7680[0] = 0.000001;
	i = 1;
	while (i < 360)
	{
		rads360[i] = i * (M_PI / 180.0);
		i++;
	}
	i = 1;
	while (i < 7680)
	{
		rads7680[i] = (i * (M_PI / 180.0)) / 21.3333333333333333333;
		tans7680[i] = tanl(rads7680[i]);
		i++;
	}
	tans7680[3840] = 0.000001;
	i = -1;
	while (i++ < 640)
		fisheye1280[i] = cosl(rads360[(int)(330 + (i * 0.046875))]);
	while (i++ < 1279)
		fisheye1280[i] = cosl(rads360[(int)(-29 + i * 0.046875)]);
	fisheye1280[641] = 1.0;
}

void		initialize_states(t_view *view)
{
	view->minimap_on = 0;
	view->textures_on = 1;
	view->shading_on = 1;
	view->print_player_on = 0;
	view->p->rotating[0] = 0;
	view->p->rotating[1] = 0;
	view->p->stepping[0] = 0;
	view->p->stepping[1] = 0;
	view->p->move_look = 0;
	view->p->stepping_velo = 0;
	view->p->rotation_velo = 0;
	view->p->rad = view->p->move_look * (M_PI / 180.0);
	assign_px_py(view->g, view->p);
}

void		initialize_view(t_view *view, char *title)
{
	/*
	 * // WONT NEED
	view->mlx = mlx_init();
	// WONT NEED
	view->idp = &(view->img_data);
	 // WONT NEED
	if (!(view->window = mlx_new_window(view->mlx, 1280, 800, title)))
		exit(print_error(MEMORY_ERROR));
	 // WONT NEED
	if (!(view->img = mlx_new_image(view->mlx, 1280, 800)))
		exit(print_error(MEMORY_ERROR));
	 // WONT NEED
	view->idp->buffer = mlx_get_data_addr(view->img,
										  &(view->idp->bits_per_pixel), &(view->idp->bytes_per_line),
										  &(view->idp->endianness));
	view->idp->int_buffer = (int *)view->idp->buffer;
	 // WONT NEED
	mlx_do_key_autorepeatoff(view->mlx);
	 // WONT NEED
	mlx_clear_window(view->mlx, view->window);
	 // WONT NEED
	hook_input(view);*/

	// ALREADY DONE EARLIER IN CODE ATM
	/*if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_EVENTS) < 0)
		quit_error("Could not initialize SDL base systems");
	if (TTF_Init() != 0)
		quit_error("Could not initialize SDL_ttf extension");
	if (IMG_Init(IMG_INIT_PNG) == 0)
		quit_error("Could not initialize SDL_image extension");
	SDL_CreateWindowAndRenderer(640, 480, 0, &g_win, &g_ren);
	g_surf = SDL_CreateRGBSurface(0, 640, 480, 32, 0, 0, 0, 0);
	if (g_win == NULL || g_ren == NULL || g_surf == NULL)
		quit_error("Could not initialize window, surface and renderer.");*/
	view->quit = 0;
	if (title != NULL)
		load_textures(view);
	populate_doubles_tables(view->rads360, view->rads7680,
							view->tans7680, view->fisheye1280);
	populate_color_tables(view->wall_colors);
	view->color_white.a = 255;
	view->color_white.r = 255;
	view->color_white.g = 255;
	view->color_white.b = 255;
}
