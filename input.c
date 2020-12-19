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

#include "wolf3dheader"

static void	key_toggle(t_view *view, int *toggle, char *message)
{
	*toggle = !(*toggle);
	cast_walls(-1, view->g, view->p, view);
	mlx_string_put(view->mlx, view->window,
		620 - (((int)ft_strlen(message)) * 3), 230, 0xFFFFFF, message);
	if (*toggle)
		mlx_string_put(view->mlx, view->window, 623, 250, 0xFFFFFF, "ON");
	else
		mlx_string_put(view->mlx, view->window, 620, 250, 0xFFFFFF, "OFF");
}

static int	exit_program(void *view_ptr)
{
	t_view	*view;
	int		i;

	view = (t_view*)view_ptr;
	i = 0;
	while (i < 4)
		mlx_destroy_image(view->mlx, view->txt_nesw[i++]);
	mlx_destroy_image(view->mlx, view->img);
	mlx_destroy_window(view->mlx, view->window);
	exit(0);
	return (0);
}

static int	key_releases(int i, t_view *view)
{
	if (i == KEY_ESC)
		exit_program((void*)view);
	if (i == KEY_W || i == KEY_UP)
		view->p->stepping[0] = 0;
	if (i == KEY_S || i == KEY_DOWN)
		view->p->stepping[1] = 0;
	if (i == KEY_D || i == KEY_RIGHT)
		view->p->rotating[0] = 0;
	if (i == KEY_A || i == KEY_LEFT)
		view->p->rotating[1] = 0;
	return (1);
}

static int	key_presses(int i, t_view *view)
{
	if (i == KEY_ESC)
		exit(0);
	if (i == KEY_W || i == KEY_UP)
		view->p->stepping[0] = 1;
	if (i == KEY_S || i == KEY_DOWN)
		view->p->stepping[1] = -1;
	if (i == KEY_D || i == KEY_RIGHT)
		view->p->rotating[0] = -1;
	if (i == KEY_A || i == KEY_LEFT)
		view->p->rotating[1] = 1;
	if (i == KEY_TAB)
		view->minimap_on = !(view->minimap_on);
	if (i == KEY_SPACE)
		key_toggle(view, &view->textures_on, "Textures");
	if (i == KEY_ENTER)
		key_toggle(view, &view->shading_on, "Shading");
	if (i == KEY_T)
		key_toggle(view, &view->threading_on, "Threading");
	if (i == KEY_TAB)
		cast_walls(-1, view->g, view->p, view);
	if (i == KEY_H || i == KEY_SLASH)
		print_keyhelp();
	return (1);
}

void		hook_input(t_view *view)
{
	mlx_hook(view->window, 2, (1L << 0), key_presses, view);
	mlx_hook(view->window, 3, (1L << 1), key_releases, view);
	mlx_hook(view->window, 17, (1L << 17), exit_program, view);
}
