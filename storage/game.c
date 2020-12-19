#include "delta-2d.h"

extern SDL_Window			*window;
extern SDL_Renderer			*renderer;
extern SDL_Surface			*surface;
extern Uint32				*pixels;
extern SDL_Texture			*screenTexture;
extern SDL_Event			event;
extern t_pro				*pro;
extern t_wave				wave;
extern SDL_AudioDeviceID	device;
extern SDL_Rect				rect;
extern SDL_Rect				inner;
extern TTF_Font				*bb_font;
extern double				time_stage;
extern unsigned int			limit;
extern int					stage;
extern int					audio_volume;
extern SDL_Color			color_white;

SDL_Rect					tree_rect;
SDL_Rect					bushing_loc = { 0 };
SDL_Surface					*climb_tree_top;
SDL_Surface					*bushing = NULL;
SDL_Surface					*target_statue;
SDL_Surface					*thief_64;
SDL_Surface					*game_text = NULL;
char						*game_str = NULL;
int							throw_y;

SDL_Surface				*Wrapped_CreateRGBSurface(Uint32 flags, int width, int height, int depth)
{
	int rmask, gmask, bmask, amask;

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
#else
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
#endif
	return (SDL_CreateRGBSurface(flags, width, height, depth, rmask, gmask, bmask, amask));
}

SDL_Surface				*blit_create_surface(SDL_Surface *src, SDL_Rect *loc)
{
	SDL_Surface			*ret;

	ret = Wrapped_CreateRGBSurface(0, loc->w, loc->h, 32);	
	SDL_BlitSurface(src, loc, ret, NULL);
	return (ret);
}

void					set_frame(int frame_id, SDL_Rect *loc, SDL_Surface *sheet)
{
	int					cols;

	cols = sheet->w / loc->w;
	loc->x = (frame_id % cols) * loc->w;
	loc->y = (frame_id / cols) * loc->h;
	//printf("set_frame_id [ %d / %d ] (tried: %d)\n", ((loc->y / loc->h) * (sheet->w / loc->w)) + (loc->x / loc->w), (sheet->w / loc->w) * (sheet->h / loc->h), frame_id);
}

void					render_text(char *str, int x, int y)
{
	static SDL_Rect			sloc = { 0 };
	static char				*last_str = NULL;
	static SDL_Surface		*delta_text;
	int						i;

	if (last_str != NULL && str != NULL && strcmp(last_str, str) == 0)
	{
		sloc.w = game_text->w;
		sloc.h = game_text->h;
		sloc.x = x;
		sloc.y = y;
		SDL_BlitSurface(game_text, NULL, surface, &sloc);
	}
	else
	{
		if (delta_text)
		{
			SDL_BlitSurface(delta_text, NULL, surface, &sloc);
			SDL_FreeSurface(delta_text);
		}
		if (last_str != NULL)
			free(last_str);
		last_str = (char*)malloc(sizeof(char) * (strlen(str) + 1));
		last_str[strlen(str)] = '\0';
		i = strlen(str);
		while (i--)
		{
			last_str[i] = str[i];
		}
		if (game_text)
			SDL_FreeSurface(game_text);
		game_text = TTF_RenderText_Solid(bb_font, str, color_white);
		if (!game_text)
			error_exit("Fatal Error: TTF_RenderText_Solid failed.", 1);
		sloc.w = game_text->w;
		sloc.h = game_text->h;
		sloc.x = x;
		sloc.y = y;
		delta_text = Wrapped_CreateRGBSurface(0, sloc.w, sloc.h, 32);
		SDL_BlitSurface(surface, &sloc, delta_text, NULL);
		SDL_BlitSurface(game_text, NULL, surface, &sloc);
	}
}

static inline void		prepare_gpu(void)
{
	if (SDL_MUSTLOCK(surface))
		SDL_LockSurface(surface);
}

static inline void		update_gpu(void)
{
	if (SDL_MUSTLOCK(surface))
		SDL_UnlockSurface(surface);
	screenTexture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_RenderCopy(renderer, screenTexture, NULL, NULL);
	SDL_RenderPresent(renderer);
	SDL_DestroyTexture(screenTexture);
}

static void				adjust_rect(SDL_Rect *loc)
{
	static int			lock_keys = 0;

	if (event.type == SDL_KEYDOWN && !lock_keys)
	{		
		if (event.key.keysym.scancode == SDL_SCANCODE_UP)
			loc->y--;
		else if (event.key.keysym.scancode == SDL_SCANCODE_DOWN)
			loc->y++;
		else if (event.key.keysym.scancode == SDL_SCANCODE_LEFT)
			loc->x--;
		else if (event.key.keysym.scancode == SDL_SCANCODE_RIGHT)
			loc->x++;
		printf("loc x,y = %d,%d | w,h = %d,%d\n", loc->x, loc->y, loc->w, loc->h);
		lock_keys = 1;
	}
	else if (event.type == SDL_KEYUP && lock_keys)
	{
		lock_keys = 0;
	}
}

static void				adjust_line(t_line *line)
{
	static int			lock_keys = 0;
	static int			tick = 0;
	
	if (event.type == SDL_KEYDOWN && !lock_keys)
	{		
		if (event.key.keysym.scancode == SDL_SCANCODE_UP)
			line->y2--;
		else if (event.key.keysym.scancode == SDL_SCANCODE_DOWN)
			line->y2++;
		else if (event.key.keysym.scancode == SDL_SCANCODE_RETURN)
			puts("*throws!*");
		printf("line x1,y1 = %d,%d | x2,y2 = %d,%d\n", line->x1, line->y1, line->x2, line->y2);
		lock_keys = 1;
		tick = time_now();
	}
	if (lock_keys && time_now() - tick > 16)
		lock_keys = 0;
}

static inline void		throw_line(t_line *line)
{
	if (event.key.keysym.scancode == SDL_SCANCODE_RETURN && throw_y == 0)
	{
		throw_y = line->y2;
		//line->x2 = line->x1;
		//line->y2 = line->y1;
		line->segment = 10;
		line->empty = 0;
	}
}

static void				wave_line(t_line *line)
{
	static int			tick = 0;
	static int			spd_dir = 4;

	if (time_now() - tick > 16)
	{
		line->y2 += spd_dir;
		if (line->y2 > 330 || line->y2 < 230)
			spd_dir = spd_dir * (-1);
		tick = time_now();
	}
}

void					spinning_init(void)
{
	puts("hit the target! steeper angle means faster speed!");
	throw_y = 0;
}

void					spinning_loop(void)
{
	static SDL_Surface	*spinning_bg = NULL;
	static SDL_Surface	*spinning = NULL;
	static SDL_Rect		spinning_frame = { 0 };
	static SDL_Rect		spinning_loc = { 0 };
	static SDL_Rect		rope_rect = { 0 };
	static t_line		rope = { 0 };
	static int			spin_phase = 0;
	static int			tick = 0;
	

	prepare_gpu();
	if (!spinning_bg)
	{
		spinning_loc.x = 474;
		spinning_loc.y = 124;
		spinning_loc.w = spinning_loc.h = spinning_frame.w = spinning_frame.h = 32;
		spinning_bg = blit_create_surface(surface, &spinning_loc);
		spinning = IMG_Load("assets/grappling_hook_32.png");
		if (!spinning || !spinning_bg)
			error_exit("Fatal error: Could not load surfaces for spinning grappling hooks", 1);
		rope_rect.x = 160;
		rope_rect.y = 155;
		rope_rect.w = spinning_loc.x - rope_rect.x;
		rope_rect.h = 480 - rope_rect.y - 150;
		rope.x1 = rope_rect.x + rope_rect.w;
		rope.y1 = rope_rect.y;
		rope.x2 = rope_rect.x;
		rope.y2 = rope_rect.y + rope_rect.h;
		rope.color = 0xffffff44;
		rope.buff = surface;
		rope.segment = 12;
		rope.empty = 4;
		tick = time_now();
	}
	if (time_now() - tick > 64)
	{
		set_frame(spin_phase % 4, &spinning_frame, spinning);
		tick = time_now();
		spin_phase++;
	}
	SDL_BlitSurface(bushing, NULL, surface, &bushing_loc);
	SDL_BlitSurface(spinning_bg, NULL, surface, &spinning_loc);
	SDL_BlitSurface(spinning, &spinning_frame, surface, &spinning_loc);
	//SDL_FillRect(surface, &rope_rect, 0xffff0000);
	//if (throw_y == 0)
	delta2d_rope(&rope, surface);
	throw_line(&rope);
	wave_line(&rope);
	update_gpu();
}

void					climb_init(void)
{
    SDL_Surface	*battle_back;
    SDL_Surface	*climb_tree_bot;
    SDL_Surface	*throw_tree_top;
    SDL_Surface	*throw_tree_bot;

	time_stage = time_now();
    SDL_PauseAudioDevice(device, SDL_TRUE);
    close_audio(&device);
    audio_volume = 128;
	battle_back = IMG_Load("assets/battle_back.png");
    climb_tree_top = IMG_Load("assets/climb_tree_top.png");
    climb_tree_bot = IMG_Load("assets/climb_tree_bot.png");
    throw_tree_top = IMG_Load("assets/throw_tree_top.png");
    throw_tree_bot = IMG_Load("assets/throw_tree_bot.png");
	target_statue = IMG_Load("assets/target_statue.png");
	thief_64 = IMG_Load("assets/thief_64.png");
    if (!battle_back || !climb_tree_top || !climb_tree_bot || !throw_tree_top || !throw_tree_bot || !target_statue || !thief_64)
        error_exit("Could not load PNG assets for climbing!", 1);
    if (SDL_MUSTLOCK(surface))
		SDL_LockSurface(surface);
    SDL_BlitSurface(battle_back, NULL, surface, NULL);
    tree_rect.w = climb_tree_top->w;
    tree_rect.h = climb_tree_top->h;
    tree_rect.x = 640 - tree_rect.w - 32;
    tree_rect.y = 64;
    SDL_BlitSurface(climb_tree_bot, NULL, surface, &tree_rect);
    SDL_BlitSurface(climb_tree_top, NULL, surface, &tree_rect);
    tree_rect.w = throw_tree_top->w;
    tree_rect.h = throw_tree_top->h;
    tree_rect.x -= 256 + 64;
    tree_rect.y += 128;
    SDL_BlitSurface(throw_tree_bot, NULL, surface, &tree_rect);
    SDL_BlitSurface(throw_tree_top, NULL, surface, &tree_rect);
    if (SDL_MUSTLOCK(surface))
		SDL_UnlockSurface(surface);
	SDL_FreeSurface(battle_back);
	SDL_FreeSurface(climb_tree_bot);
	SDL_FreeSurface(throw_tree_top);
	SDL_FreeSurface(throw_tree_bot);
}

void					climb_loop(void)
{
	static SDL_Rect		placing = { 0 };
	static SDL_Rect 	sprite = { -1 };
	static SDL_Rect 	loc = { 0 };
	static SDL_Rect 	prev = { 0 };
	static SDL_Rect		wbgr = { 0 };
	static SDL_Rect		cbgr = { 0 };
	static SDL_Surface	*delta_bg = NULL;
	static SDL_Surface	*walk_bg = NULL;
	static SDL_Surface	*climb_bg = NULL;
	static int			prev_tick;
	int					rise_max = 11;
	static int			rise_ids[12] = { 265, 265, 265, 265, 264, 264, 263, 262, 261, 260, 260, 260 };
	static int			rise_phase = 0;
	static int			rise_delay = 112;
	static int			rising = 0;
	static int			walk_max = 8;
	static int			walk_begin = 117;
	static int			walk_phase = 0;
	static int			walk_delay = 112;
	static int			walk_step = 8;
	static int			walking = 0;
	static int			climbing = 0;
	static int			climb_max = 11;
	static int			climb_ids[6] = { 210, 211, 212, 213, 212, 213 };
	static int			climb_phase = 0;
	static int			climb_delay = 112;
	static int			lock_keys = 0;
	static int			tlocx = 0;
	static int			tlocy = 0;
	int					walked_input = 0;
	int					climbed_input = 0;

	if (event.type == SDL_KEYDOWN && !lock_keys)
	{		
		if (event.key.keysym.scancode == SDL_SCANCODE_UP)
			climbed_input = 1;
		else if (event.key.keysym.scancode == SDL_SCANCODE_DOWN)
			walk_begin++;
		else if (event.key.keysym.scancode == SDL_SCANCODE_LEFT)
			walked_input = 1;
		else if (event.key.keysym.scancode == SDL_SCANCODE_RIGHT)
			walk_max--;
		//printf("walk_begin = %d | max = %d\n", walk_begin, walk_max);
		lock_keys = 1;
	}
	else if (event.type == SDL_KEYUP && lock_keys)
	{
		lock_keys = 0;
	}

	if (!placing.x)
	{
		placing.w = target_statue->w;
		placing.h = target_statue->h;
		placing.x = 350;
		placing.y = 290;
	}
	if (!loc.x)
	{
		loc.w = 64;
		loc.h = 64;
		loc.x = placing.x + 96 + 96;
		loc.y = placing.y;
	}
	if (sprite.x == -1)
	{
		sprite.w = loc.w;
		sprite.h = loc.h;
		sprite.x = 0;
		sprite.y = 0;
	}
	if (walking && rising)
	{
		rising = 0;
		prev_tick = time_now();
		walk_phase = 0;
		set_frame(walk_begin + walk_phase, &sprite, thief_64);		
	}
	if (!rising && !walking)
	{
		rising = 1;
		rise_phase = 0;
		prev_tick = time_now();
		set_frame(rise_ids[rise_phase], &sprite, thief_64);
	}
	if (SDL_MUSTLOCK(surface))
		SDL_LockSurface(surface);
	if (!delta_bg)
	{
		delta_bg = Wrapped_CreateRGBSurface(0, loc.w, loc.h, 32);
		SDL_BlitSurface(surface, &loc, delta_bg, NULL);
	}
	if (!walk_bg)
	{
		walk_bg = Wrapped_CreateRGBSurface(0, loc.w + ((walk_max + 1) * walk_step), loc.h, 32);
		loc.x -= (walk_max + 1) * walk_step;
		loc.w += (walk_max + 1) * walk_step;
		SDL_BlitSurface(surface, &loc, walk_bg, NULL);
		loc.x += (walk_max + 1) * walk_step;
		loc.w -= (walk_max + 1) * walk_step;
		wbgr.w = loc.w + ((walk_max + 1) * walk_step);
		wbgr.h = loc.h;
		wbgr.x = loc.x - ((walk_max + 1) * walk_step);
		wbgr.y = loc.y;
	}
	if (!climb_bg)
	{
		climb_bg = Wrapped_CreateRGBSurface(0, loc.w, loc.h * 4, 32);
		loc.y -= loc.h * 3;
		loc.h *= 4;
		loc.x -= (walk_max + 1) * walk_step;
		SDL_BlitSurface(surface, &loc, climb_bg, NULL);
		cbgr.w = loc.w;
		cbgr.h = loc.h;
		cbgr.x = loc.x;
		cbgr.y = loc.y;
		loc.h /= 4;
		loc.y += loc.h * 3;
		loc.x += (walk_max + 1) * walk_step;
		tree_rect.x += 256 + 64;
    	tree_rect.y -= 128;
	}
	if (climbing)
	{
		if (climb_phase < climb_max && time_now() - prev_tick > climb_delay)
		{
			set_frame(climb_ids[climb_phase % 6], &sprite, thief_64);
			climb_phase++;
			prev_tick = time_now();
		}
		else if (climb_phase < climb_max && climb_phase != 0)
		{
			int step_next = (((climb_max - climb_phase) + 1) * ((cbgr.y - wbgr.y) / climb_max));
			int step_now = ((climb_max - climb_phase) * ((cbgr.y - wbgr.y) / climb_max));
			int	step_delta = step_next - step_now;
			loc.y = cbgr.y - ((climb_delay - (time_now() - prev_tick)) * step_delta / climb_delay) - step_now;
		}
		SDL_BlitSurface(climb_bg, NULL, surface, &cbgr);
		//SDL_FillRect(surface, &cbgr, 0xffffffff);
		SDL_BlitSurface(thief_64, &sprite, surface, &loc);
		SDL_BlitSurface(climb_tree_top, NULL, surface, &tree_rect);
		if (climb_phase == climb_max)
		{
			set_frame(18, &sprite, thief_64);
			if (time_now() - prev_tick > (climb_delay * 3))
			{
				climb_phase++;
				prev_tick = time_now();
			}
			SDL_BlitSurface(thief_64, &sprite, surface, &loc);
		}
		else if (climb_phase == climb_max + 1)
		{
			set_frame(19, &sprite, thief_64);
			if (time_now() - prev_tick > (climb_delay * 3))
				climb_phase++;
			SDL_BlitSurface(thief_64, &sprite, surface, &loc);
		}
		else if (climb_phase == climb_max + 2)
		{
			set_frame(233, &sprite, thief_64);
			SDL_BlitSurface(thief_64, &sprite, surface, &loc);
			stage++;
		}
		if (climb_phase > 8)
			SDL_BlitSurface(bushing, NULL, surface, &bushing_loc);
	}
	else if (rising)
	{
		if (rise_phase < rise_max && time_now() - prev_tick > rise_delay)
		{
			rise_phase++;
			prev_tick = time_now();
			set_frame(rise_ids[rise_phase], &sprite, thief_64);
		}
		if (rise_phase == rise_max && walked_input)
		{
			walking = 1;
			render_text(" ", tlocx, tlocy);
		}
		SDL_BlitSurface(target_statue, NULL, surface, &placing);
		SDL_BlitSurface(delta_bg, NULL, surface, &loc);
		SDL_BlitSurface(thief_64, &sprite, surface, &loc);
		if (rise_phase == rise_max && !walked_input)
		{
			tlocx = loc.x - 64;
			tlocy = loc.y + 96;
			render_text("PRESS LEFT!", tlocx, tlocy);
			
		}
	}
	else if (walking)
	{
		if (walk_phase < walk_max && time_now() - prev_tick > walk_delay)
		{
			walk_phase++;
			prev_tick = time_now();
			set_frame(walk_begin + walk_phase, &sprite, thief_64);
			loc.x = placing.x + 192 - (walk_phase * 8);
			if (walk_phase == walk_max)
			{
				render_text("PRESS UP!", tlocx, tlocy);
				set_frame(0, &sprite, thief_64);
			}
			SDL_BlitSurface(walk_bg, NULL, surface, &wbgr);			
			SDL_BlitSurface(thief_64, &sprite, surface, &loc);
		}
		if (walk_phase == walk_max && climbed_input)
		{
			climbing = 1;
			render_text(" ", tlocx, tlocy);
		}
	}
	if (!bushing_loc.x)
	{
		bushing_loc.x = 507 - tree_rect.x - 30;
		bushing_loc.y = 142 - tree_rect.y;
		bushing_loc.w = bushing_loc.h = 24;
		if (!(bushing = blit_create_surface(climb_tree_top, &bushing_loc)))
			error_exit("Fatal error: Could not blit surface at spinning loop!", 1);
		bushing_loc.x = 497;
		bushing_loc.y = 158;
	}
	if (SDL_MUSTLOCK(surface))
		SDL_UnlockSurface(surface);
	screenTexture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_RenderCopy(renderer, screenTexture, NULL, NULL);
	SDL_RenderPresent(renderer);
	SDL_DestroyTexture(screenTexture);
	// When done with statue target, can free it.
	// SDL_BlitSurface(target_statue, NULL, surface, &statue_rect);
	// Check freeable surfaces in main.c as well.
}