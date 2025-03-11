/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_wallvar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 10:11:41 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/11 12:28:51 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

// TOP    : 0x1
// LEFT   : 0x2
// RIGHT  : 0x4
// BOTTOM : 0x8
int	map_wallvar(t_map *map, t_2d pos)
{
	int	res;

	res = 0;
	if (map->map[pos.y][pos.x] != '1')
		return (res);
	// Check top (cell above)
	if (pos.y != 0 && map->map[pos.y - 1][pos.x] == '1')
		res |= 0x1;
	// Check left (cell to the left)
	if (pos.x != 0 && map->map[pos.y][pos.x - 1] == '1')
		res |= 0x2;
	// Check right (cell to the right)
	if (pos.x != map->size.x - 1 && map->map[pos.y][pos.x + 1] == '1')
		res |= 0x4;
	// Check bottom (cell below)
	if (pos.y != map->size.y - 1 && map->map[pos.y + 1][pos.x] == '1')
		res |= 0x8;
	return (res);
}
