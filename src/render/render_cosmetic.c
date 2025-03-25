/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_cosmetic.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:42:56 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/18 14:00:22 by lfiorell         ###   ########.fr       */
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

static inline void	setup_nums(t_data *fuckno)
{
	int	i;

	if (fuckno->collectibles || fuckno->col_available)
		return (log_error("collectibles or col_available already set", __FILE__,
				__LINE__));
	fuckno->collectibles = ft_calloc(fuckno->map->size.y, sizeof(int8_t *));
	fuckno->col_available = ft_calloc(fuckno->map->size.y, sizeof(bool *));
	i = 0;
	while (i < fuckno->map->size.y)
	{
		fuckno->collectibles[i] = ft_calloc(fuckno->map->size.x,
				sizeof(int8_t));
		ft_memset(fuckno->collectibles[i], -1, fuckno->map->size.x);
		fuckno->col_available[i] = ft_calloc(fuckno->map->size.x, sizeof(bool));
		i++;
	}
}

static inline void	setup_collectibles(t_data *fuckno)
{
	int	i;
	int	j;

	i = 0;
	while (i < fuckno->map->size.y)
	{
		j = 0;
		while (j < fuckno->map->size.x)
		{
			if (fuckno->map->map[i][j] == 'C')
			{
				fuckno->collectibles[i][j] = ft_rand_int(1, 3);
				fuckno->col_available[i][j] = true;
			}
			j++;
		}
		i++;
	}
}

static inline void	eeemages(t_2d *imgs)
{
	imgs[0] = (t_2d){4, 14};
	imgs[1] = (t_2d){5, 14};
	imgs[2] = (t_2d){4, 15};
	imgs[3] = (t_2d){5, 15};
}

void	render_cosmetic(t_data *data, t_map *map, t_2d pos, t_img *img)
{
	t_2d	images[4];
	t_img	*img_to_draw;
	t_2d	pos;
	t_img	*new;

	if (!data->collectibles || !data->col_available)
	{
		setup_nums(data);
		setup_collectibles(data);
	}
	eeemages(images);
	if (data->collectibles[pos.y][pos.x] != -1)
	{
		pos = images[data->collectibles[pos.y][pos.x]];
		img_to_draw = crust_set_get_img_by_pos(data->set, pos);
		if (!img_to_draw)
			return ;
		new = crust_img_scale(img_to_draw, (t_2d){16, 16},
				CRUST_IMG_SCALE_NEAREST);
		if (!new)
			return ;
		crust_img_draw(img, new, (t_2d){pos.x * 32, pos.y * 32});
		crust_img_destroy(new);
	}
}
