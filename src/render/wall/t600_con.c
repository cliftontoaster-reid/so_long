/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t600_con.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 10:58:49 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/27 11:21:53 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Crust/img/scale.h"
#include "render.h"
#include "utils.h"

/* Helper function to create the final wall image */
inline t_img	*create_wall_image(void *mlx, t_img *gay[4])
{
	t_img	*wall;

	if (!(gay[0] && gay[1] && gay[2] && gay[3]))
		return (NULL);
	wall = crust_img_new(mlx, 32, 32);
	if (!wall)
		return (NULL);
	crust_img_draw(wall, gay[0], (t_2d){0, 0});
	crust_img_draw(wall, gay[1], (t_2d){16, 0});
	crust_img_draw(wall, gay[2], (t_2d){0, 16});
	crust_img_draw(wall, gay[3], (t_2d){16, 16});
	return (wall);
}

t_img	*wall_t600_connected_right(t_data *data, t_wall_vars vars)
{
	t_img	*gay[4];
	int8_t	n;

	n = vars.n;
	if ((n & WALL_RIGHT) && (n & WALL_TOP))
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
	return (create_wall_image(data->mlx, gay));
}

t_img	*wall_t600_connected_left(t_data *data, t_wall_vars vars)
{
	t_img	*gay[4];
	int8_t	n;

	n = vars.n;
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
	return (create_wall_image(data->mlx, gay));
}

inline t_img	*wall_t600_connected(t_data *data, t_wall_vars vars, t_2d pos)
{
	int8_t	n;
	t_img	*wall;
	t_img	*scaled;

	n = vars.n;
	if (!is600cornered(data, vars, pos))
	{
		wall = get_wall(data, 1, 1, false);
		scaled = crust_img_scale(wall, (t_2d){32, 32}, CRUST_IMG_SCALE_NEAREST);
		crust_img_drop(wall);
		return (scaled);
	}
	if (n & WALL_LEFT)
		return (wall_t600_connected_left(data, vars));
	else
		return (wall_t600_connected_right(data, vars));
}
