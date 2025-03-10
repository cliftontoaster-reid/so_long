/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_find_collectibles.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 17:18:11 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/06 13:51:07 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

inline t_list	*map_find_collectibles(t_map *map)
{
	t_list	*collectibles;
	t_2d	pos;

	collectibles = NULL;
	ft_bzero(&pos, sizeof(t_2d));
	while (pos.y < map->size.y)
	{
		pos.x = 0;
		while (pos.x < map->size.x)
		{
			if (map->map[pos.y][pos.x] == 'C')
			{
				if (!collectibles)
					collectibles = ft_lstnew(t2dclone(pos));
				else
					ft_lstadd_back(&collectibles, ft_lstnew(t2dclone(pos)));
			}
			pos.x++;
		}
		pos.y++;
	}
	return (collectibles);
}
