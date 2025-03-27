/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 13:13:41 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/27 10:24:50 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Crust/img/img.h"
#include "Crust/img/scale.h"
#include "Crust/img/set.h"
#include "render.h"
#include "utils.h"

#define SIDES_VALUE 0x0F
#define DIAGO_VALUE 0xF0
#define FULLL_VALUE 0xFF

#define WALL_TOP 0x01
#define WALL_BOTTOM 0x02
#define WALL_LEFT 0x04
#define WALL_RIGHT 0x08

#define WALLBASE 8

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
inline t_img	*wall_hull(t_data *data)
{
	t_img	*wall;
	t_img	*gay[4];

	wall = crust_img_new(data->mlx, 32, 32);
	(void)"This is a comment made to annoy the norm";
	gay[0] = crust_set_get_img_by_pos(data->set, (t_2d){WALLBASE, 0});
	gay[1] = crust_set_get_img_by_pos(data->set, (t_2d){WALLBASE + 2, 0});
	gay[2] = crust_set_get_img_by_pos(data->set, (t_2d){WALLBASE, 2});
	gay[3] = crust_set_get_img_by_pos(data->set, (t_2d){WALLBASE + 2, 2});
	if (!(gay[0] && gay[1] && gay[2] && gay[3]))
		return (NULL);
	(void)"Now we print the walls, because we can";
	crust_img_draw(wall, gay[0], (t_2d){0, 0});
	crust_img_draw(wall, gay[1], (t_2d){16, 0});
	crust_img_draw(wall, gay[2], (t_2d){0, 16});
	crust_img_draw(wall, gay[3], (t_2d){16, 16});
	(void)"This is a comment made to annoy the norm, again";
	return (wall);
}

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
static inline bool	isasexual(t_data *data, t_2d pos)
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
static inline bool	islesbian(t_data *data, t_2d pos)
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
static inline bool	isgay(t_data *data, t_2d pos)
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
static inline t_2d	posadd(t_2d a, int x, int y)
{
	return ((t_2d){a.x + x, a.y + y});
}

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
inline t_img	*get_wall(t_data *data, int x, int y, bool colour)
{
	t_2d	pos;
	t_img	*img;

	pos = (t_2d){WALLBASE + x, y};
	if (colour)
		pos.y += 5;
	img = crust_set_get_img_by_pos(data->set, pos);
	if (!img)
		return (NULL);
	return (img);
}

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
static inline t_img	*wall_tbone(t_data *data, t_wall_vars vars)
{
	t_img	*wall;
	t_img	*gay[4];

	wall = crust_img_new(data->mlx, 32, 32);
	if (!wall)
		return (NULL);
	if (vars.n & WALL_TOP)
	{
		gay[0] = get_wall(data, 0, 1, data->d);
		gay[1] = get_wall(data, 2, 1, data->d);
		gay[2] = get_wall(data, 0, 2, data->d);
		gay[3] = get_wall(data, 2, 2, data->d);
	}
	else if (vars.n & WALL_BOTTOM)
	{
		gay[0] = get_wall(data, 0, 0, data->d);
		gay[1] = get_wall(data, 2, 0, data->d);
		gay[2] = get_wall(data, 0, 1, data->d);
		gay[3] = get_wall(data, 2, 1, data->d);
	}
	else if (vars.n & WALL_LEFT)
	{
		gay[0] = get_wall(data, 1, 0, data->d);
		gay[1] = get_wall(data, 2, 0, data->d);
		gay[2] = get_wall(data, 1, 2, data->d);
		gay[3] = get_wall(data, 2, 2, data->d);
	}
	else if (vars.n & WALL_RIGHT)
	{
		gay[0] = get_wall(data, 0, 0, data->d);
		gay[1] = get_wall(data, 1, 0, data->d);
		gay[2] = get_wall(data, 0, 2, data->d);
		gay[3] = get_wall(data, 1, 2, data->d);
	}
	crust_img_draw(wall, gay[0], (t_2d){0, 0});
	crust_img_draw(wall, gay[1], (t_2d){16, 0});
	crust_img_draw(wall, gay[2], (t_2d){0, 16});
	crust_img_draw(wall, gay[3], (t_2d){16, 16});
	return (wall);
}

static inline bool	is600cornered(t_data *data, t_wall_vars vars, t_2d pos)
{
	int8_t	n;

	(void)vars;
	n = find_neighbours_extended(data->map, pos.x, pos.y);
	log_debug("Checking if cornered (%d, %d: 0x%x)", __FILE__, __LINE__, pos.x,
		pos.y, n);
	if ((n & WALL_LEFT) && (n & WALL_TOP))
	{
		return (n & NEIGHBOR_NW);
	}
	else if ((n & WALL_RIGHT) && (n & WALL_TOP))
	{
		return (n & NEIGHBOR_NE);
	}
	else if ((n & WALL_LEFT) && (n & WALL_BOTTOM))
	{
		return (n & NEIGHBOR_SW);
	}
	else if ((n & WALL_RIGHT) && (n & WALL_BOTTOM))
	{
		log_info("WALL SW: %d", __FILE__, __LINE__, NEIGHBOR_NW);
		log_debug("NORTH CAT %d", __FILE__, __LINE__, n & isgay(data,
				posadd(pos, -1, 0)));
		log_debug("WEST CAT %d", __FILE__, __LINE__, n & isgay(data, posadd(pos,
					0, -1)));
		// if none of the two are gay, then it's a corner
		if (!isgay(data, posadd(pos, -1, 0)) && !isgay(data, posadd(pos, 0,
					-1)))
			return (true);
		return (n & NEIGHBOR_SE);
	}
	return (false);
}

/**
 * @brief Creates a wall image for connected corners.
 *
 * This function generates a 32x32 pixel wall image for a corner where two walls
 * connect (such as an L-shape). The corner appearance varies based on which
 * directions (top-left, top-right, bottom-left,
 * bottom-right) the walls connect.
 *
 * @param data Pointer to the main data structure.
 * @param map Pointer to the map structure.
 * @param vars Wall variables containing position and neighbor information.
 * @param img Pointer to the base image.
 *
 * @return Pointer to the created wall image, or NULL on failure.
 */
static inline t_img	*wall_t600_connected(t_data *data, t_wall_vars vars,
		t_2d pos)
{
	t_img	*wall;
	t_img	*gay[4];
	int8_t	n;

	n = vars.n;
	if (!is600cornered(data, vars, pos))
		return (crust_img_scale(get_wall(data, 1, 1, false), (t_2d){32, 32},
				CRUST_IMG_SCALE_NEAREST));
	if ((n & WALL_LEFT) && (n & WALL_TOP))
	{
		gay[0] = get_wall(data, 1, 1, data->d);
		gay[1] = get_wall(data, 1, 2, data->d);
		gay[2] = get_wall(data, 1, 2, data->d);
		gay[3] = get_wall(data, 2, 2, data->d);
	}
	else if ((n & WALL_LEFT) && (n & WALL_BOTTOM))
	{
		gay[0] = get_wall(data, 0, 1, data->d);
		gay[1] = get_wall(data, 2, 0, data->d);
		gay[2] = get_wall(data, 1, 1, data->d);
		gay[3] = get_wall(data, 2, 1, data->d);
	}
	else if ((n & WALL_RIGHT) && (n & WALL_TOP))
	{
		gay[0] = get_wall(data, 0, 1, data->d);
		gay[1] = get_wall(data, 1, 1, data->d);
		gay[2] = get_wall(data, 0, 2, data->d);
		gay[3] = get_wall(data, 1, 2, data->d);
	}
	else if ((n & WALL_RIGHT) && (n & WALL_BOTTOM))
	{
		gay[0] = get_wall(data, 0, 0, data->d);
		gay[1] = get_wall(data, 1, 0, data->d);
		gay[2] = get_wall(data, 0, 1, data->d);
		gay[3] = get_wall(data, 1, 1, data->d);
	}
	wall = crust_img_new(data->mlx, 32, 32);
	if (!wall)
		return (NULL);
	crust_img_draw(wall, gay[0], (t_2d){0, 0});
	crust_img_draw(wall, gay[1], (t_2d){16, 0});
	crust_img_draw(wall, gay[2], (t_2d){0, 16});
	crust_img_draw(wall, gay[3], (t_2d){16, 16});
	return (wall);
}

/**
 * @brief Creates a wall image for isolated wall segments.
 *
 * This function generates a 32x32 pixel wall image for isolated wall segments
 * that only connect in one direction (either top or left). The function creates
 * a repeating pattern appropriate for the wall's orientation.
 *
 * @param data Pointer to the main data structure.
 * @param map Pointer to the map structure.
 * @param vars Wall variables containing position and neighbor information.
 * @param img Pointer to the base image.
 *
 * @return Pointer to the created wall image, or NULL on failure.
 */
static inline t_img	*wall_t600_lonely(t_data *data, t_wall_vars vars, t_2d pos)
{
	t_img	*wall;
	t_img	*gay[4];

	if (vars.n & WALL_TOP)
	{
		if (!islesbian(data, posadd(pos, -1, 0)))
		{
			gay[0] = get_wall(data, 0, 1, data->d);
			gay[2] = get_wall(data, 0, 1, data->d);
		}
		else
		{
			gay[0] = get_wall(data, 1, 1, data->d);
			gay[2] = get_wall(data, 1, 1, data->d);
		}
		if (!islesbian(data, posadd(pos, 1, 0)))
		{
			gay[1] = get_wall(data, 2, 1, data->d);
			gay[3] = get_wall(data, 2, 1, data->d);
		}
		else
		{
			gay[1] = get_wall(data, 1, 1, data->d);
			gay[3] = get_wall(data, 1, 1, data->d);
		}
	}
	else if (vars.n & WALL_LEFT)
	{
		if (!islesbian(data, posadd(pos, 0, -1)))
		{
			gay[0] = get_wall(data, 1, 0, data->d);
			gay[1] = get_wall(data, 1, 0, data->d);
		}
		else
		{
			gay[0] = get_wall(data, 1, 1, data->d);
			gay[1] = get_wall(data, 1, 1, data->d);
		}
		if (!islesbian(data, posadd(pos, 0, 1)))
		{
			gay[2] = get_wall(data, 1, 2, data->d);
			gay[3] = get_wall(data, 1, 2, data->d);
		}
		else
		{
			gay[2] = get_wall(data, 1, 1, data->d);
			gay[3] = get_wall(data, 1, 1, data->d);
		}
	}
	else
		log_error("WHAT THE FUCK IS THAT GAY WALL DOING HERE", __FILE__,
			__LINE__);
	if (!(gay[0] && gay[1] && gay[2] && gay[3]))
		return (NULL);
	wall = crust_img_new(data->mlx, 32, 32);
	if (!wall)
		return (NULL);
	crust_img_draw(wall, gay[0], (t_2d){0, 0});
	crust_img_draw(wall, gay[1], (t_2d){16, 0});
	crust_img_draw(wall, gay[2], (t_2d){0, 16});
	crust_img_draw(wall, gay[3], (t_2d){16, 16});
	return (wall);
}

/**
 * @brief Creates a wall image for configurations with two adjacent walls.
 *
 * This function handles wall sections with exactly two adjacent wall neighbors.
 * It delegates to either wall_t600_connected (for L-shaped corners) or
 * wall_t600_lonely (for straight wall sections) based on the specific
 * configuration of neighboring walls.
 *
 * @param data Pointer to the main data structure.
 * @param map Pointer to the map structure.
 * @param vars Wall variables containing position and neighbor information.
 * @param img Pointer to the base image.
 *
 * @return Pointer to the created wall image, or NULL on failure.
 */
t_img	*wall_t600(t_data *data, t_wall_vars vars, t_2d pos)
{
	t_img	*wall;
	bool	connected;

	connected = vars.n & (WALL_TOP | WALL_BOTTOM)
		&& vars.n & (WALL_LEFT | WALL_RIGHT);
	if (connected)
	{
		wall = wall_t600_connected(data, vars, pos);
	}
	else
	{
		wall = wall_t600_lonely(data, vars, pos);
	}
	return (wall);
}

/**
 * @brief Determines wall tile image based on adjacent wall positions
 *
 * This function selects appropriate wall tile images based on the presence
 * or absence of adjacent walls in different directions (top, bottom, left,
 * right).
 * The selection is determined by the bit flags in the vars.n parameter.
 *
 * @param data  Pointer to the game data structure
 * @param map   Pointer to the map structure
 * @param vars  Structure containing wall variables and neighbor bitflags
 * @param img   Input image pointer (unused in current implementation)
 *
 * @return      Pointer to the selected wall tile image
 *
 * @note        This function appears incomplete as it doesn't assign the wall
 *              variable or include a return statement
 */
static inline t_img	*wall_tbi(t_data *data, t_wall_vars vars, t_2d pos)
{
	t_img	*wall;
	t_img	*gay[4];

	if (isasexual(data, pos))
	{
		gay[0] = get_wall(data, 1, 1, data->d);
		gay[1] = get_wall(data, 1, 1, data->d);
		gay[2] = get_wall(data, 1, 1, data->d);
		gay[3] = get_wall(data, 1, 1, data->d);
	}
	else if (!(vars.n & WALL_BOTTOM))
	{
		gay[0] = get_wall(data, 1, 1, data->d);
		gay[1] = get_wall(data, 1, 1, data->d);
		gay[2] = get_wall(data, 1, 2, data->d);
		gay[3] = get_wall(data, 1, 2, data->d);
	}
	else if (!(vars.n & WALL_TOP))
	{
		gay[0] = get_wall(data, 1, 0, data->d);
		gay[1] = get_wall(data, 1, 0, data->d);
		gay[2] = get_wall(data, 1, 1, data->d);
		gay[3] = get_wall(data, 1, 1, data->d);
	}
	else if (!(vars.n & WALL_RIGHT))
	{
		gay[0] = get_wall(data, 1, 1, data->d);
		gay[1] = get_wall(data, 2, 1, data->d);
		gay[2] = get_wall(data, 1, 1, data->d);
		gay[3] = get_wall(data, 2, 1, data->d);
	}
	else if (!(vars.n & WALL_LEFT))
	{
		gay[0] = get_wall(data, 2, 1, data->d);
		gay[1] = get_wall(data, 1, 1, data->d);
		gay[2] = get_wall(data, 2, 1, data->d);
		gay[3] = get_wall(data, 1, 1, data->d);
	}
	wall = crust_img_new(data->mlx, 32, 32);
	if (!wall)
		return (NULL);
	crust_img_draw(wall, gay[0], (t_2d){0, 0});
	crust_img_draw(wall, gay[1], (t_2d){16, 0});
	crust_img_draw(wall, gay[2], (t_2d){0, 16});
	crust_img_draw(wall, gay[3], (t_2d){16, 16});
	return (wall);
}

inline t_img	*wall_no(t_data *data)
{
	t_img	*wall;
	t_img	*none;

	wall = crust_img_new(data->mlx, 32, 32);
	if (!wall)
		return (NULL);
	none = get_wall(data, 1, 1, false);
	if (!none)
		return (NULL);
	crust_img_draw(wall, none, (t_2d){0, 0});
	crust_img_draw(wall, none, (t_2d){16, 0});
	crust_img_draw(wall, none, (t_2d){0, 16});
	crust_img_draw(wall, none, (t_2d){16, 16});
	return (wall);
}

/**
	* @brief Renders a wall tile at the specified position.
	*
	* This function determines the appropriate wall image to render based on
	* neighboring wall configurations and renders it at the specified position.
	* It selects different wall types (hull, T-bone, t600,
		t800) based on the
	* number of adjacent walls.
	*
	* @param data Pointer to the main data structure.
	* @param map Pointer to the map structure.
	* @param pos The position where the wall should be rendered.
	* @param img Pointer to the base image.
	*/
void	render_wall(t_data *data, t_map *map, t_2d pos, t_img *img)
{
	t_wall_vars	vars;
	t_img		*wall;
	int			n;

	vars.n = find_neighbours_extended(map, pos.x, pos.y);
	if (!data->set)
		return ;
	n = get_neighbour_count(vars.n);
	if (n == 0)
		wall = wall_hull(data);
	else if (n == 1)
		wall = wall_tbone(data, vars);
	else if (n == 2)
		wall = wall_t600(data, vars, pos);
	else if (n == 3)
		wall = wall_tbi(data, vars, pos);
	else
		wall = wall_no(data);
	if (wall)
	{
		crust_img_draw(img, wall, (t_2d){pos.x * 32, pos.y * 32});
		crust_img_drop(wall);
	}
	else
		log_error("Wall rendering failed, dumbass", __FILE__, __LINE__);
	log_debug("End of wall rendering process for wall at (%d, %d)", __FILE__,
		__LINE__, pos.x, pos.y);
	return ;
}

void	just_render_walls(t_data *data)
{
	t_2d	pos;

	pos.y = 0;
	while (pos.y < data->map->size.y)
	{
		pos.x = 0;
		while (pos.x < data->map->size.x)
		{
			if (data->map->map[pos.y][pos.x] == '1' && !isgay(data, pos))
				render_wall(data, data->map, pos, data->floor);
			pos.x++;
		}
		pos.y++;
	}
}
