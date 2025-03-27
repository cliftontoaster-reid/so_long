/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_is_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 14:51:44 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/27 10:22:58 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

static size_t	count_players(t_map *map)
{
	size_t	player_count;
	int		i;
	int		j;

	player_count = 0;
	i = 0;
	while (i < map->size.y)
	{
		j = 0;
		while (j < map->size.x)
		{
			if (map->map[i][j] == 'P')
				player_count++;
			j++;
		}
		i++;
	}
	return (player_count);
}

t_trinary	map_is_player(t_map *map)
{
	size_t	player_count;

	player_count = count_players(map);
	if (player_count == 0)
		return (ZONE);
	if (player_count > 1)
		return (ZTWO);
	return (ZERO);
}
