/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krusthol <krusthol@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 17:26:31 by krusthol          #+#    #+#             */
/*   Updated: 2020/02/07 19:08:49 by krusthol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	key_toggle(t_view *view, int *toggle, char *message)
{
	*toggle = !(*toggle);
	cast_walls(-1, view->g, view->p, view);
	puts(message);
	if (*toggle)
		puts("ON");
	else
		puts("OFF");
	/*
	mlx_string_put(view->mlx, view->window,
		620 - (((int)ft_strlen(message)) * 3), 230, 0xFFFFFF, message);
	if (*toggle)
		mlx_string_put(view->mlx, view->window, 623, 250, 0xFFFFFF, "ON");
	else
		mlx_string_put(view->mlx, view->window, 620, 250, 0xFFFFFF, "OFF"); */
}

static void	key_releases(int i, t_view *view)
{
	if (i == SDL_SCANCODE_W || i == SDL_SCANCODE_UP)
		view->p->stepping[0] = 0;
	else if (i == SDL_SCANCODE_S || i == SDL_SCANCODE_DOWN)
		view->p->stepping[1] = 0;
	else if (i == SDL_SCANCODE_D || i == SDL_SCANCODE_RIGHT)
		view->p->rotating[0] = 0;
	else if (i == SDL_SCANCODE_A || i == SDL_SCANCODE_LEFT)
		view->p->rotating[1] = 0;
}

static void	key_presses(int i, t_view *view)
{
	if (i == SDL_SCANCODE_W || i == SDL_SCANCODE_UP)
		view->p->stepping[0] = 1;
	else if (i == SDL_SCANCODE_S || i == SDL_SCANCODE_DOWN)
		view->p->stepping[1] = -1;
	else if (i == SDL_SCANCODE_D || i == SDL_SCANCODE_RIGHT)
		view->p->rotating[0] = -1;
	else if (i == SDL_SCANCODE_A || i == SDL_SCANCODE_LEFT)
		view->p->rotating[1] = 1;
	else if (i == SDL_SCANCODE_TAB)
	{
		view->minimap_on = !(view->minimap_on);
		cast_walls(-1, view->g, view->p, view);
	}
	else if (i == SDL_SCANCODE_SPACE)
		key_toggle(view, &view->textures_on, "Textures");
	else if (i == SDL_SCANCODE_RETURN)
		key_toggle(view, &view->shading_on, "Shading");
	else if (i == SDL_SCANCODE_H)
		print_keyhelp();
	else if (i == SDL_SCANCODE_ESCAPE)
		exit(0);
}

void		process_input(t_view *view)
{
	if (view->event.type == SDL_KEYDOWN)
		key_presses(view->event.key.keysym.scancode, view);
	else if (view->event.type == SDL_KEYUP)
		key_releases(view->event.key.keysym.scancode, view);
}
