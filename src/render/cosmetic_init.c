/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cosmetic_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 13:18:32 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/28 13:18:37 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

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
