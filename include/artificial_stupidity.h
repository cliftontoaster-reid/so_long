/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   artificial_stupidity.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 15:40:53 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/28 16:12:43 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARTIFICIAL_STUPIDITY_H
# define ARTIFICIAL_STUPIDITY_H

# include "data.h"
# include "libft.h"
# include "map.h"
# include <stdbool.h>

void	move_dummy(t_data *data, t_dummy *dummy);
void	move_dummies(t_data *data);
bool	didummy_reach_player(t_data *data, t_dummy *dummy);
bool	didummies_reach_player(t_data *data);

int		setup_dummies(t_data *data, t_map *map);

#endif
