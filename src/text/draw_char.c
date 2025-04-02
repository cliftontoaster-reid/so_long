/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_char.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 23:03:48 by lfiorell          #+#    #+#             */
/*   Updated: 2025/04/02 11:42:52 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "text.h"

#define SPECIALS "!@#$%^&*[]-=+.,:;\"()?\\/|-:"

static t_2d	get_alphanum_pos(char c)
{
	t_2d	pos;

	ft_bzero(&pos, sizeof(t_2d));
	if (ft_isalpha(c))
	{
		c = ft_tolower(c);
		pos.x = c - 'a';
		pos.y = 6;
	}
	else if (ft_isdigit(c))
	{
		if (c == '0')
			pos.x = 10;
		else
			pos.x = c - '1';
		pos.y = 7;
	}
	return (pos);
}

/**
 * @brief Get the image corresponding to the given character
 *
 * @param data Pointer to the game data structure
 * @param c Character to get the image for (must be a-z or A-Z)
 * @return t_img* Pointer to the image, or NULL if character is not alphabetic
 */
t_img	*get_char_img(t_data *data, char c)
{
	t_2d	pos;
	int		special_idx;

	if (!data || !data->text_set)
		return (NULL);
	ft_bzero(&pos, sizeof(t_2d));
	if (ft_strchr(SPECIALS, c))
	{
		special_idx = 0;
		while (SPECIALS[special_idx] != c)
			special_idx++;
		pos.x = special_idx;
		pos.y = 5;
	}
	else if (ft_isalnum(c))
		pos = get_alphanum_pos(c);
	if (pos.y == 0)
		return (NULL);
	return (crust_set_get_img_by_pos(data->text_set, pos));
}

/**
 * @brief Draw a character on an image at a specific position
 *
 * @param data Pointer to the game data structure
 * @param img Destination image to draw on
 * @param c Character to draw (must be a-z or A-Z)
 * @param pos Position to draw the character at
 */
void	draw_char(t_data *data, t_img *img, char c, t_2d pos)
{
	t_img	*char_img;

	if (!data || !img)
		return ;
	char_img = get_char_img(data, c);
	if (char_img)
	{
		crust_img_draw(img, char_img, pos);
		crust_img_drop(char_img);
	}
}
