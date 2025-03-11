/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_walllst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 10:13:51 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/11 13:01:21 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

static int	**init_walllst(t_map *map)
{
	t_2d	pos;
	int		**res;

	if (!map)
		return (NULL);
	ft_bzero(&pos, sizeof(t_2d));
	res = ft_calloc(map->size.y, sizeof(int *));
	if (!res)
		return (NULL);
	while (pos.y < map->size.y)
	{
		res[pos.y] = ft_calloc(map->size.x, sizeof(int));
		if (!res[pos.y])
		{
			while (pos.y >= 0)
				free(res[pos.y--]);
			free(res);
			return (NULL);
		}
		pos.y++;
	}
	return (res);
}

int	**map_walllst(t_map *map)
{
	t_2d	pos;
	int		**res;

	res = init_walllst(map);
	if (!res)
		return (NULL);
	ft_bzero(&pos, sizeof(t_2d));
	while (pos.y < map->size.y)
	{
		while (pos.x < map->size.x)
		{
			res[pos.y][pos.x] = map_wallvar(map, pos);
			pos.x++;
		}
		pos.x = 0;
		pos.y++;
	}
	return (res);
}
