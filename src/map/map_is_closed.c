/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_is_closed.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 14:49:38 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/05 14:20:41 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

bool	map_is_closed(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->size.x)
	{
		if (map->map[0][i] != '1' || map->map[map->size.y - 1][i] != '1')
			return (false);
		i++;
	}
	i = 1;
	while (i < map->size.y - 1)
	{
		if (map->map[i][0] != '1' || map->map[i][map->size.x - 1] != '1')
			return (false);
		i++;
	}
	return (true);
}
