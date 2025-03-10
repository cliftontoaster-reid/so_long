/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_is_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 14:53:48 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/05 14:05:10 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

t_trinary	map_is_exit(t_map *map)
{
	size_t	exit_count;
	int		i;
	int		j;

	exit_count = 0;
	i = 0;
	while (i < map->size.y)
	{
		j = 0;
		while (j < map->size.x)
		{
			if (map->map[i][j] == 'E')
				exit_count++;
			j++;
		}
		i++;
	}
	if (exit_count == 0)
		return (ZONE);
	if (exit_count > 1)
		return (ZTWO);
	return (ZERO);
}
