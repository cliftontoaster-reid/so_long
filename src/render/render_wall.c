/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 13:13:41 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/27 12:46:35 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Crust/img/img.h"
#include "Crust/img/scale.h"
#include "Crust/img/set.h"
#include "render.h"
#include "utils.h"

/**
 * @brief Creates wall segments based on neighboring wall configuration
 *
 * @param data Game data pointer
 * @param config Wall configuration structure containing segment coordinates
 * @return t_img* Composed wall tile, or NULL if creation failed
 */
t_img	*create_wall_tile(t_data *data, t_wall_config config)
{
	t_img	*wall;
	t_img	*segments[4];

	segments[0] = get_wall(data, config.x1, config.y1, data->d);
	segments[1] = get_wall(data, config.x2, config.y2, data->d);
	segments[2] = get_wall(data, config.x3, config.y3, data->d);
	segments[3] = get_wall(data, config.x4, config.y4, data->d);
	if (!segments[0] || !segments[1] || !segments[2] || !segments[3])
	{
		log_error("Failed to create wall segments", __FILE__, __LINE__);
		return (NULL);
	}
	wall = crust_img_new(data->mlx, 32, 32);
	if (!wall)
		return (NULL);
	crust_img_draw(wall, segments[0], (t_2d){0, 0});
	crust_img_draw(wall, segments[1], (t_2d){16, 0});
	crust_img_draw(wall, segments[2], (t_2d){0, 16});
	crust_img_draw(wall, segments[3], (t_2d){16, 16});
	crust_img_drop(segments[0]);
	crust_img_drop(segments[1]);
	crust_img_drop(segments[2]);
	crust_img_drop(segments[3]);
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
	crust_img_drop(none);
	return (wall);
}

/**
 * @brief Selects the appropriate wall image based on neighbor configuration.
 *
 * This function determines which wall image to use based on the number of
 * neighboring walls. It returns the appropriate image for rendering.
 *
 * @param data Pointer to the main data structure.
 * @param vars Wall variables containing neighbor information.
 * @param pos The position where the wall should be rendered.
 * @return Pointer to the selected wall image, or NULL on failure.
 */
t_img	*select_wall_image(t_data *data, t_wall_vars vars, t_2d pos)
{
	int		n;
	t_img	*wall;

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
	return (wall);
}

/**
 * @brief Renders a wall tile at the specified position.
 *
 * This function determines the appropriate wall image to render based on
 * neighboring wall configurations and renders it at the specified position.
 * It selects different wall types (hull, T-bone, t600, t800) based on the
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

	vars.n = find_neighbours_extended(map, pos.x, pos.y);
	if (!data->set)
		return ;
	wall = select_wall_image(data, vars, pos);
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
	log_debug("End of wall rendering process for wall at (%d, %d)", __FILE__,
		__LINE__, pos.x, pos.y);
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
