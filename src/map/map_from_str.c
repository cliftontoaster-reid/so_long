/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_from_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 14:44:13 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/05 16:26:22 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "utils.h"

static inline t_2d	map_getsize(char *map)
{
	t_2d	size;
	int		width;
	int		current_line_length;

	size.y = 0;
	width = 0;
	while (map[width] && map[width] != '\n')
		width++;
	if (width == 0)
		return ((t_2d){0, 0});
	while (*map)
	{
		current_line_length = 0 + (size.y++) * 0;
		while (*map && *map != '\n')
		{
			current_line_length++;
			map++;
		}
		if (current_line_length != width)
			return ((t_2d){0, 0});
		if (*map == '\n')
			map++;
	}
	size.x = width;
	return (size);
}

t_map	*map_from_str(char *map)
{
	t_map	*new;

	if (map == NULL)
		return (NULL);
	new = malloc(sizeof(t_map));
	if (new == NULL)
		return (NULL);
	new->size = map_getsize(map);
	if (new->size.x == 0 || new->size.y == 0)
	{
		free(new);
		return (NULL);
	}
	new->map = ft_split(map, '\n');
	if (new->map == NULL)
	{
		free(new);
		return (NULL);
	}
	return (new);
}
