/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krusthol <krusthol@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 16:26:43 by krusthol          #+#    #+#             */
/*   Updated: 2020/02/04 19:07:19 by krusthol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int	correct_edge(char c)
{
	return (c == 'W');
}

static int	correct_char(char c)
{
	static int amount_of_p;

	if (c != 'W' && c != 'P' && c != '.')
		printf("Incorrect char culprit: %c\n", c);
	if (!c)
		return (amount_of_p);
	if (c == 'P')
		amount_of_p++;
	if (amount_of_p > 1)
		return (0);
	return (c == 'W' || c == 'P' || c == '.');
}

static int	load_map_line(char *buff, int (correct)(char c))
{
	if (correct_edge(*buff))
		buff++;
	while (*buff)
	{
		if (!correct(*buff))
			return (0);
		buff++;
	}
	if (correct_edge(*(buff - 1)))
		return (1);
	return (0);
}

static void print_data(char *data, int cols, int rows)
{
	int i = 0;
	printf("%d x %d COLS, ROWS\n", cols, rows);
	puts("Received data");
	while (*data)
	{
		if (i != 0 && i % cols == 0)
			write(1, "\n", 1);
		write(1, data, 1);
		data++;
		i++;
	}
	puts("\nEnd of data");
}

static int	read_map(int opened, t_view *view)
{
	char	*buff;
	char	*data;
	char	*temp;
	int		line;

	data = ft_strnew(1);
	line = 0;
	while (get_next_line(opened, &buff))
	{
		//if (!load_map_line(buff, line++ == 0 ? correct_edge : correct_char))
		load_map_line(buff, line++ == 0 ? correct_edge : correct_char);
		//	close_and_exit(opened, MAP_CONTENT);
		if ((int)ft_strlen(buff) == view->g->cols || view->g->cols == 0)
			view->g->cols = ft_strlen(buff);
		//else
		//	close_and_exit(opened, MAP_SHAPE);
		view->g->rows++;
		temp = data;
		data = ft_strjoin(data, buff);
		free(temp);
		free(buff);
	}
	view->g->grid = grid_set(view->g->rows, view->g->cols, data);
	print_data(data, view->g->cols, view->g->rows);
	free(data);
	close(opened);
	return (0);
}

int			check_mapfile(char *file_arg, t_view *view)
{
	int opened;
	int is_bad;

	opened = open(file_arg, O_RDONLY, 0);
	if (opened > 1)
	{
		view->g->cols = 0;
		view->g->rows = 0;
		is_bad = read_map(opened, view);
		if (!is_bad)
		{
			//if (!load_map_line(view->g->grid[view->g->rows - 1], correct_edge))
			//	puts("Bottom edge culprit!");
			//if (correct_char(0) != 1)
			//	puts("Culprit incorrect P amount!");
			//return (MAP_CONTENT);
			if (view->g->rows < 3 || view->g->cols < 3 ||
				view->g->rows > 256 || view->g->cols > 256)
				return (MAP_SIZE);
			return (0);
		}
	}
	return (MAP_FILE);
}
