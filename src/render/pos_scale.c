/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pos_scale.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:54:29 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/11 14:53:07 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include <limits.h>

t_2d	pos_scale(t_2d pos, t_2d size, int scale)
{
	t_2d	scaled;
	long	x_long;
	long	y_long;

	x_long = (long)pos.x * size.x * scale;
	y_long = (long)pos.y * size.y * scale;
	if (x_long > INT_MAX)
		x_long = INT_MAX;
	if (y_long > INT_MAX)
		y_long = INT_MAX;
	if (x_long < INT_MIN)
		x_long = INT_MIN;
	if (y_long < INT_MIN)
		y_long = INT_MIN;
	scaled.x = (int)x_long;
	scaled.y = (int)y_long;
	return (scaled);
}
