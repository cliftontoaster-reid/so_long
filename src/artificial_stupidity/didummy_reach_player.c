/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   didummy_reach_player.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 15:50:56 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/28 16:42:01 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "artificial_stupidity.h"
#include "utils.h"

bool	didummy_reach_player(t_data *data, t_dummy *dummy)
{
	t_2d	player_pos;

	player_pos = data->player;
	if (dummy->pos.x == player_pos.x && dummy->pos.y == player_pos.y)
	{
		log_debug("Dummy %d reached player at [%d][%d]", __FILE__, __LINE__,
			dummy->colour, player_pos.x, player_pos.y);
		return (true);
	}
	return (false);
}

bool	didummies_reach_player(t_data *data)
{
	t_list	*dummy_list;
	t_dummy	*dummy;

	dummy_list = data->dummies;
	while (dummy_list)
	{
		dummy = dummy_list->content;
		if (didummy_reach_player(data, dummy))
			return (true);
		dummy_list = dummy_list->next;
	}
	return (false);
}
