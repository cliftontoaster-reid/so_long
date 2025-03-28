/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_run_checks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 16:26:37 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/28 10:22:58 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "utils.h"

static t_map_error	freenret(t_map *map, t_map_error ret, char *msg)
{
	if (msg)
		log_warning("%s", __FILE__, __LINE__, msg);
	map_free(map);
	return (ret);
}

static inline t_map_error	map_run_checks_part1(t_map *map_struct)
{
	if (!map_struct)
		return (MAP_ERROR_CHAR);
	log_info("Map size is valid", __FILE__, __LINE__);
	if (!map_is_char_valid(map_struct))
		return (freenret(map_struct, MAP_ERROR_CHAR, ERR_MAP_ERROR_CHAR));
	log_info("Map characters are valid", __FILE__, __LINE__);
	if (!map_is_closed(map_struct))
		return (freenret(map_struct, MAP_ERROR_OPEN, ERR_MAP_ERROR_OPEN));
	log_info("Map is closed", __FILE__, __LINE__);
	if (!map_is_collectible(map_struct))
		return (freenret(map_struct, MAP_ERROR_COLLECTIBLE_NOT_FOUND,
				ERR_MAP_ERROR_COLLECTIBLE_NOT_FOUND));
	log_info("Collectible found", __FILE__, __LINE__);
	return (MAP_ERROR_NONE);
}

static inline t_map_error	map_is_valid_part2(t_map *map_struct)
{
	char	tmp;
	t_2d	t;

	tmp = map_is_exit(map_struct);
	if (tmp == ZONE)
		return (freenret(map_struct, MAP_ERROR_EXIT_NOT_FOUND,
				ERR_MAP_ERROR_EXIT_NOT_FOUND));
	if (tmp == ZTWO)
		return (freenret(map_struct, MAP_ERROR_EXIT_MULTIPLE,
				ERR_MAP_ERROR_EXIT_MULTIPLE));
	t = map_find_exit(map_struct);
	log_info("Exit is valid at %d %d", __FILE__, __LINE__, t.x, t.y);
	tmp = map_is_player(map_struct);
	if (tmp == ZONE)
		return (freenret(map_struct, MAP_ERROR_PLAYER_NOT_FOUND,
				ERR_MAP_ERROR_PLAYER_NOT_FOUND));
	if (tmp == ZTWO)
		return (freenret(map_struct, MAP_ERROR_PLAYER_MULTIPLE,
				ERR_MAP_ERROR_PLAYER_MULTIPLE));
	t = map_find_player(map_struct);
	log_info("Player is valid at %d %d", __FILE__, __LINE__, t.x, t.y);
	return (MAP_ERROR_NONE);
}

t_map_error	map_run_checks(char *map)
{
	t_map		*map_struct;
	t_map_error	part;

	if (!map_is_size_valid(map))
	{
		log_warning("Map size is invalid", __FILE__, __LINE__);
		return (MAP_ERROR_SIZE);
	}
	map_struct = map_from_str(map);
	part = map_run_checks_part1(map_struct);
	if (part != MAP_ERROR_NONE)
		return (part);
	part = map_is_valid_part2(map_struct);
	if (part != MAP_ERROR_NONE)
		return (part);
	if (!map_is_valid(map_struct))
		return (freenret(map_struct, MAP_ERROR_INVALID_PATH,
				ERR_MAP_ERROR_INVALID_PATH));
	log_info("Path is valid", __FILE__, __LINE__);
	map_free(map_struct);
	return (MAP_ERROR_NONE);
}
