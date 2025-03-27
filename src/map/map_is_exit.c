/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_is_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 14:53:48 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/27 10:10:12 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "utils.h"

static size_t	count_exits(t_map *map)
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
	return (exit_count);
}

bool	map_is_exit(t_map *map)
{
	size_t	exit_count;
	bool	is_valid;

	is_valid = true;
	exit_count = count_exits(map);
	if (exit_count == 0)
	{
		log_error("No exit found", __FILE__, __LINE__);
		is_valid = false;
	}
	if (exit_count > 1)
	{
		log_error("Too many exits found", __FILE__, __LINE__);
		is_valid = false;
	}
	log_debug("Exit count: %d", __FILE__, __LINE__, exit_count);
	return (is_valid);
}
