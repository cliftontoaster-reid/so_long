/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 14:59:39 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/26 12:57:46 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Crust/img/img.h"
#include "Crust/img/scale.h"
#include "Crust/img/set.h"
#include "data.h"
#include "libft.h"
#include "map.h"
#include "mlx.h"
#include "render.h"
#include "utils.h"
#include <fcntl.h>
#include <unistd.h>

int	err(char *str)
{
	log_error("%s", __FILE__, __LINE__, str);
	return (1);
}

static inline void	render_floors(t_data *data)
{
	t_2d	pos;

	pos.y = 0;
	while (pos.y < data->map->size.y)
	{
		pos.x = 0;
		while (pos.x < data->map->size.x)
		{
			render_floor(data, data->map, pos, data->img);
			pos.x++;
		}
		pos.y++;
	}
}

static inline int	render_map(t_data *data, char *map)
{
	// parsing map & loading stuff
	data->map = map_from_str(map);
	if (!data->map)
		return (err("Map file read error"));
	data->set = crust_set_from_xpm(data->mlx,
			"assets/images/CuteRPG_Dungeon.xpm", (t_2d){16, 16});
	if (!data->set)
		return (err("Image set creation failed"));
	data->img = crust_img_new(data->mlx, data->map->size.x * 32,
			data->map->size.y * 32);
	if (!data->img)
		return (err("Image creation failed"));
	// rendering map
	// rendering floor
	render_floors(data);
	// rendering cosmetics
	setup_cosmetics(data);
	render_cosmetics(data);
	// rendering exit
	just_render_exit(data);
	// rendering walls
	just_render_walls(data);
	return (0);
}

int	main(int argc, char *argv[])
{
	char	*map;
	int		res;
	t_data	data;
	t_img	*scaled;

	ft_bzero(&data, sizeof(t_data));
	data.mlx = mlx_init();
	if (!data.mlx || argc != 2)
		return (err("Usage: ./so_long [map.ber]"));
	if (!fs_exists(argv[1]))
		return (err("Map file not found"));
	map = fs_read_file(argv[1]);
	if (!map)
		return (err("Map file read error"));
	res = map_run_checks(map);
	if (res == MAP_ERROR_NONE)
	{
		ft_printf("\033[34mMap '%s' valid\033[0m\n", argv[1]);
		if (render_map(&data, map))
			return (1);
		// upscale image based on scale factor
		scaled = crust_img_scale(data.img, (t_2d){data.map->size.x * 64,
				data.map->size.y * 64}, CRUST_IMG_SCALE_NEAREST);
		if (!scaled)
			return (err("Image scaling failed"));
		// WIN
		data.win = mlx_new_window(data.mlx, scaled->width, scaled->height,
				"so_long");
		if (!data.win)
			return (err("Window creation failed"));
		mlx_put_image_to_window(data.mlx, data.win, scaled->img_ptr, 0, 0);
	}
	else
	{
		free(map);
		mlx_destroy_display(data.mlx);
		free(data.mlx);
		return (err("Map file invalid"));
	}
	free(map);
	mlx_loop(data.mlx);
	mlx_destroy_display(data.mlx);
	return (0);
}
