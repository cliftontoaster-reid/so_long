/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:16:40 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/27 12:47:32 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "data.h"
# include "map.h"

/* Basic neighbor directions */
# define NEIGHBOR_N 0x01 /* North / Top:        0000 0001 */
# define NEIGHBOR_S 0x02 /* South / Bottom:     0000 0010 */
# define NEIGHBOR_W 0x04 /* West / Left:        0000 0100 */
# define NEIGHBOR_E 0x08 /* East / Right:       0000 1000 */

/* Extended neighbor directions */
# define NEIGHBOR_NW 0x10 /* Northwest:         0001 0000 */
# define NEIGHBOR_NE 0x20 /* Northeast:         0010 0000 */
# define NEIGHBOR_SW 0x40 /* Southwest:         0100 0000 */
# define NEIGHBOR_SE 0x80 /* Southeast:         1000 0000 */

# define SIDES_VALUE 0x0F
# define DIAGO_VALUE 0xF0
# define FULLL_VALUE 0xFF

# define WALL_TOP 0x01
# define WALL_BOTTOM 0x02
# define WALL_LEFT 0x04
# define WALL_RIGHT 0x08

# define WALLBASE 8

int			ft_rand_int(int x, int y);
t_2d		pos_scale(t_2d pos, t_2d size, int scale);

void		render(t_data *data, t_map *map);

t_img		*create_floor(t_data *data);
void		render_floor(t_data *data, t_map *map, t_2d pos, t_img *img);

void		setup_cosmetics(t_data *data);
void		render_cosmetics(t_data *data);
void		render_cosmetic(t_data *data, t_map *map, t_2d pos, t_img *img);
void		render_guy(t_data *data);

void		just_render_exit(t_data *data);
void		render_exit(t_data *data, t_map *map, t_2d pos, t_img *img);

typedef struct s_wall_vars
{
	uint8_t	n;
	t_2d	pos;
}			t_wall_vars;

typedef struct s_wall_config
{
	int		x1;
	int		y1;
	// Top-left segment coordinates
	int		x2;
	int		y2;
	// Top-right segment coordinates
	int		x3;
	int		y3;
	// Bottom-left segment coordinates
	int		x4;
	int		y4;
	// Bottom-right segment coordinates
}			t_wall_config;

void		just_render_walls(t_data *data);
void		render_wall(t_data *data, t_map *map, t_2d pos, t_img *img);

uint8_t		**compute_wall_connections(t_map *map);

/// @brief Finds the extended neighbours of a given position
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
uint8_t		find_neighbours_extended(t_map *map, int x, int y);

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
uint8_t		find_neighbours(t_map *map, int x, int y);

/// @brief Finds the extended neighbours of a given position
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
uint8_t		find_neighbours_extended(t_map *map, int x, int y);

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
uint8_t		find_neibours_border(t_map *map, int x, int y);

/// @brief Finds the off map extended neighbours of a given position
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
uint8_t		find_neibours_border_extended(t_map *map, int x, int y);

/// @brief Returns the number of neighbours in a given bitfield
///
/// This function is used to count the number of neighbours in a given bitfield
/// representing the neighbours of a given position in the map.
///
/// @param neighbours the bitfield representing the neighbours
/// @return the number of neighbours
int			get_neighbour_count(uint8_t neighbours);

/// @brief Returns the number of neighbours in a given bitfield
///
/// This function is used to count the number of neighbours in a given bitfield
/// representing the neighbours of a given position in the map.
///
/// @param neighbours the bitfield representing the neighbours
/// @return the number of neighbours
int			get_neighbour_count_extended(uint8_t neighbours);
/// ALL DUN
t_img		*wall_hull(t_data *data);

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
bool		isasexual(t_data *data, t_2d pos);

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
bool		islesbian(t_data *data, t_2d pos);

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
bool		isgay(t_data *data, t_2d pos);

/**
 * @brief Adds coordinates to a position.
 *
 * This function adds the given x and y coordinates to a position.
 *
 * @param a The original position.
 * @param x The x coordinate to add.
 * @param y The y coordinate to add.
 * @return The new position after adding the coordinates.
 */
t_2d		posadd(t_2d a, int x, int y);

/**
 * @brief Retrieves a wall image from the set.
 *
 * This function retrieves a wall image from the set based on the given x and y
 * coordinates.
 *
 * @param data Pointer to the main data structure.
 * @param x The x coordinate in the set.
 * @param y The y coordinate in the set.
 * @return Pointer to the retrieved wall image, or NULL on failure.
 */
t_img		*get_wall(t_data *data, int x, int y, bool colour);

/**
 * @brief Creates a wall image with a hull shape.
 *
 * This function generates a wall image with a hull shape by combining four
 * smaller wall images. The resulting image is a 32x32 pixel wall section.
 *
 * The shape of the wall is as follows:
 *
 * ```
 * +----+
 * |    |
 * |    |
 * +----+
 * ```
 *
 * @param data Pointer to the main data structure.
 * @param map Pointer to the map structure.
 * @param vars Wall variables containing position and neighbor information.
 * @param img Pointer to the base image.
 * @return Pointer to the created wall image, or NULL on failure.
 */
t_img		*wall_hull(t_data *data);

/**
 * @brief Creates a T-bone junction wall image
 *
 * This function generates a 32x32 pixel image for a T-bone junction wall tile
 * by combining four 16x16 wall segments. The appearance varies based on the
 * wall's orientation (top, bottom, left, or right) and adjacent wall types.
 *
 * @param data      Pointer to the game data structure
 * @param map       Pointer to the map structure
 * @param vars      Wall variables including position and orientation flags
 * @param img       Pointer to an image (unused in this function)
 *
 * @return          Pointer to the newly created wall image,
 *                  or NULL if memory allocation fails
 */
t_img		*wall_tbone(t_data *data, t_wall_vars vars);
bool		is600cornered(t_data *data, t_wall_vars vars, t_2d pos);
t_img		*wall_t600_connected(t_data *data, t_wall_vars vars, t_2d pos);
bool		is600cornered(t_data *data, t_wall_vars vars, t_2d pos);
t_img		*wall_t600_lonely(t_data *data, t_wall_vars vars, t_2d pos);
t_img		*wall_t600(t_data *data, t_wall_vars vars, t_2d pos);
bool		is600cornered_check(t_data *data, t_wall_vars vars, t_2d pos,
				int8_t n);
t_img		*wall_tbi(t_data *data, t_wall_vars vars, t_2d pos);
t_img		*create_wall_tile(t_data *data, t_wall_config config);

#endif
