/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   didummy_reach_player.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 15:50:56 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/28 17:03:37 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "artificial_stupidity.h"
#include "utils.h"

bool	didummy_reach_player(t_data *data, t_dummy *dummy)
{
	if (dummy->pos.x == data->player.x && dummy->pos.y == data->player.y)
	{
		log_debug("Dummy %d reached player at [%d][%d]", __FILE__, __LINE__,
			dummy->colour, data->player.x, data->player.y);
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
