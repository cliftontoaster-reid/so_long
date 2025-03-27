/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lgbt.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 10:35:13 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/27 14:26:59 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "utils.h"

/**
 * @brief Checks if a position is surrounded by walls or boundaries.
 *
 * This function determines if a given position has all four cardinal neighbors
 * (top, bottom, left, right) either as walls or out of bounds. A position
 * is considered "asexual" if it's completely surrounded, with no non-wall
 * adjacent cells.
 *
 * @param data Pointer to the main data structure.
 * @param pos The position to check.
 * @return true if all four neighbors are walls or boundaries, false otherwise.
 */
bool	isasexual(t_data *data, t_2d pos)
{
	int8_t	nei;

	nei = find_neibours_border(data->map, pos.x, pos.y);
	nei |= find_neighbours(data->map, pos.x, pos.y);
	log_warning("NEIGHBOURS: %d", __FILE__, __LINE__, get_neighbour_count(nei));
	if (nei == 0xF)
		return (true);
	return (false);
}

/**
 * @brief Determines if a map position should be rendered as a wall.
 *
 * This function checks if a given position on the map should be rendered as a
 * wall based on two criteria: whether it's a valid wall according to the base
 * map data and whether it's flagged as a "random wall" that should be hidden.
 *
 * @param data Pointer to the main game data structure containing map and
 *             random wall information.
 * @param pos The 2D position (x, y) on the map to check.
 * @return true if the position should be rendered as a wall, false otherwise.
 *
 * @note This function first checks if the position is a valid wall based on
 *       the original map data. If it is, it then checks the random wall data
 *       to determine if this specific wall should be hidden.
 */
bool	islesbian(t_data *data, t_2d pos)
{
	if (!data)
		return (true);
	if (!data->map)
		return (true);
	if (pos.x < 0)
		return (true);
	if (pos.y < 0)
		return (true);
	if (pos.x >= data->map->size.x)
		return (true);
	if (pos.y >= data->map->size.y)
		return (true);
	return (data->map->map[pos.y][pos.x] == '1');
}

/**
 * @brief Checks if a position is considered a wall.
 *
 * This function determines if a given position is considered in the closet
 * or not, based on the map data and the random wall data.
 *
 * Closeted walls should not be rendered, that is why they hide in the closet.
 *
 * @param data Pointer to the main data structure.
 * @param pos The position to check.
 * @return true if the position is considered hidden, false otherwise.
 */
bool	isgay(t_data *data, t_2d pos)
{
	if (!data)
		return (true);
	if (!data->map)
		return (true);
	if (pos.x < 0)
		return (true);
	if (pos.y < 0)
		return (true);
	if (pos.x >= data->map->size.x)
		return (true);
	if (pos.y >= data->map->size.y)
		return (true);
	if (data->map->map[pos.y][pos.x] != '1')
		return (false);
	if (!data->rndwall || !data->rndwall[pos.y])
		return (false);
	return (!(data->rndwall[pos.y][pos.x]));
}
