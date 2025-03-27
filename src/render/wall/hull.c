/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hull.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 10:47:02 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/27 12:44:06 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

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
	gay[0] = crust_set_get_img_by_pos(data->set, (t_2d){WALLBASE, 0 + data->d
			* 5});
	gay[1] = crust_set_get_img_by_pos(data->set, (t_2d){WALLBASE + 2, 0
			+ data->d * 5});
	gay[2] = crust_set_get_img_by_pos(data->set, (t_2d){WALLBASE, 2 + data->d
			* 5});
	gay[3] = crust_set_get_img_by_pos(data->set, (t_2d){WALLBASE + 2, 2
			+ data->d * 5});
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
