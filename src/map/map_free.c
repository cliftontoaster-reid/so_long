/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 17:02:37 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/04 17:38:28 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

void	map_free(t_map *map)
{
	int	i;

	if (map == NULL)
		return ;
	i = 0;
	while (i < map->size.y)
	{
		free(map->map[i]);
		i++;
	}
	free(map->map);
	free(map);
}
