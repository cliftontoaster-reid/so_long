/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_cosmetic.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:42:56 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/27 14:26:59 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Crust/img/img.h"
#include "Crust/img/scale.h"
#include "Crust/img/set.h"
#include "render.h"
#include "utils.h"

// images[0] = (t_2d){4, 14}; -- collected
// images[1] = (t_2d){5, 14};
// images[2] = (t_2d){4, 15};
// images[3] = (t_2d){5, 15};

static void	eeemages(t_2d *imgs, t_data *data)
{
	imgs[0] = (t_2d){4 + (data->d * 8), 14};
	imgs[1] = (t_2d){5 + (data->d * 8), 14};
	imgs[2] = (t_2d){4 + (data->d * 8), 15};
	imgs[3] = (t_2d){5 + (data->d * 8), 15};
}

void	init_cosmetic_position(t_data *data, t_2d pos)
{
	if (data->map->map[pos.y][pos.x] == 'C')
	{
		data->collectibles[pos.y][pos.x] = ft_rand_int(1, 3);
		data->col_available[pos.y][pos.x] = true;
	}
	else
	{
		data->collectibles[pos.y][pos.x] = -1;
		data->col_available[pos.y][pos.x] = false;
	}
}

void	setup_cosmetics(t_data *data)
{
	t_2d	pos;

	ft_bzero(&pos, sizeof(t_2d));
	data->collectibles = ft_calloc(data->map->size.y, sizeof(int *));
	data->col_available = ft_calloc(data->map->size.y, sizeof(bool *));
	if (!data->collectibles || !data->col_available)
		return ;
	while (pos.y < data->map->size.y)
	{
		data->collectibles[pos.y] = ft_calloc(data->map->size.x, sizeof(int));
		data->col_available[pos.y] = ft_calloc(data->map->size.x, sizeof(bool));
		if (!data->collectibles[pos.y] || !data->col_available[pos.y])
			return ;
		pos.x = 0;
		while (pos.x < data->map->size.x)
		{
			init_cosmetic_position(data, pos);
			pos.x++;
		}
		pos.y++;
	}
}

void	render_cosmetic(t_data *data, t_map *map, t_2d pos, t_img *img)
{
	t_2d	images[4];
	t_img	*img_to_draw;
	t_2d	newpos;
	t_img	*new;

	(void)map;
	eeemages(images, data);
	if (data->collectibles[pos.y][pos.x] != -1)
	{
		img_to_draw = crust_set_get_img_by_pos(data->set,
				images[data->collectibles[pos.y][pos.x]]);
		if (!img_to_draw)
			return ;
		new = crust_img_scale(img_to_draw, (t_2d){20, 20},
				CRUST_IMG_SCALE_NEAREST);
		crust_img_drop(img_to_draw);
		if (!new)
			return ;
		log_debug("Drawing collectible", __FILE__, __LINE__);
		(void)img;
		newpos.x = pos.x * 32 + (32 - 20) / 2;
		newpos.y = pos.y * 32 + (32 - 20) / 2;
		crust_img_draw(img, new, newpos);
		crust_img_drop(new);
	}
}

void	render_cosmetics(t_data *data)
{
	t_2d	pos;

	pos.y = 0;
	while (pos.y < data->map->size.y)
	{
		pos.x = 0;
		while (pos.x < data->map->size.x)
		{
			render_cosmetic(data, data->map, pos, data->img);
			pos.x++;
		}
		pos.y++;
	}
}
