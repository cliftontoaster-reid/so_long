/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_dummy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 16:35:17 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/31 12:15:06 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Crust/img/img.h"
#include "Crust/img/scale.h"
#include "artificial_stupidity.h"
#include "render.h"
#include "utils.h"

t_img	*get_dummy(t_data *data, int colour, int direction, bool var)
{
	t_2d	pos;
	t_img	*img;
	t_img	*scaled;

	pos.x = colour * 3;
	pos.y = direction + var * 4;
	log_debug("Dummy pos.x: %d, pos.y: %d", __FILE__, __LINE__, pos.x, pos.y);
	log_debug("Dummy colour: %d, direction: %d", __FILE__, __LINE__, colour,
		direction);
	img = crust_set_get_img_by_pos(data->dum, pos);
	if (img == NULL)
	{
		log_error("Failed to get image", __FILE__, __LINE__);
		return (NULL);
	}
	scaled = crust_img_scale(img, (t_2d){30, 30}, CRUST_IMG_SCALE_NEAREST);
	crust_img_drop(img);
	return (scaled);
}

/// bottom = 0, left = 1, top = 2, right = 3
static int	getdir(t_dummy *dummy)
{
	if (dummy->horizontal)
	{
		if (dummy->pos.x > dummy->lst_pos.x)
			return (2);
		else
			return (1);
	}
	else
	{
		if (dummy->pos.y > dummy->lst_pos.y)
			return (0);
		else
			return (3);
	}
}

void	render_dummy(t_data *data, t_dummy *dummy)
{
	t_img	*img;
	t_2d	pos;
	int		direction;
	t_img	*scaled;

	if (!data || !dummy)
		return ;
	pos = (t_2d){dummy->pos.x * 32, dummy->pos.y * 32};
	direction = getdir(dummy);
	img = get_dummy(data, dummy->colour, direction, data->d);
	if (img == NULL)
		return ;
	scaled = crust_img_scale(img, (t_2d){30, 30}, CRUST_IMG_SCALE_NEAREST);
	crust_img_drop(img);
	if (!scaled)
	{
		log_error("Failed to scale image", __FILE__, __LINE__);
		return ;
	}
	drawtoscale(data, data->img, scaled, pos);
	crust_img_drop(scaled);
}

void	render_dummies(t_data *data)
{
	t_list	*dummy_list;
	t_dummy	*dummy;

	dummy_list = data->dummies;
	while (dummy_list)
	{
		dummy = (t_dummy *)dummy_list->content;
		render_dummy(data, dummy);
		dummy_list = dummy_list->next;
	}
}
