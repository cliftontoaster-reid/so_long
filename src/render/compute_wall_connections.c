/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_wall_connections.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 16:40:21 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/25 16:19:13 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Crust/img/img.h"
#include "Crust/img/scale.h"
#include "Crust/img/set.h"
#include "render.h"
#include "utils.h"

static inline void	safe_set(uint8_t **connections, t_map *map, int posx,
		int posy)
{
	if (posx >= 0 && posx < map->size.x && posy >= 0 && posy < map->size.y)
	{
		connections[posy][posx] = 1;
	}
}

static inline uint8_t	**allocate_connections(t_map *map)
{
	uint8_t	**connections;
	int		y;

	y = 0;
	connections = ft_calloc(map->size.y, sizeof(uint8_t *));
	if (!connections)
		return (NULL);
	while (y < map->size.y)
	{
		connections[y] = ft_calloc(map->size.x, sizeof(uint8_t));
		if (!connections[y])
		{
			while (--y >= 0)
				free(connections[y]);
			free(connections);
			return (NULL);
		}
		y++;
	}
	return (connections);
}

static inline void	set_wall_connection(uint8_t **connections, t_map *map,
		int posx, int posy)
{
	if (map->map[posy][posx] == '1')
	{
		if (posx + 1 < map->size.x && map->map[posy][posx + 1] == '1')
		{
			safe_set(connections, map, posx + 1, posy);
		}
		if (posx - 1 >= 0 && map->map[posy][posx - 1] == '1')
		{
			safe_set(connections, map, posx - 1, posy);
		}
		if (posy + 1 < map->size.y && map->map[posy + 1][posx] == '1')
		{
			safe_set(connections, map, posx, posy + 1);
		}
		if (posy - 1 >= 0 && map->map[posy - 1][posx] == '1')
		{
			safe_set(connections, map, posx, posy - 1);
		}
	}
}

uint8_t	**compute_wall_connections(t_map *map)
{
	uint8_t	**connections;
	int		x;
	int		y;

	connections = allocate_connections(map);
	if (!connections)
		return (NULL);
	y = 0;
	while (y < map->size.y)
	{
		x = 0;
		while (x < map->size.x)
		{
			set_wall_connection(connections, map, x, y);
			x++;
		}
		y++;
	}
	return (connections);
}
