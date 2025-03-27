/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t600_con.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 10:58:49 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/27 15:23:01 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Crust/img/scale.h"
#include "render.h"
#include "utils.h"

/* Helper function to create the final wall image */
t_img	*create_wall_image(void *mlx, t_img *gay[4])
{
	t_img	*wall;

	wall = crust_img_new(mlx, 32, 32);
	if (!wall)
		return (NULL);
	if (gay[0])
		crust_img_draw(wall, gay[0], (t_2d){0, 0});
	if (gay[1])
		crust_img_draw(wall, gay[1], (t_2d){16, 0});
	if (gay[2])
		crust_img_draw(wall, gay[2], (t_2d){0, 16});
	if (gay[3])
		crust_img_draw(wall, gay[3], (t_2d){16, 16});
	if (gay[0])
		crust_img_drop(gay[0]);
	if (gay[1])
		crust_img_drop(gay[1]);
	if (gay[2])
		crust_img_drop(gay[2]);
	if (gay[3])
		crust_img_drop(gay[3]);
	return (wall);
}

t_img	*wall_t600_connected_right(t_data *data, t_wall_vars vars)
{
	t_img	*gay[4];
	t_img	*final_wall;
	int8_t	n;

	n = vars.n;
	ft_bzero(gay, sizeof(gay));
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
	final_wall = create_wall_image(data->mlx, gay);
	return (final_wall);
}

t_img	*wall_t600_connected_left(t_data *data, t_wall_vars vars)
{
	t_img	*gay[4];
	t_img	*final_wall;
	int8_t	n;

	n = vars.n;
	ft_bzero(gay, sizeof(gay));
	if ((n & WALL_LEFT) && (n & WALL_TOP))
	{
		gay[0] = get_wall(data, 1, 1, data->d);
		gay[1] = get_wall(data, 1, 2, data->d);
		gay[2] = get_wall(data, 2, 1, data->d);
		gay[3] = get_wall(data, 2, 2, data->d);
	}
	else if ((n & WALL_LEFT) && (n & WALL_BOTTOM))
	{
		gay[0] = get_wall(data, 0, 1, data->d);
		gay[1] = get_wall(data, 2, 0, data->d);
		gay[2] = get_wall(data, 1, 1, data->d);
		gay[3] = get_wall(data, 2, 1, data->d);
	}
	final_wall = create_wall_image(data->mlx, gay);
	return (final_wall);
}

t_img	*wall_t600_connected(t_data *data, t_wall_vars vars, t_2d pos)
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
