/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_is_closed.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 14:49:38 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/27 10:08:36 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "utils.h"

static bool	map_is_closed_horizontal(t_map *map)
{
	int		i;
	bool	is_closed;

	i = 0;
	is_closed = true;
	while (i < map->size.x)
	{
		if (map->map[0][i] != '1')
		{
			log_error("Map is not closed at top: [%d:%d] = '%c'", __FILE__,
				__LINE__, 0, i, map->map[0][i]);
			is_closed = false;
		}
		if (map->map[map->size.y - 1][i] != '1')
		{
			log_error("Map is not closed at bottom: [%d][%d] = '%c'", __FILE__,
				__LINE__, map->size.y - 1, i, map->map[map->size.y - 1][i]);
			is_closed = false;
		}
		i++;
	}
	return (is_closed);
}

bool	map_is_closed(t_map *map)
{
	int		i;
	bool	is_closed;

	is_closed = map_is_closed_horizontal(map);
	i = 1;
	while (i < map->size.y - 1)
	{
		if (map->map[i][0] != '1')
		{
			log_error("Map is not closed at left: [%d][%d] = '%c'", __FILE__,
				__LINE__, i, 0, map->map[i][0]);
			is_closed = false;
		}
		if (map->map[i][map->size.x - 1] != '1')
		{
			log_error("Map is not closed at right: [%d][%d] = '%c'", __FILE__,
				__LINE__, i, map->size.x - 1, map->map[i][map->size.x - 1]);
			is_closed = false;
		}
		i++;
	}
	return (is_closed);
}
