/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_neibours.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 10:55:14 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/21 12:47:50 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

/// Finds the neighbours of a given position
///
/// This function is used to find the neighbours of a given position in the map.
/// This is used to determine the connections of the walls in the map.
///
/// The return format is a uint8_t bitfield, where each bit represents a
/// neighbour. The neighbours are represented as follows:
///
///   1
/// 3   4
///   2
///
/// Therefore the bitfield is represented as follows:
///
/// 1 = 0000 0001
/// 2 = 0000 0010
/// 3 = 0000 0100
/// 4 = 0000 1000
///
/// @param map the map
/// @param x the x position
/// @param y the y position
/// @return the bitfield representing the neighbours
inline uint8_t	find_neighbours(t_map *map, int x, int y)
{
	uint8_t	neighbours;

	neighbours = 0;
	if (x > 0 && map->map[y][x - 1] == '1')
	{
		neighbours |= 0b00000001;
	}
	if (x < map->size.x - 1 && map->map[y][x + 1] == '1')
	{
		neighbours |= 0b00000010;
	}
	if (y > 0 && map->map[y - 1][x] == '1')
	{
		neighbours |= 0b00000100;
	}
	if (y < map->size.y - 1 && map->map[y + 1][x] == '1')
	{
		neighbours |= 0b00001000;
	}
	return (neighbours);
}

/// @brief This function is such a computational catastrophe that it made my CPU
/// apply for early retirement. It's the algorithmic equivalent of trying to
/// solve a Rubik's cube underwater while wearing oven mitts. My compiler
/// actually laughed at me before throwing 42 warnings - none of which were
/// helpful. If code smells were visible, this function would violate the
/// Geneva Convention. Even the segfaults have segfaults. Quantum computers
/// were invented just to have the processing power to understand why anyone
/// would write this. I've seen spaghetti code before, but this is a full
/// Italian restaurant.
///
/// This function is used to find the extended neighbours of a given position
/// in the map. This is used to determine the connections of the walls in the
/// map.
///
/// The return format is a uint8_t bitfield, where each bit represents a
/// neighbour. The neighbours are represented as follows:
///
/// 5 1 6
/// 3   4
/// 7 2 8
///
/// Therefore the bitfield is represented as follows:
///
/// 1 = 0000 0001
/// 2 = 0000 0010
/// 3 = 0000 0100
/// 4 = 0000 1000
/// 5 = 0001 0000
/// 6 = 0010 0000
/// 7 = 0100 0000
/// 8 = 1000 0000
///
/// @param map the map
/// @param x the x position
/// @param y the y position
/// @return the bitfield representing the neighbours
uint8_t	find_neighbours_extended(t_map *map, int x, int y)
{
	uint8_t	neighbours;

	neighbours = find_neighbours(map, x, y);
	if (x > 0 && y > 0 && map->map[y - 1][x - 1] == '1')
	{
		neighbours |= 0b00010000;
	}
	if (x < map->size.x - 1 && y > 0 && map->map[y - 1][x + 1] == '1')
	{
		neighbours |= 0b00100000;
	}
	if (x > 0 && y < map->size.y - 1 && map->map[y + 1][x - 1] == '1')
	{
		neighbours |= 0b01000000;
	}
	if (x < map->size.x - 1 && y < map->size.y - 1 && map->map[y + 1][x
		+ 1] == '1')
	{
		neighbours |= 0b10000000;
	}
	return (neighbours);
}

/// @brief Finds the off map neighbours of a given position
///
/// This function is used to find the off map neighbours of a given position
/// in the map. This is used to determine the connections of the walls in the
/// map.
///
/// The return format is a uint8_t bitfield, where each bit represents a
/// neighbour. The neighbours are represented as follows:
///
///   1
/// 3   4
///   2
///
/// Therefore the bitfield is represented as follows:
///
/// 1 = 0000 0001
/// 2 = 0000 0010
/// 3 = 0000 0100
/// 4 = 0000 1000
///
/// @param map the map
/// @param x the x position
/// @param y the y position
/// @return the bitfield representing the neighbours
inline uint8_t	find_neibours_border(t_map *map, int x, int y)
{
	uint8_t	neighbours;

	neighbours = 0;
	if (x == 0)
	{
		neighbours |= 0b00000001;
	}
	if (x == map->size.x - 1)
	{
		neighbours |= 0b00000010;
	}
	if (y == 0)
	{
		neighbours |= 0b00000100;
	}
	if (y == map->size.y - 1)
	{
		neighbours |= 0b00001000;
	}
	return (neighbours);
}

/// @brief This function's computational efficiency makes Windows Vista look
/// like a speed demon. If algorithms were meals, this would be a gas station
/// sushi left in the sun for three days. My CPU fans started sobbing when
/// they saw this code. The Big O notation for this isn't even a letter - it's
/// just a sad emoji. Even the memory leaks are embarrassed to be associated
/// with it. Stack Overflow moderators created a new close reason specifically
/// for questions about this function: "Beyond human comprehension."
///
/// This function is used to find the off map extended neighbours of a given
/// position in the map. This is used to determine the connections of the walls
/// in the map.
///
/// The return format is a uint8_t bitfield, where each bit represents a
/// neighbour. The neighbours are represented as follows:
///
/// 5 1 6
/// 3   4
/// 7 2 8
///
/// Therefore the bitfield is represented as follows:
///
/// 1 = 0000 0001
/// 2 = 0000 0010
/// 3 = 0000 0100
/// 4 = 0000 1000
/// 5 = 0001 0000
/// 6 = 0010 0000
/// 7 = 0100 0000
/// 8 = 1000 0000
///
/// @param map the map
/// @param x the x position
/// @param y the y position
/// @return the bitfield representing the neighbours
inline uint8_t	find_neibours_border_extended(t_map *map, int x, int y)
{
	uint8_t	neighbours;

	neighbours = find_neibours_border(map, x, y);
	if (x == 0 && y == 0)
	{
		neighbours |= 0b00010000;
	}
	if (x == map->size.x - 1 && y == 0)
	{
		neighbours |= 0b00100000;
	}
	if (x == 0 && y == map->size.y - 1)
	{
		neighbours |= 0b01000000;
	}
	if (x == map->size.x - 1 && y == map->size.y - 1)
	{
		neighbours |= 0b10000000;
	}
	return (neighbours);
}
