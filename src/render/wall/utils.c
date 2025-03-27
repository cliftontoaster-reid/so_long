/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 10:43:58 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/27 14:26:59 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

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
t_2d	posadd(t_2d a, int x, int y)
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
t_img	*get_wall(t_data *data, int x, int y, bool colour)
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
