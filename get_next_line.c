/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krusthol <krusthol@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 12:51:45 by krusthol          #+#    #+#             */
/*   Updated: 2020/02/03 19:59:25 by krusthol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3dheader"

static char		*heap_file(const int fd)
{
	int		rd;
	char	buff[BUFF_SIZE + 1];
	char	*heap;
	char	*join;

	rd = read(fd, buff, BUFF_SIZE);
	buff[rd] = '\0';
	heap = ft_strdup((const char*)&buff);
	while (rd > 0)
	{
		rd = read(fd, buff, BUFF_SIZE);
		buff[rd] = '\0';
		if (rd > 0)
		{
			join = ft_strdup(heap);
			ft_strdel(&heap);
			heap = ft_strjoin(join, (char*)&buff);
			ft_strdel(&join);
		}
	}
	if (heap[0] != '\0')
		return (heap);
	ft_strdel(&heap);
	return (0);
}

static size_t	line_len(const char *heap, size_t heap_size)
{
	size_t len;

	len = 0;
	if (*heap == '\n')
		return (len);
	while (*heap && len < heap_size)
	{
		len++;
		heap++;
		if (*heap == '\n' || *heap == '\0')
			return (len);
	}
	return (len);
}

static char		*pick_line(char **heap, const int fd)
{
	size_t	heap_size;
	size_t	len;
	char	*line;
	char	*new_heap;

	len = fd;
	len = 0;
	heap_size = ft_strlen((const char*)*heap);
	len = line_len((const char*)*heap, heap_size);
	line = ft_strsub((const char*)*heap, 0, len);
	if ((int)heap_size - ((int)len + 1) > 0)
	{
		new_heap = ft_strsub((const char*)*heap, len + 1,
				(heap_size - (len + 1)));
		ft_strdel(heap);
		*heap = new_heap;
	}
	else
		ft_strdel(heap);
	if (line[0] != '\n' && line[0] != '\0')
		return (line);
	if (heap_size > 0)
		return (line);
	return (0);
}

int				get_next_line(const int fd, char **line)
{
	static char	*heap[8192] = { 0 };
	char		*picked;
	int			error_fd;

	picked = 0;
	if (fd < 0 || ((error_fd = read(fd, picked, 0) == -1)))
		return (-1);
	if (!heap[fd])
	{
		heap[fd] = heap_file(fd);
		if (!heap[fd])
			return (0);
	}
	if ((picked = pick_line(&heap[fd], fd)))
	{
		*line = ft_strdup(picked);
		ft_strdel(&picked);
		return (1);
	}
	return (0);
}
