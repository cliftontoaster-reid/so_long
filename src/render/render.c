/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 15:31:41 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/27 15:46:59 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Crust/img/img.h"
#include "Crust/img/scale.h"
#include "mlx.h"
#include "render.h"

static inline void	render_floors(t_data *data)
{
	t_2d	pos;

	data->floor = crust_img_new(data->mlx, data->map->size.x * 32,
			data->map->size.y * 32);
	if (!data->floor)
		return ;
	pos.y = 0;
	while (pos.y < data->map->size.y)
	{
		pos.x = 0;
		while (pos.x < data->map->size.x)
		{
			render_floor(data, data->map, pos, data->floor);
			pos.x++;
		}
		pos.y++;
	}
}

void	prerender(t_data *data)
{
	setup_cosmetics(data);
	render_floors(data);
	just_render_walls(data);
}

static inline void	printscrn(t_data *data)
{
	t_img	*scaled;

	scaled = crust_img_scale(data->img, (t_2d){data->img->width * 2,
			data->img->height * 2}, CRUST_IMG_SCALE_NEAREST);
	if (!scaled)
		return ;
	mlx_put_image_to_window(data->mlx, data->win, scaled->img_ptr, 0, 0);
	crust_img_drop(scaled);
}

void	render(t_data *data, t_map *map)
{
	if (!data || !map)
		return ;
	if (!data->floor)
		prerender(data);
	crust_img_cpy(data->img, data->floor, (t_2d){0, 0}, (t_2d){data->img->width,
		data->img->height});
	render_cosmetics(data);
	just_render_exit(data);
	render_guy(data);
	if (data->win)
		printscrn(data);
}
