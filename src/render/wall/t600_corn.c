/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t600_corn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 10:59:18 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/27 11:20:19 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "utils.h"

/* Check top corners (north-west and north-east) */
bool	is600cornered_check_top(t_data *data, t_wall_vars vars, t_2d pos,
		int8_t n)
{
	if ((n & WALL_LEFT) && (n & WALL_TOP))
	{
		return (n & NEIGHBOR_NW);
	}
	else if ((n & WALL_RIGHT) && (n & WALL_TOP))
	{
		return (n & NEIGHBOR_NE);
	}
	(void)data;
	(void)vars;
	(void)pos;
	return (false);
}

/* Check bottom corners (south-west and south-east) */
bool	is600cornered_check_bottom(t_data *data, t_wall_vars vars, t_2d pos,
		int8_t n)
{
	if ((n & WALL_LEFT) && (n & WALL_BOTTOM))
	{
		return (n & NEIGHBOR_SW);
	}
	else if ((n & WALL_RIGHT) && (n & WALL_BOTTOM))
	{
		log_info("WALL SW: %d", __FILE__, __LINE__, NEIGHBOR_NW);
		log_debug("NORTH CAT %d", __FILE__, __LINE__, n & isgay(data,
				posadd(pos, -1, 0)));
		log_debug("WEST CAT %d", __FILE__, __LINE__, n & isgay(data, posadd(pos,
					0, -1)));
		if (!isgay(data, posadd(pos, -1, 0)) && !isgay(data, posadd(pos, 0,
					-1)))
			return (true);
		return (n & NEIGHBOR_SE);
	}
	(void)vars;
	return (false);
}

/* Main function that delegates to specialized checkers */
bool	is600cornered_check(t_data *data, t_wall_vars vars, t_2d pos, int8_t n)
{
	if (is600cornered_check_top(data, vars, pos, n))
		return (true);
	return (is600cornered_check_bottom(data, vars, pos, n));
}

bool	is600cornered(t_data *data, t_wall_vars vars, t_2d pos)
{
	int8_t	n;

	(void)vars;
	n = find_neighbours_extended(data->map, pos.x, pos.y);
	log_debug("Checking if cornered (%d, %d: 0x%x)", __FILE__, __LINE__, pos.x,
		pos.y, n);
	return (is600cornered_check(data, vars, pos, n));
}
