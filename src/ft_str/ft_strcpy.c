/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krusthol <krusthol@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 14:47:01 by krusthol          #+#    #+#             */
/*   Updated: 2019/10/22 12:16:21 by krusthol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strcpy(char *dst, const char *src)
{
	char *ptr;

	ptr = dst;
	while (*src)
	{
		*ptr = *src;
		ptr++;
		src++;
	}
	*ptr = *src;
	return (dst);
}
