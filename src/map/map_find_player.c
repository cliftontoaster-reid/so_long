/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_find_player.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 16:44:58 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/05 16:45:11 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

t_2d	map_find_player(t_map *map)
{
	t_2d	pos;
	int		i;
	int		j;

	pos = (t_2d){-1, -1};
	i = 0;
	while (i < map->size.y)
	{
		j = 0;
		while (j < map->size.x)
		{
			if (map->map[i][j] == 'P')
			{
				pos = (t_2d){j, i};
				break ;
			}
			j++;
		}
		i++;
	}
	return (pos);
}
