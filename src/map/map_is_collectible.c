/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_is_collectible.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 14:52:30 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/05 14:05:06 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

inline int	ft_strfreq(char *str, char c)
{
	int	count;

	count = 0;
	while (*str)
	{
		if (*str == c)
			count++;
		str++;
	}
	return (count);
}

bool	map_is_collectible(t_map *map)
{
	size_t	collectible_count;
	int		i;

	collectible_count = 0;
	i = 0;
	while (i < map->size.y)
	{
		collectible_count += ft_strfreq(map->map[i], 'C');
		i++;
	}
	if (collectible_count == 0)
		return (false);
	return (true);
}
