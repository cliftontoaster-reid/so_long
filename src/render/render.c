/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 15:31:41 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/31 12:36:06 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Crust/img/img.h"
#include "Crust/img/scale.h"
#include "mlx.h"
#include "render.h"
#include "utils.h"
#include <math.h>

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

void	prescale(t_data *data)
{
	t_2d	new_size;

	if (data->floorsc)
		crust_img_drop(data->floorsc);
	new_size.x = data->floor->width * data->scale;
	new_size.y = data->floor->height * data->scale;
	data->floorsc = crust_img_scale(data->floor, new_size,
			CRUST_IMG_SCALE_NEAREST);
	crust_img_drop(data->img);
	data->img = crust_img_new(data->mlx, new_size.x, new_size.y);
}

static inline void	printscrn(t_data *data)
{
	t_2d	scaled;

	scaled.x = data->scale * data->map->size.x * 32;
	scaled.y = data->scale * data->map->size.y * 32;
	crust_img_cpy(data->img, data->floorsc, (t_2d){0, 0}, (t_2d){scaled.x,
		scaled.y});
	render_cosmetics(data);
	just_render_exit(data);
	render_guy(data);
	render_dummies(data);
	if (!data || !data->mlx || !data->win || !data->img || !data->img->img_ptr)
		return ;
	mlx_put_image_to_window(data->mlx, data->win, data->img->img_ptr, 0, 0);
}

#include <time.h>

void	render(t_data *data, t_map *map)
{
	double	elapsed_ms;

	clock_t start, end;
	start = clock();
	if (!data || !map)
		return ;
	data->map = map;
	if (!data->floor)
		prerender(data);
	if (!data->floorsc || data->floorsc->width != data->floor->width
		* data->scale || data->floorsc->height != data->floor->height
		* data->scale)
		prescale(data);
	printscrn(data);
	end = clock();
	elapsed_ms = (end - start) * 1000000.0 / CLOCKS_PER_SEC;
	log_debug("Render CPU time: %x micro-seconds", __FILE__, __LINE__,
		(int)elapsed_ms);
}
