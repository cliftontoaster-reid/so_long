/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_is_size_valid.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 14:39:47 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/27 10:24:33 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "utils.h"

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

static bool	map_is_rectangular(char **map_lines)
{
	int	i;
	int	size;

	i = 0;
	size = ft_strlen(map_lines[0]);
	while (map_lines[i])
	{
		if (ft_strlen(map_lines[i]) != size)
		{
			log_error("Map not rectangular", __FILE__, __LINE__);
			return (false);
		}
		i++;
	}
	return (true);
}

bool	map_is_size_valid(char *map)
{
	char	**map_lines;
	bool	is_valid;

	is_valid = true;
	map_lines = ft_split(map, '\n');
	if (!map_lines)
	{
		log_error("Map split failed", __FILE__, __LINE__);
		return (false);
	}
	if (ft_strarr_len(map_lines) < 3)
	{
		log_error("Map too small", __FILE__, __LINE__);
		ft_splitfree(map_lines);
		is_valid = false;
	}
	else if (!map_is_rectangular(map_lines))
		is_valid = false;
	ft_splitfree(map_lines);
	if (!is_valid)
		log_error("Map size invalid", __FILE__, __LINE__);
	else
		log_info("Map size is valid", __FILE__, __LINE__);
	return (is_valid);
}
