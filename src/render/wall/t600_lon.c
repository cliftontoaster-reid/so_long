/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t600_lon.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 10:59:45 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/27 14:30:05 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "utils.h"

void	wall_t600_lonely_top(t_data *data, t_2d pos, t_img *gay[4])
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

void	wall_t600_lonely_left(t_data *data, t_2d pos, t_img *gay[4])
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

t_img	*wall_t600_lonely(t_data *data, t_wall_vars vars, t_2d pos)
{
	t_img	*wall;
	t_img	*gay[4];

	if (vars.n & WALL_TOP)
		wall_t600_lonely_top(data, pos, gay);
	else if (vars.n & WALL_LEFT)
		wall_t600_lonely_left(data, pos, gay);
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
	crust_img_drop(gay[0]);
	crust_img_drop(gay[1]);
	crust_img_drop(gay[2]);
	crust_img_drop(gay[3]);
	return (wall);
}
