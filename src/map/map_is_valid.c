/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_is_valid.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 16:34:28 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/10 15:26:51 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "map.h"

static inline bool	check_coll(t_map *map, t_list *accs)
{
	t_list	*colls;
	t_list	*current_coll;

	colls = map_find_collectibles(map);
	if (!colls)
		return (true);
	current_coll = colls;
	while (current_coll)
	{
		if (!is2d_inlist(accs, current_coll->content))
		{
			ft_lstclear(&colls, free);
			return (false);
		}
		current_coll = current_coll->next;
	}
	ft_lstclear(&colls, free);
	return (true);
}

static inline bool	freenreturn(t_list **visited, t_list **accessible,
		t_list **to_visit, bool ret)
{
	ft_lstclear(visited, free);
	ft_lstclear(accessible, free);
	ft_lstclear(to_visit, free);
	return (ret);
}

static inline bool	is2d_inlisto(t_list *list, t_2d pos)
{
	if (!list)
		return (false);
	if (pos.x < 0 || pos.y < 0)
		return (false);
	while (list)
	{
		if (((t_2d *)list->content)->x == pos.x
			&& ((t_2d *)list->content)->y == pos.y)
			return (true);
		list = list->next;
	}
	return (false);
}

bool	map_is_valid(t_map *map)
{
	t_list	*visited;
	t_list	*accessible;
	t_list	*to_visit;
	t_list	*tmp;

	accessible = NULL;
	visited = NULL;
	visited = NULL;
	to_visit = ft_lstnew(t2dclone(map_find_exit(map)));
	if (!to_visit)
		return (false);
	while (to_visit)
	{
		find_neibours(map, &to_visit, &visited, &accessible);
		tmp = to_visit;
		to_visit = to_visit->next;
		ft_lstdelone(tmp, free);
	}
	if (!is2d_inlisto(accessible, map_find_player(map)))
		return (freenreturn(&visited, &accessible, &to_visit, false));
	if (!check_coll(map, accessible))
		return (freenreturn(&visited, &accessible, &to_visit, false));
	return (freenreturn(&visited, &accessible, &to_visit, true));
}
