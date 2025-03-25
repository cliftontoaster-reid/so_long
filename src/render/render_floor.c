/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_floor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:33:12 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/18 15:48:28 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "img/img.h"
#include "img/set.h"
#include "render.h"

static inline t_img	*get_floor(t_set *set)
{
	t_2d	images[9];
	int		rand;

	images[0] = (t_2d){0, 2};
	images[1] = (t_2d){1, 0};
	images[2] = (t_2d){1, 1};
	images[3] = (t_2d){1, 2};
	images[4] = (t_2d){2, 0};
	images[5] = (t_2d){2, 1};
	images[6] = (t_2d){2, 2};
	images[7] = (t_2d){3, 2};
	images[8] = (t_2d){4, 2};
	rand = ft_rand_int(0, 8);
	return (crust_set_get_img_by_pos(set, images[rand]));
}

static inline void	draw_random(t_img *base, t_2d pos, t_set *set)
{
	t_img	*random;
	t_2d	scaled_pos;

	random = get_floor(set);
	if (!random)
		return ;
	scaled_pos = pos_scale(pos, (t_2d){base->width, base->height}, 2);
	crust_img_draw(base, random, scaled_pos);
	crust_img_destroy(random);
}

t_img	*create_floor(t_data *data)
{
	t_img	*floors;
	t_2d	poses[4];

	floors = crust_img_new(data->mlx, 16 * 2, 16 * 2);
	if (!floors)
		return ;
	poses[0] = (t_2d){0, 0};
	poses[1] = (t_2d){16, 0};
	poses[2] = (t_2d){0, 16};
	poses[3] = (t_2d){16, 16};
	draw_random(floors, poses[0], data->set);
	draw_random(floors, poses[1], data->set);
	draw_random(floors, poses[2], data->set);
	draw_random(floors, poses[3], data->set);
}

void	render_floor(t_data *data, t_map *map, t_2d pos, t_img *img)
{
	t_img	*floors;

	floors = create_floor(data);
	if (!floors)
		return ;
	crust_img_draw(img, floors, (t_2d){pos.x * 32, pos.y * 32});
	crust_img_destroy(floors);
}
