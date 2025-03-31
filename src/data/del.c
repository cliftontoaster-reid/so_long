/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 13:24:44 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/31 17:36:33 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "audio.h"
#include "data.h"
#include "mlx.h"
#include "utils.h"

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

static void	delete_data_graphics(t_data *data)
{
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->set)
		crust_set_drop(data->set);
	if (data->guy)
		crust_set_drop(data->guy);
	if (data->dum)
		crust_set_drop(data->dum);
	if (data->img)
		crust_img_drop(data->img);
	if (data->floor)
		crust_img_drop(data->floor);
	if (data->floorsc)
		crust_img_drop(data->floorsc);
	if (data->col_available)
		free_matrix((void **)data->col_available, data->map->size.y);
	if (data->collectibles)
		free_matrix((void **)data->collectibles, data->map->size.y);
	if (data->wall_vars)
		free_matrix((void **)data->wall_vars, data->map->size.y);
	if (data->dummies)
		ft_lstclear(&data->dummies, free);
}

void	delete_data(t_data *data)
{
	delete_data_graphics(data);
	if (data->map)
	{
		free_matrix((void **)data->map->map, data->map->size.y);
		free(data->map);
	}
	if (data->rndwall)
		free_matrix((void **)data->rndwall, data->map->size.y);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	if (data->music)
		freesource(data->music);
	if (data->alctx)
		free_openal(data->alctx);
}
