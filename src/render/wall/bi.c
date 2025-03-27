/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 12:40:35 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/27 14:26:59 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "utils.h"

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
t_img	*wall_tbi(t_data *data, t_wall_vars vars, t_2d pos)
{
	t_wall_config	config;

	if (isasexual(data, pos))
		config = (t_wall_config){1, 1, 1, 1, 1, 1, 1, 1};
	else if (!(vars.n & WALL_BOTTOM))
		config = (t_wall_config){1, 1, 1, 1, 1, 2, 1, 2};
	else if (!(vars.n & WALL_TOP))
		config = (t_wall_config){1, 0, 1, 0, 1, 1, 1, 1};
	else if (!(vars.n & WALL_RIGHT))
		config = (t_wall_config){1, 1, 2, 1, 1, 1, 2, 1};
	else if (!(vars.n & WALL_LEFT))
		config = (t_wall_config){2, 1, 1, 1, 2, 1, 1, 1};
	else
	{
		config = (t_wall_config){1, 1, 1, 1, 1, 1, 1, 1};
		log_debug("Using default wall configuration for position (%d, %d)",
			__FILE__, __LINE__, pos.x, pos.y);
	}
	return (create_wall_tile(data, config));
}
