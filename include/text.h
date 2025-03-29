/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 22:59:47 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/28 23:03:29 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXT_H
# define TEXT_H

# include "Crust/img/img.h"
# include "Crust/img/set.h"
# include "data.h"
# include "render.h"

t_img	*create_text(t_data *data, char *text);
void	draw_text(t_data *data, t_img *img, char *text, t_2d pos);
void	draw_char(t_data *data, t_img *img, char c, t_2d pos);

#endif
