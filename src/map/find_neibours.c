/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_neibours.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 18:20:55 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/28 10:21:38 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "utils.h"

inline t_2d	*t2dclone(t_2d src)
{
	t_2d	*dest;

	dest = malloc(sizeof(t_2d));
	if (!dest)
		return (NULL);
	ft_bzero(dest, sizeof(t_2d));
	dest->x = src.x;
	dest->y = src.y;
	return (dest);
}

inline bool	is2d_inlist(t_list *list, t_2d *pos)
{
	if (!list)
		return (false);
	if (!pos)
		return (false);
	if (pos->x < 0 || pos->y < 0)
		return (false);
	while (list)
	{
		if (((t_2d *)list->content)->x == pos->x
			&& ((t_2d *)list->content)->y == pos->y)
			return (true);
		list = list->next;
	}
	return (false);
}

void	find_step(t_map *map, t_list **lists[3], t_2d neibours[4], int i)
{
	t_2d	*pos1;
	t_2d	*pos2;

	if (!is2d_inlist(*lists[1], &neibours[i]))
	{
		if (map->map[neibours[i].y][neibours[i].x] != '1')
		{
			pos1 = t2dclone(neibours[i]);
			pos2 = t2dclone(neibours[i]);
			ft_lstadd_back(lists[0], ft_lstnew(pos1));
			ft_lstadd_back(lists[1], ft_lstnew(pos2));
		}
		ft_lstadd_back(lists[2], ft_lstnew(t2dclone(neibours[i])));
	}
}

inline void	find_neibours(t_map *map, t_list **to_visit, t_list **visited,
		t_list **accessible)
{
	t_2d	*pos;
	t_2d	neibours[4];
	int		i;
	t_list	**lists[3];

	pos = (*to_visit)->content;
	log_debug("Analyzing tile: %c at position x: %d, y: %d", __FILE__, __LINE__,
		map->map[pos->y][pos->x], pos->x, pos->y);
	neibours[0] = (t_2d){pos->x + 1, pos->y};
	neibours[1] = (t_2d){pos->x - 1, pos->y};
	neibours[2] = (t_2d){pos->x, pos->y + 1};
	neibours[3] = (t_2d){pos->x, pos->y - 1};
	i = 0;
	while (i < 4)
	{
		if (neibours[i].x < map->size.x && neibours[i].y < map->size.y)
		{
			lists[0] = to_visit;
			lists[1] = visited;
			lists[2] = accessible;
			find_step(map, lists, neibours, i);
		}
		i++;
	}
}
