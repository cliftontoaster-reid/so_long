/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 14:59:39 by lfiorell          #+#    #+#             */
/*   Updated: 2025/04/02 11:59:24 by lfiorell         ###   ########.fr       */
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
#include <X11/X.h>
#include <fcntl.h>
#include <unistd.h>

int	err(char *str)
{
	log_error("%s", __FILE__, __LINE__, str);
	return (1);
}

static int	setup_assets(t_data *data, char *map)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		return (err("MLX initialization failed"));
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
	data->guy = crust_set_from_xpm(data->mlx, "assets/images/guy.xpm",
			(t_2d){24, 24});
	if (!data->guy)
		return (err("Guy set creation failed"));
	data->player = map_find_player(data->map);
	data->last_player = (t_2d){data->player.x, data->player.y - 1};
	data->scale = 1;
	return (0);
}

static int	setup(t_data *data, char **map, int argc, char *argv[])
{
	ft_bzero(data, sizeof(t_data));
	data->d = ft_rand_int(0, 3) == 0;
	if (argc != 2)
		return (err("Usage: ./so_long [map.ber]"));
	if (!fs_exists(argv[1]))
		return (err("Map file not found"));
	*map = fs_read_file(argv[1]);
	if (!*map)
		return (err("Map file read error"));
	return (map_run_checks(*map));
}

static int	game_start(t_data *data, char *map, char *argv[])
{
	log_info("Map '%s' is valid", __FILE__, __LINE__, argv[1]);
	if (setup_assets(data, map))
		return (1);
	render(data, data->map);
	data->win = mlx_new_window(data->mlx, data->img->width, data->img->height,
			GAME_NAME);
	mlx_hook(data->win, DestroyNotify, StructureNotifyMask, (int (*)())vkthxbye,
		data);
	mlx_key_hook(data->win, key_hook, data);
	if (!data->win)
		return (err("Window creation failed"));
	mlx_put_image_to_window(data->mlx, data->win, data->img->img_ptr, 0, 0);
	return (0);
}

int	main(int argc, char *argv[])
{
	char	*map;
	int		res;
	t_data	data;

	map = NULL;
	res = setup(&data, &map, argc, argv);
	if (res == MAP_ERROR_NONE)
	{
		res = game_start(&data, map, argv);
		if (res)
			return (res);
	}
	else
	{
		free(map);
		return (err("Map file invalid"));
	}
	free(map);
	mlx_loop(data.mlx);
	mlx_destroy_display(data.mlx);
	return (0);
}
