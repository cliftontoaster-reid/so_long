/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_guy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 14:30:32 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/27 14:33:41 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Crust/img/img.h"
#include "Crust/img/scale.h"
#include "Crust/img/set.h"
#include "data.h"
#include "render.h"
#include "utils.h"

static t_img	*get_sprite(t_data *data, t_dir direction, bool colour)
{
	t_2d	pos;
	t_img	*img;

	pos.y = direction;
	if (colour)
		pos.x = 9;
	else
		pos.x = 6;
	log_debug("OWO pos.x: %d, pos.y: %d", __FILE__, __LINE__, pos.x, pos.y);
	img = crust_set_get_img_by_pos(data->guy, pos);
	if (img == NULL)
	{
		log_error("Failed to get image", __FILE__, __LINE__);
		return (NULL);
	}
	t_img *scale = crust_img_scale(img, (t_2d){30, 30}, CRUST_IMG_SCALE_NEAREST);
	crust_img_drop(img);
	return (scale);
}

static t_dir	get_direction(t_data *data)
{
	t_2d	diff;

	diff.x = data->player.x - data->last_player.x;
	diff.y = data->player.y - data->last_player.y;
	if (diff.x > 0)
		return (RIGHT);
	if (diff.x < 0)
		return (LEFT);
	if (diff.y > 0)
		return (DOWN);
	return (UP);
}

void	render_guy(t_data *data)
{
	t_img	*sprite;
	t_dir	direction;
	t_2d	pos;

	if (data->guy == NULL || data->img == NULL)
		return ;
	direction = get_direction(data);
	sprite = get_sprite(data, direction, data->d);
	if (sprite == NULL)
	{
		log_error("Failed to get sprite", __FILE__, __LINE__);
		return ;
	}
	pos.x = data->player.x * 32;
	pos.y = data->player.y * 32;
	crust_img_draw(data->img, sprite, pos);
	crust_img_drop(sprite);
}
