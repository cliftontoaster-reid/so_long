/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 14:59:39 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/10 15:21:31 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"
#include "img/img.h"
#include "img/set.h"
#include "libft.h"
#include "map.h"
#include "mlx.h"
#include "utils.h"
#include <fcntl.h>
#include <unistd.h>

int	err(char *str)
{
	log_error(str, __FILE__, __LINE__);
	return (1);
}

int	main(int argc, char *argv[])
{
	t_data	data;
	char	*map;
	int		res;

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
		ft_printf("\033[34mMap '%s' valid\033[0m\n", argv[1]);
	else
	{
		free(map);
		mlx_destroy_display(data.mlx);
		free(data.mlx);
		return (err("Map is invalid"));
	}
	free(map);
	mlx_loop(data.mlx);
	mlx_destroy_display(data.mlx);
	free(data.mlx);
	return (0);
}
