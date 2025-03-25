/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 13:13:41 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/25 15:58:13 by lfiorell         ###   ########.fr       */
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
	if (pos.x < 0 || pos.y < 0 || pos.x >= data->map->size.x
		|| pos.y >= data->map->size.y)
		return (true);
	if (data->map->map[pos.y][pos.x] != '1')
		return (true);
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
inline t_img	*get_wall(t_data *data, int x, int y)
{
	t_2d	pos;
	t_img	*img;

	pos = (t_2d){WALLBASE + x, y};
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
		if (isgay(data, posadd(vars.pos, 0, -1)))
		{
			gay[0] = get_wall(data, 1, 3);
			gay[1] = get_wall(data, 1, 3);
		}
		else
		{
			gay[0] = get_wall(data, 1, 1);
			gay[1] = get_wall(data, 1, 1);
		}
		gay[2] = get_wall(data, 1, 2);
		gay[3] = get_wall(data, 1, 2);
	}
	else if (vars.n & WALL_BOTTOM)
	{
		gay[0] = get_wall(data, 1, 0);
		gay[1] = get_wall(data, 1, 0);
		if (isgay(data, posadd(vars.pos, 0, 1)))
		{
			gay[2] = get_wall(data, 1, 1);
			gay[3] = get_wall(data, 1, 1);
		}
		else
		{
			gay[2] = get_wall(data, 1, 2);
			gay[3] = get_wall(data, 1, 2);
		}
	}
	else if (vars.n & WALL_LEFT)
	{
		if (isgay(data, posadd(vars.pos, -1, 0)))
		{
			gay[0] = get_wall(data, 1, 3);
			gay[2] = get_wall(data, 1, 3);
		}
		else
		{
			gay[0] = get_wall(data, 1, 1);
			gay[2] = get_wall(data, 1, 1);
		}
		gay[1] = get_wall(data, 2, 1);
		gay[3] = get_wall(data, 2, 1);
	}
	else if (vars.n & WALL_RIGHT)
	{
		if (isgay(data, posadd(vars.pos, 1, 0)))
		{
			gay[1] = get_wall(data, 1, 3);
			gay[3] = get_wall(data, 1, 3);
		}
		else
		{
			gay[1] = get_wall(data, 1, 1);
			gay[3] = get_wall(data, 1, 1);
		}
		gay[0] = get_wall(data, 0, 1);
		gay[2] = get_wall(data, 0, 1);
	}
	crust_img_draw(wall, gay[0], (t_2d){0, 0});
	crust_img_draw(wall, gay[1], (t_2d){16, 0});
	crust_img_draw(wall, gay[2], (t_2d){0, 16});
	crust_img_draw(wall, gay[3], (t_2d){16, 16});
	return (wall);
}

/**
 * @brief Creates a wall image for connected corners.
 *
 * This function generates a 32x32 pixel wall image for a corner where two walls
 * connect (such as an L-shape). The corner appearance varies based on which
 * directions (top-left, top-right, bottom-left,
	bottom-right) the walls connect.
 *
 * @param data Pointer to the main data structure.
 * @param map Pointer to the map structure.
 * @param vars Wall variables containing position and neighbor information.
 * @param img Pointer to the base image.
 *
 * @return Pointer to the created wall image, or NULL on failure.
 */
static inline t_img	*wall_t600_connected(t_data *data, t_wall_vars vars)
{
	t_img	*wall;
	t_img	*gay[4];

	if (vars.n & (WALL_LEFT | WALL_TOP))
	{
		gay[0] = get_wall(data, 1, 1);
		gay[1] = get_wall(data, 1, 2);
		gay[2] = get_wall(data, 1, 2);
		gay[3] = get_wall(data, 2, 2);
	}
	else if (vars.n & (WALL_LEFT | WALL_BOTTOM))
	{
		gay[0] = get_wall(data, 0, 1);
		gay[1] = get_wall(data, 2, 0);
		gay[2] = get_wall(data, 1, 1);
		gay[3] = get_wall(data, 2, 1);
	}
	else if (vars.n & (WALL_RIGHT | WALL_TOP))
	{
		gay[0] = get_wall(data, 0, 1);
		gay[1] = get_wall(data, 1, 1);
		gay[2] = get_wall(data, 0, 2);
		gay[3] = get_wall(data, 1, 2);
	}
	else if (vars.n & (WALL_RIGHT | WALL_BOTTOM))
	{
		gay[0] = get_wall(data, 0, 0);
		gay[1] = get_wall(data, 1, 0);
		gay[2] = get_wall(data, 0, 1);
		gay[3] = get_wall(data, 1, 1);
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
static inline t_img	*wall_t600_lonely(t_data *data, t_wall_vars vars)
{
	t_img	*wall;
	t_img	*gay[4];

	if (vars.n & WALL_TOP)
	{
		gay[0] = get_wall(data, 0, 1);
		gay[1] = get_wall(data, 2, 1);
		gay[2] = get_wall(data, 0, 1);
		gay[3] = get_wall(data, 2, 1);
	}
	else if (vars.n & WALL_LEFT)
	{
		gay[0] = get_wall(data, 1, 0);
		gay[1] = get_wall(data, 1, 0);
		gay[2] = get_wall(data, 1, 2);
		gay[3] = get_wall(data, 1, 2);
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
t_img	*wall_t600(t_data *data, t_wall_vars vars)
{
	t_img	*wall;
	bool	connected;

	connected = vars.n & (WALL_TOP | WALL_BOTTOM)
		&& vars.n & (WALL_LEFT | WALL_RIGHT);
	if (connected)
	{
		wall = wall_t600_connected(data, vars);
	}
	else
	{
		wall = wall_t600_lonely(data, vars);
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
static inline t_img	*wall_tbi(t_data *data, t_wall_vars vars)
{
	t_img	*wall;
	t_img	*gay[4];

	if (!(vars.n & WALL_BOTTOM))
	{
		gay[0] = get_wall(data, 1, 1);
		gay[1] = get_wall(data, 1, 1);
		gay[2] = get_wall(data, 1, 2);
		gay[3] = get_wall(data, 1, 2);
	}
	else if (!(vars.n & WALL_TOP))
	{
		gay[0] = get_wall(data, 1, 0);
		gay[1] = get_wall(data, 1, 0);
		gay[2] = get_wall(data, 1, 1);
		gay[3] = get_wall(data, 1, 1);
	}
	else if (!(vars.n & WALL_RIGHT))
	{
		gay[0] = get_wall(data, 0, 1);
		gay[1] = get_wall(data, 1, 1);
		gay[2] = get_wall(data, 0, 1);
		gay[3] = get_wall(data, 1, 1);
	}
	else if (!(vars.n & WALL_LEFT))
	{
		gay[0] = get_wall(data, 1, 1);
		gay[1] = get_wall(data, 2, 1);
		gay[2] = get_wall(data, 1, 1);
		gay[3] = get_wall(data, 1, 2);
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
	none = get_wall(data, 1, 1);
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
		wall = wall_t600(data, vars);
	else if (n == 3)
		wall = wall_tbi(data, vars);
	else
		wall = wall_no(data);
	if (wall)
	{
		crust_img_draw(img, wall, (t_2d){pos.x * 32, pos.y * 32});
		crust_img_drop(wall);
	}
	else
		log_error("Wall rendering failed, dumbass", __FILE__, __LINE__);
	log_info("End of wall rendering process", __FILE__, __LINE__);
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
			if (data->map->map[pos.y][pos.x] == '1')
				render_wall(data, data->map, pos, data->img);
			pos.x++;
		}
		pos.y++;
	}
}
