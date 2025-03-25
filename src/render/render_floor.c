/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_floor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:33:12 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/25 14:17:52 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Crust/img/img.h"
#include "Crust/img/set.h"
#include "render.h"

static inline t_img	*get_floor(t_set *set)
{
	t_2d	images[9];
	int		rand;

	images[0] = (t_2d){2, 0};
	images[1] = (t_2d){0, 1};
	images[2] = (t_2d){1, 1};
	images[3] = (t_2d){2, 1};
	images[4] = (t_2d){0, 2};
	images[5] = (t_2d){1, 2};
	images[6] = (t_2d){2, 2};
	images[7] = (t_2d){2, 3};
	images[8] = (t_2d){2, 4};
	rand = ft_rand_int(0, 8);
	(void)rand;
	return (crust_set_get_img_by_pos(set, images[rand]));
}

static inline void	draw_random(t_img *base, t_2d pos, t_set *set)
{
	t_img	*random;

	random = get_floor(set);
	if (!random)
		return ;
	crust_img_draw(base, random, pos);
	crust_img_drop(random);
}

t_img	*create_floor(t_data *data)
{
	t_img	*floors;
	t_2d	poses[4];

	floors = crust_img_new(data->mlx, 16 * 2, 16 * 2);
	if (!floors)
		return (NULL);
	poses[0] = (t_2d){0, 0};
	poses[1] = (t_2d){16, 0};
	poses[2] = (t_2d){0, 16};
	poses[3] = (t_2d){16, 16};
	draw_random(floors, poses[0], data->set);
	draw_random(floors, poses[1], data->set);
	draw_random(floors, poses[2], data->set);
	draw_random(floors, poses[3], data->set);
	return (floors);
}

void	render_floor(t_data *data, t_map *map, t_2d pos, t_img *img)
{
	t_img	*floors;
	char	c;

	c = map->map[pos.y][pos.x];
	if (c == '1')
		return ;
	floors = create_floor(data);
	if (!floors)
		return ;
	crust_img_draw(img, floors, (t_2d){pos.x * 32, pos.y * 32});
	crust_img_drop(floors);
}
