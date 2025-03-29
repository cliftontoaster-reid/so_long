/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_text.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 23:34:44 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/28 23:39:06 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "text.h"

t_img	*create_text(t_data *data, char *text)
{
	t_img	*img;
	t_2d	pos;

	if (!data || !data->text_set || !text)
		return (NULL);
	pos.x = 0;
	pos.y = 0;
	img = crust_img_new(data, ft_strlen(text) * 8, 8);
	if (!img)
		return (NULL);
	draw_text(data, img, text, pos);
	return (img);
}
