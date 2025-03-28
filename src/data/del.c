/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 13:24:44 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/28 15:53:15 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	drop_map(t_map *map)
{
	if (map)
	{
		free_matrix((void **)map->map, map->size.y);
		free(map);
	}
}

static void	delete_data_graphics(t_data *data)
{
	log_debug("Deleting graphics data", __FILE__, __LINE__);
	if (data->win)
	{
		log_debug("Destroying window", __FILE__, __LINE__);
		mlx_destroy_window(data->mlx, data->win);
	}
	if (data->set)
	{
		log_debug("Dropping set", __FILE__, __LINE__);
		crust_set_drop(data->set);
	}
	if (data->guy)
	{
		log_debug("Dropping guy", __FILE__, __LINE__);
		crust_set_drop(data->guy);
	}
	if (data->img)
	{
		log_debug("Dropping img", __FILE__, __LINE__);
		crust_img_drop(data->img);
	}
}

static void	delete_data_map_resources(t_data *data)
{
	if (data->floor)
	{
		log_debug("Dropping floor", __FILE__, __LINE__);
		crust_img_drop(data->floor);
	}
	if (data->col_available)
	{
		log_debug("Freeing col_available matrix", __FILE__, __LINE__);
		free_matrix((void **)data->col_available, data->map->size.y);
	}
	if (data->collectibles)
	{
		log_debug("Freeing collectibles matrix", __FILE__, __LINE__);
		free_matrix((void **)data->collectibles, data->map->size.y);
	}
	if (data->wall_vars)
	{
		log_debug("Freeing wall_vars matrix", __FILE__, __LINE__);
		free_matrix((void **)data->wall_vars, data->map->size.y);
	}
	if (data->dummies)
	{
		log_debug("Freeing dummies list", __FILE__, __LINE__);
		ft_lstclear(&data->dummies, free);
	}
}

void	delete_data(t_data *data)
{
	log_debug("Starting data deletion process", __FILE__, __LINE__);
	delete_data_graphics(data);
	log_debug("Deleting map resources", __FILE__, __LINE__);
	delete_data_map_resources(data);
	if (data->map)
	{
		log_debug("Dropping map", __FILE__, __LINE__);
		drop_map(data->map);
	}
	if (data->rndwall)
	{
		log_debug("Freeing rndwall matrix", __FILE__, __LINE__);
		free_matrix((void **)data->rndwall, data->map->size.y);
	}
	if (data->mlx)
	{
		log_debug("Destroying MLX display and freeing MLX data", __FILE__,
			__LINE__);
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	log_debug("Data deletion complete", __FILE__, __LINE__);
}
