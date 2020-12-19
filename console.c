/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   console.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krusthol <krusthol@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 16:16:20 by krusthol          #+#    #+#             */
/*   Updated: 2020/02/27 23:02:52 by krusthol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3dheader"

void	close_and_exit(int fd_to_close, int code)
{
	close(fd_to_close);
	exit(print_error(code));
}

void	print_keyhelp(void)
{
	write(1, "wolf3d keyhelp:\n", 16);
	write(1, "\twasd arrows\tmove\n", 18);
	write(1, "\ttab\t\ttoggle minimap\n", 21);
	write(1, "\tenter space t\tsettings\n", 24);
	write(1, "\th / ?\t\tshow keyhelp\n", 21);
	write(1, "\tesc\t\tquit wolf3d\n", 18);
}

void	print_intro(char *file_arg)
{
	write(1, "wolf3d valid map [", 18);
	write(1, file_arg, ft_strlen(file_arg));
	write(1, "] loaded. show keyhelp by pressing H / (?)\n", 43);
}

int		print_error(int code)
{
	write(1, "wolf3d error:\n", 14);
	if (code == MAP_CONTENT)
	{
		write(1, "map content invalid\n", 20);
		write(1, "must have a single 'P', all edges 'W'\n", 38);
		write(1, "must have the rest either 'W' or '.'\n", 37);
	}
	if (code == MAP_FILE)
		write(1, "parameter must be able to open\n", 31);
	if (code == MAP_SIZE)
		write(1, "map size must be 3x3 ... 256x256\n", 33);
	if (code == MAP_SHAPE)
		write(1, "map shape must be rectangular\n", 30);
	if (code == INVALID_TEXTURE)
		write(1, "textures must be 256x256 .xpm files\n", 36);
	if (code == MEMORY_ERROR)
		write(1, "ran out of available memory\n", 28);
	if (code == TEXTURE_LOAD_FAILURE)
		write(1, "could not load a texture to memory\n", 35);
	if (code == MAP_DIRECTORY)
		write(1, "parameter can not be a directory\n", 33);
	return (code);
}

void	print_usage_and_exit(int code)
{
	write(1, "wolf3d usage:\n./wolf3d [mapfile]\n", 33);
	exit(code);
}
