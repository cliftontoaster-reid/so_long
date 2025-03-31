/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawtoscale.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 11:44:58 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/31 12:13:37 by lfiorell         ###   ########.fr       */
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

	newsize.x = img->width * data->scale;
	newsize.y = img->height * data->scale;
	scaled = crust_img_scale(img, newsize, CRUST_IMG_SCALE_NEAREST);
	if (!scaled)
		return ;
	newpos.x = pos.x * data->scale;
	newpos.y = pos.y * data->scale;
	crust_img_draw(dst, scaled, newpos);
	crust_img_drop(scaled);
	ft_bzero(&scaled, sizeof(t_img));
	ft_bzero(&newsize, sizeof(t_2d));
	ft_bzero(&newpos, sizeof(t_2d));
	return ;
}
