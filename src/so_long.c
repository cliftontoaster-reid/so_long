/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 14:59:39 by lfiorell          #+#    #+#             */
/*   Updated: 2025/04/02 11:50:46 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Crust/img/img.h"
#include "Crust/img/scale.h"
#include "Crust/img/set.h"
#include "artificial_stupidity.h"
#include "data.h"
#include "libft.h"
#include "map.h"
#include "mlx.h"
#include "render.h"
#include "utils.h"
#include <X11/X.h>
#include <X11/keysym.h>
#include <fcntl.h>
#include <unistd.h>

#ifndef VERSION
# define VERSION "DEV"
#endif

void	print_usage(void)
{
	log_info("So Toast", __FILE__, __LINE__);
	log_debug("CC %s", __FILE__, __LINE__, __VERSION__);
	log_debug("Compiled on %s at %s", __FILE__, __LINE__, __DATE__, __TIME__);
	log_debug("Author: %s", __FILE__, __LINE__, "Clifton Toaster Reid");
	log_debug("Assets by %s", __FILE__, __LINE__, "https://pixymoon.itch.io");
	log_debug("Version: %s", __FILE__, __LINE__, VERSION);
	return ;
}

int	err(char *str)
{
	log_error("%s", __FILE__, __LINE__, str);
	return (1);
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

	print_usage();
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
		mlx_destroy_display(data.mlx);
		free(data.mlx);
		return (err("Map file invalid"));
	}
	free(map);
	mlx_loop(data.mlx);
	mlx_destroy_display(data.mlx);
	return (0);
}
