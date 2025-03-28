/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_dummies.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 15:54:56 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/28 16:56:58 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "artificial_stupidity.h"
#include "libft.h"
#include "render.h"

static bool	ft_rand_bool(void)
{
	return (ft_rand_int(0, 2) == 1);
}

static t_2d	randdir(t_2d pos, bool horizontal)
{
	t_2d	dir;

	if (horizontal)
	{
		if (ft_rand_bool())
			dir.x = -1;
		else
			dir.x = 1;
		dir.y = 0;
	}
	else
	{
		if (ft_rand_bool())
			dir.y = -1;
		else
			dir.y = 1;
		dir.x = 0;
	}
	return (posadd(pos, dir.x, dir.y));
}

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
		dummy->lst_pos = randdir(pos, dummy->horizontal);
		dummy->colour = ft_rand_int(0, 3);
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
