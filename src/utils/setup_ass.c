/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_ass.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 16:09:14 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/31 17:39:00 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "artificial_stupidity.h"
#include "audio.h"
#include "data.h"
#include "map.h"
#include "mlx.h"
#include "utils.h"

int	setup_textures(t_data *data)
{
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
	data->dum = crust_set_from_xpm(data->mlx, "assets/images/dummy.xpm",
			(t_2d){24, 24});
	if (!data->dum)
		return (err("Dummy set creation failed"));
	if (!setup_dummies(data, data->map))
		return (err("Dummy setup failed"));
	return (0);
}

static inline int	setupaudio(t_data *data)
{
	t_openalsource	*music_source;

	data->alctx = init_openal();
	if (!data->alctx)
		return (err("OpenAL context initialization failed"));
	music_source = playmusic(data->alctx, "assets/audio/music.wav");
	if (!music_source)
		return (err("Failed to play music"));
	data->music = music_source;
	return (0);
}

int	setup_assets(t_data *data, char *map)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		return (err("MLX initialization failed"));
	data->map = map_from_str(map);
	if (!data->map)
		return (err("Map file read error"));
	if (setup_textures(data))
		return (1);
	if (!data->dummies)
		log_warning("No dummies found", __FILE__, __LINE__);
	data->player = map_find_player(data->map);
	data->last_player = (t_2d){data->player.x, data->player.y - 1};
	data->scale = 1;
	setupaudio(data);
	return (0);
}
