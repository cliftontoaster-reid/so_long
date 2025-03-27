/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 13:24:44 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/27 13:27:30 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"

static inline void	free_matrix(void **matrix, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

void	drop_map(t_map *map)
{
	if (map)
	{
		free_matrix((void **)map->map, map->size.y);
		free(map);
	}
}

void	delete_data(t_data *data)
{
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->set)
		crust_set_drop(data->set);
	if (data->guy)
		crust_set_drop(data->guy);
	if (data->img)
		crust_img_drop(data->img);
	if (data->floor)
		crust_img_drop(data->floor);
	if (data->col_available)
		free_matrix((void **)data->col_available, data->map->size.y);
	if (data->collectibles)
		free_matrix((void **)data->collectibles, data->map->size.y);
	if (data->wall_vars)
		free_matrix((void **)data->wall_vars, data->map->size.y);
	if (data->map)
		drop_map(data->map);
	if (data->rndwall)
		free_matrix((void **)data->rndwall, data->map->size.y);
	free(data);
}
