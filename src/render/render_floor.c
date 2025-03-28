/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_floor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:33:12 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/28 10:19:33 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Crust/img/img.h"
#include "Crust/img/set.h"
#include "render.h"
#include "utils.h"

static inline t_img	*get_floor(t_data *data)
{
	t_2d	images[9];
	int		rand;

	images[0] = (t_2d){2, 0 + data->d * 5};
	images[1] = (t_2d){0, 1 + data->d * 5};
	images[2] = (t_2d){1, 1 + data->d * 5};
	images[3] = (t_2d){2, 1 + data->d * 5};
	images[4] = (t_2d){0, 2 + data->d * 5};
	images[5] = (t_2d){1, 2 + data->d * 5};
	images[6] = (t_2d){2, 2 + data->d * 5};
	images[7] = (t_2d){2, 3 + data->d * 5};
	images[8] = (t_2d){2, 4 + data->d * 5};
	rand = ft_rand_int(0, 8);
	(void)rand;
	return (crust_set_get_img_by_pos(data->set, images[rand]));
}

static inline void	draw_random(t_img *base, t_2d pos, t_data *data)
{
	t_img	*random;

	random = get_floor(data);
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
	draw_random(floors, poses[0], data);
	draw_random(floors, poses[1], data);
	draw_random(floors, poses[2], data);
	draw_random(floors, poses[3], data);
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
	{
		log_error("Failed to create floor", __FILE__, __LINE__);
		return ;
	}
	crust_img_draw(img, floors, (t_2d){pos.x * 32, pos.y * 32});
	crust_img_drop(floors);
	log_debug("Floor rendered at position x: %d, y: %d", __FILE__, __LINE__,
		pos.x, pos.y);
}
