/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 12:24:32 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/28 12:48:31 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"
#include "render.h"
#include "utils.h"

void	funnywall(void);

void	mov_event(t_data *data, t_2d pos)
{
	char	c;

	c = data->map->map[pos.y][pos.x];
	log_debug("Player is on top of %c", __FILE__, __LINE__, c);
	if (c == 'C')
	{
		data->col_available[pos.y][pos.x] = false;
		log_debug("Player collected a collectible at %d, %d", __FILE__,
			__LINE__, pos.x, pos.y);
	}
	else if (c == 'E')
	{
		if (is_won(data))
		{
			log_info("Player has won the game", __FILE__, __LINE__);
			kthxbye(data);
		}
		else
		{
			log_warning("Player has not collected all collectibles", __FILE__,
				__LINE__);
			funnywall();
		}
	}
}

void	move(t_data *data, int x, int y)
{
	t_2d	new_pos;

	new_pos = posadd(data->player, x, y);
	if (data->map->map[new_pos.y][new_pos.x] == '1')
	{
		funnywall();
		return ;
	}
	data->last_player = data->player;
	data->player = new_pos;
	data->moves++;
	mov_event(data, new_pos);
	render(data, data->map);
	log_debug("Player moved to %d, %d", __FILE__, __LINE__, data->player.x,
		data->player.y);
	log_info("Player has now made %d moves", __FILE__, __LINE__, data->moves);
}
