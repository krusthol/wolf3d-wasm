/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krusthol <krusthol@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 17:00:29 by krusthol          #+#    #+#             */
/*   Updated: 2020/02/04 19:35:36 by krusthol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		hits_wall(t_grid *grid, int x, int y)
{
	int		cols;
	int		rows;
	int		grid_x;
	int		grid_y;

	cols = grid->cols;
	rows = grid->rows;
	grid_x = x >> 8;
	grid_y = y >> 8;
	if ((grid_x < 0 || grid_x >= cols || grid_y < 0 || grid_y >= rows) ||
		!(grid_x <= cols && grid_y <= rows))
		return (-1);
	if (grid->grid[grid_y][grid_x] == 'W')
		return (1);
	return (0);
}

void	assign_clip_values(int *cx, int *cy, int move_facing)
{
	*cx = 0;
	*cy = 0;
	if (move_facing == 0)
		*cy = 32;
	else if (move_facing == 1)
		*cx = -32;
	else if (move_facing == 2)
		*cy = -32;
	else if (move_facing == 3)
		*cx = 32;
}

void	stop_velocity(t_player *p)
{
	p->stepping_velo = 0;
}

void	assign_px_py(t_grid *grid, t_player *p)
{
	int i;
	int k;

	i = 0;
	k = 0;
	while (i < grid->rows)
	{
		while (k < grid->cols)
		{
			if (grid->grid[i][k] == 'P')
			{
				p->x = 256 * k + 128;
				p->y = 256 * i + 128;
				grid->grid[i][k] = '.';
			}
			k++;
		}
		i++;
		k = 0;
	}
}

char	**grid_set(int rows, int columns, char *data)
{
	char	**grid;
	char	*ptr;
	int		i;
	int		k;

	i = -1;
	if (!(grid = (char **)malloc(sizeof(char *) * rows
			+ sizeof(char) * columns * rows)))
		exit(print_error(MEMORY_ERROR));
	ptr = (char *)(grid + rows);
	while (i++ < rows)
		grid[i] = (ptr + columns * i);
	i = 0;
	k = 0;
	while (i < rows)
	{
		while (k < columns)
		{
			grid[i][k] = *data++;
			k++;
		}
		i++;
		k = 0;
	}
	return (grid);
}
