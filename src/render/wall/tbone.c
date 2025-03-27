/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tbone.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 10:48:25 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/27 10:54:25 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

inline t_img	*wall_tbone_top_bottom(t_data *data, t_wall_vars vars,
		t_img *gay[4])
{
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
	return (gay[4]);
}

inline t_img	*wall_tbone_left_right(t_data *data, t_wall_vars vars,
		t_img *gay[4])
{
	if (vars.n & WALL_LEFT)
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
	return (gay[4]);
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
inline t_img	*wall_tbone(t_data *data, t_wall_vars vars)
{
	t_img	*wall;
	t_img	*gay[4];

	wall = crust_img_new(data->mlx, 32, 32);
	if (!wall)
		return (NULL);
	wall_tbone_top_bottom(data, vars, gay);
	wall_tbone_left_right(data, vars, gay);
	crust_img_draw(wall, gay[0], (t_2d){0, 0});
	crust_img_draw(wall, gay[1], (t_2d){16, 0});
	crust_img_draw(wall, gay[2], (t_2d){0, 16});
	crust_img_draw(wall, gay[3], (t_2d){16, 16});
	crust_img_drop(gay[0]);
	crust_img_drop(gay[1]);
	crust_img_drop(gay[2]);
	crust_img_drop(gay[3]);
	return (wall);
}
