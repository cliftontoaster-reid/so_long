/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_dummy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 15:42:45 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/28 16:07:18 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "artificial_stupidity.h"
#include "render.h"
#include "utils.h"

void	justmovealready_dummy(t_data *data, t_dummy *dummy, t_2d pos)
{
	t_2d	newpos;

	dummy->lst_pos = dummy->pos;
	if (data->map->map[pos.y][pos.x] != '1')
		dummy->pos = posadd(dummy->pos, pos.x, pos.y);
	else
	{
		newpos.x = 0 - dummy->pos.x;
		newpos.y = 0 - dummy->pos.y;
		dummy->pos = posadd(dummy->pos, newpos.x, newpos.y);
	}
}

void	move_dummy(t_data *data, t_dummy *dummy)
{
	if (dummy->horizontal)
	{
		log_debug("dummy %d is horizontal", __FILE__, __LINE__, dummy->colour);
		if (dummy->pos.x > dummy->lst_pos.x)
			justmovealready_dummy(data, dummy, (t_2d){1, 0});
		else
			justmovealready_dummy(data, dummy, (t_2d){-1, 0});
	}
	else
	{
		log_debug("dummy %d is vertical", __FILE__, __LINE__, dummy->colour);
		if (dummy->pos.y > dummy->lst_pos.y)
			justmovealready_dummy(data, dummy, (t_2d){0, 1});
		else
			justmovealready_dummy(data, dummy, (t_2d){0, -1});
	}
	log_debug("dummy %d moved to [%d][%d]", __FILE__, __LINE__, dummy->colour,
		dummy->pos.x, dummy->pos.y);
}

void	move_dummies(t_data *data)
{
	t_list	*dummy_list;
	t_dummy	*dummy;

	dummy_list = data->dummies;
	while (dummy_list)
	{
		dummy = (t_dummy *)dummy_list->content;
		move_dummy(data, dummy);
		dummy_list = dummy_list->next;
	}
}
