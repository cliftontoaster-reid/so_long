/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_cosmetic.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:42:56 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/28 13:19:05 by lfiorell         ###   ########.fr       */
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

inline void	eeemages(t_2d *imgs, t_data *data)
{
	imgs[0] = (t_2d){4 + (data->d * 8), 14};
	imgs[1] = (t_2d){5 + (data->d * 8), 14};
	imgs[2] = (t_2d){4 + (data->d * 8), 15};
	imgs[3] = (t_2d){5 + (data->d * 8), 15};
}

inline void	render_nonconsumed(t_2d *images, t_data *data, t_2d pos, t_img *img)
{
	t_img	*col;
	t_2d	newpos;
	t_img	*new;

	col = crust_set_get_img_by_pos(data->set,
			images[data->collectibles[pos.y][pos.x]]);
	if (!col)
		return ;
	new = crust_img_scale(col, (t_2d){20, 20}, CRUST_IMG_SCALE_NEAREST);
	crust_img_drop(col);
	if (!new)
		return ;
	log_debug("Drawing collectible", __FILE__, __LINE__);
	newpos.x = pos.x * 32 + (32 - 20) / 2;
	newpos.y = pos.y * 32 + (32 - 20) / 2;
	crust_img_draw(img, new, newpos);
	crust_img_drop(new);
}

inline void	render_consumed(t_2d *images, t_data *data, t_2d pos, t_img *img)
{
	t_img	*col;
	t_2d	newpos;
	t_img	*new;

	col = crust_set_get_img_by_pos(data->set, images[0]);
	if (!col)
		return ;
	new = crust_img_scale(col, (t_2d){20, 20}, CRUST_IMG_SCALE_NEAREST);
	crust_img_drop(col);
	if (!new)
		return ;
	log_debug("Drawing collectible", __FILE__, __LINE__);
	newpos.x = pos.x * 32 + (32 - 20) / 2;
	newpos.y = pos.y * 32 + (32 - 20) / 2;
	crust_img_draw(img, new, newpos);
	crust_img_drop(new);
}

void	render_cosmetic(t_data *data, t_map *map, t_2d pos, t_img *img)
{
	t_2d	images[4];

	(void)map;
	eeemages(images, data);
	if (data->collectibles[pos.y][pos.x] != -1)
	{
		if (data->col_available[pos.y][pos.x])
			render_nonconsumed(images, data, pos, img);
		else
			render_consumed(images, data, pos, img);
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
