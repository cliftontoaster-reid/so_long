/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_is_char_valid.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 15:20:30 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/05 14:04:58 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

static bool	is_char_in_str(char c, char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (c == str[i])
			return (true);
		i++;
	}
	return (false);
}

bool	map_is_char_valid(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->size.y)
	{
		j = 0;
		while (j < map->size.x)
		{
			if (!is_char_in_str(map->map[i][j], MAP_CHARS))
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}
