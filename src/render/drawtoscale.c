/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawtoscale.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 11:44:58 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/31 12:42:32 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Crust/img/img.h"
#include "Crust/img/scale.h"
#include "render.h"

inline void	drawtoscale(t_data *data, t_img *dst, t_img *img, t_2d pos)
{
	t_img	*scaled;
	t_2d	newsize;
	t_2d	newpos;

	if (data->scale <= 0 || data->scale > 10)
		return ;
	newsize.x = img->width * data->scale;
	newsize.y = img->height * data->scale;
	scaled = crust_img_scale(img, newsize, CRUST_IMG_SCALE_NEAREST);
	if (!scaled)
		return ;
	newpos.x = pos.x * data->scale;
	newpos.y = pos.y * data->scale;
	if (newpos.x + newsize.x <= dst->width && newpos.y
		+ newsize.y <= dst->height)
		crust_img_draw(dst, scaled, newpos);
	crust_img_drop(scaled);
}
