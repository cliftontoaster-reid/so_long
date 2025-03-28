/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_dummies.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 15:54:56 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/28 16:34:21 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "artificial_stupidity.h"
#include "libft.h"
#include "render.h"

#define ri ft_rand_int

static int	create_dummy_at_position(t_data *data, t_map *map, t_2d pos)
{
	t_list	*dummy_list;
	t_dummy	*dummy;

	if (map->map[pos.y][pos.x] == 'd' || map->map[pos.y][pos.x] == 'D')
	{
		dummy = malloc(sizeof(t_dummy));
		if (!dummy)
			return (0);
		dummy->pos = pos;
		dummy->horizontal = (map->map[pos.y][pos.x] == 'd');
		if (dummy->horizontal)
			dummy->lst_pos = (t_2d){pos.x + ri(0, 2), pos.y};
		else
			dummy->lst_pos = (t_2d){pos.x, pos.y + ri(0, 2)};
		dummy->colour = ft_rand_int(0, 4);
		dummy_list = ft_lstnew(dummy);
		if (!dummy_list)
			return (0);
		if (!data->dummies)
			data->dummies = dummy_list;
		else
			ft_lstadd_back(&data->dummies, dummy_list);
	}
	return (1);
}

static int	process_column(t_data *data, t_map *map, int x)
{
	t_2d	pos;

	pos.x = x;
	pos.y = 0;
	while (pos.y < map->size.y)
	{
		if (!create_dummy_at_position(data, map, pos))
			return (0);
		pos.y++;
	}
	return (1);
}

int	setup_dummies(t_data *data, t_map *map)
{
	t_2d	pos;

	ft_bzero(&pos, sizeof(t_2d));
	data->dummies = NULL;
	while (pos.x < map->size.x)
	{
		if (!process_column(data, map, pos.x))
			return (0);
		pos.x++;
	}
	return (1);
}
