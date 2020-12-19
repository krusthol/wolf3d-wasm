#include "wolf3d.h"

static void		main_loop(void *varg)
{
	t_view		*view;

	view = (t_view*)varg;
	while (SDL_PollEvent(&view->event) != 0)
	{
		if (view->event.type == SDL_KEYUP || view->event.type == SDL_KEYDOWN)
			process_input(view);
		else if (view->event.type == SDL_QUIT)
			view->quit = 1;
	}
	calc_movements(view);
}

static int		run_file_check(int argc, char *argv[], t_view *view)
{
	int		not_file;
	int		is_bad;

	if (argc == 1)
	{
		if ((not_file = open(MAPDATA, O_RDONLY, 0)) < 0)
		{
			puts(MAPDATA);
			puts(" could not be opened.");
			close_and_exit(not_file, MAP_DIRECTORY);
		}
		is_bad = check_mapfile(MAPDATA, view);
		if (!(is_bad))
			print_intro(MAPDATA);
		else
			return (print_error(is_bad));
	}
	else if (argc == 2)
	{
		puts(argv[1]);
		if ((not_file = open(argv[1], O_RDONLY | O_DIRECTORY, 0)) > 0)
			close_and_exit(not_file, MAP_DIRECTORY);
		is_bad = check_mapfile(argv[1], view);
		if (!(is_bad))
			print_intro(argv[1]);
		else
			return (print_error(is_bad));
	}
	return (0);
}

int				main(int argc, char *argv[])
{
	t_view	view;

	initialize_view(&view, "wolf3d-wasm by [krusthol]");
	init_systems(&view);
	init_memory(&view);
	view.g = &(view.grid);
	view.p = &(view.player);
	if (run_file_check(argc, argv, &view))
		return (0);
	initialize_states(&view);
	cast_walls(-1, view.g, view.p, &view);
#ifdef __EMSCRIPTEN__
	emscripten_set_main_loop_arg(main_loop, (void*)&view, 0, 1);
#else
	while (!view.quit)
		main_loop((void*)&view);
#endif
	SDL_Quit();
	return (0);
}
