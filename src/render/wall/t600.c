/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t600.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 10:57:45 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/27 11:00:28 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

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
