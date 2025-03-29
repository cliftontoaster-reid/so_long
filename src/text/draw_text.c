/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_text.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 23:33:02 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/28 23:38:42 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "text.h"

void	draw_text(t_data *data, t_img *img, char *text, t_2d pos)
{
	if (!data || !data->text_set || !img || !text)
		return ;
	ft_bzero(&pos, sizeof(t_2d));
	while (*text)
	{
		draw_char(data, img, *text, pos);
		pos.x += 8;
		text++;
	}
}
