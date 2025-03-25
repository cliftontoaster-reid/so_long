/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   baboon.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 12:11:47 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/21 12:47:53 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Crust/img/img.h"
#include "data.h"

/// Deletes the baboon ass sucking variable thanos style - making variables
/// disappear faster than LeBron's hairline in the 2010s.
/// Might work more than once, guess we'll have to see if I am stronger
/// than the purple goblin himself or if I'll choke in the 4th quarter like
/// the Taco Tuesday King himself.
void	delete_rndwall(bool **rndwall, t_map *map)
{
	t_2d	p;

	if (!rndwall)
		return ;
	ft_bzero(&p, sizeof(t_2d));
	while (p.y < map->size.y)
	{
		free(rndwall[p.y]);
		p.y++;
	}
	free(rndwall);
}

bool	**fill_rndwall(t_data *data, t_map *map)
{
	t_2d	p;
	bool	**rndwall;

	ft_bzero(&p, sizeof(t_2d));
	rndwall = ft_calloc(map->size.y, sizeof(bool *));
	if (!rndwall)
		return (NULL);
	while (p.y < map->size.y)
	{
		rndwall[p.y] = ft_calloc(map->size.x, sizeof(bool));
		if (!rndwall[p.y])
			return (NULL);
		while (p.x < map->size.x)
		{
			if (get_neighbour_count(map, p.x, p.y) < 4)
				rndwall[p.y][p.x] = true;
			else
				rndwall[p.y][p.x] = false;
			p.x++;
		}
		p.x = 0;
		p.y++;
	}
	return (rndwall);
}
