/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 10:38:49 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/27 14:26:59 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Crust/img/img.h"
#include "Crust/img/set.h"
#include "render.h"
#include "utils.h"

static bool	is_won(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->map->size.y)
	{
		j = 0;
		while (j < data->map->size.x)
		{
			if (data->col_available[i][j])
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}

void	render_exit(t_data *data, t_map *map, t_2d pos, t_img *img)
{
	t_2d	ipos;
	t_2d	image_pos;
	t_2d	image_size;
	t_img	*door;

	if (!data || !map || !img)
		return ;
	ipos = map_find_exit(map);
	if (ipos.x < 0 || ipos.y < 0 || pos.x < 0 || pos.y < 0 || ipos.x != pos.x
		|| ipos.y != pos.y)
		return ;
	image_size = (t_2d){32, 24};
	if (!is_won(data))
		image_pos = (t_2d){16 * 11, 4 + 28 + (data->d * 16 * 5)};
	else
		image_pos = (t_2d){16 * 11, 8 + (data->d * 16 * 5)};
	if (!data->set)
		return ;
	door = crust_set_get_img_offgrid(data->set, image_pos, image_size);
	if (!door)
		return ;
	crust_img_draw(img, door, (t_2d){pos.x * 32, (pos.y * 32) + 8});
	crust_img_drop(door);
}

void	just_render_exit(t_data *data)
{
	t_2d	pos;

	pos.y = 0;
	while (pos.y < data->map->size.y)
	{
		pos.x = 0;
		while (pos.x < data->map->size.x)
		{
			if (data->map->map[pos.y][pos.x] == 'E')
				render_exit(data, data->map, pos, data->img);
			pos.x++;
		}
		pos.y++;
	}
}
