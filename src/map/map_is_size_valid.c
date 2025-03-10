/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_is_size_valid.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 14:39:47 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/05 14:05:18 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

static inline void	ft_splitfree(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

static inline int	ft_strarr_len(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

bool	map_is_size_valid(char *map)
{
	char	**map_lines;
	int		i;
	int		size;

	map_lines = ft_split(map, '\n');
	if (!map_lines)
		return (false);
	if (ft_strarr_len(map_lines) < 3)
	{
		ft_splitfree(map_lines);
		return (false);
	}
	i = 0;
	size = ft_strlen(map_lines[0]);
	while (map_lines[i])
	{
		if (ft_strlen(map_lines[i]) != size)
		{
			ft_splitfree(map_lines);
			return (false);
		}
		i++;
	}
	ft_splitfree(map_lines);
	return (true);
}
