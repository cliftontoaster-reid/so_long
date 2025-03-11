/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 15:36:35 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/11 10:18:28 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H
# define MAP_CHARS "01CEP"

# include "data.h"
# include "img/img.h"
# include "libft.h"
# include <stdbool.h>

# define ERR_MAP_ERROR_SIZE "Map size is invalid"
# define ERR_MAP_ERROR_CHAR "Map contains invalid characters"
# define ERR_MAP_ERROR_OPEN "Map is not closed"
# define ERR_MAP_ERROR_PLAYER_NOT_FOUND "Player not found"
# define ERR_MAP_ERROR_PLAYER_MULTIPLE "Multiple players found"
# define ERR_MAP_ERROR_COLLECTIBLE_NOT_FOUND "Collectible not found"
# define ERR_MAP_ERROR_EXIT_NOT_FOUND "Exit not found"
# define ERR_MAP_ERROR_EXIT_MULTIPLE "Multiple exits found"
# define ERR_MAP_ERROR_INVALID_PATH "No path from player to exit"

typedef struct s_map
{
	char	**map;
	t_2d	size;
}			t_map;

t_map		*map_from_file(char *file);
t_map		*map_from_str(char *str);
void		map_free(t_map *map);
t_2d		map_find_player(t_map *map);
t_2d		map_find_exit(t_map *map);
t_list		*map_find_collectibles(t_map *map);

// I hate this part

typedef enum e_map_error
{
	MAP_ERROR_NONE,
	MAP_ERROR_SIZE,
	MAP_ERROR_CHAR,
	MAP_ERROR_OPEN,
	MAP_ERROR_PLAYER_NOT_FOUND,
	MAP_ERROR_PLAYER_MULTIPLE,
	MAP_ERROR_COLLECTIBLE_NOT_FOUND,
	MAP_ERROR_EXIT_NOT_FOUND,
	MAP_ERROR_EXIT_MULTIPLE,
	MAP_ERROR_INVALID_PATH,
}			t_map_error;

bool		map_is_size_valid(char *map);
bool		map_is_char_valid(t_map *map);
bool		map_is_closed(t_map *map);
t_trinary	map_is_player(t_map *map);
bool		map_is_collectible(t_map *map);
t_trinary	map_is_exit(t_map *map);
bool		map_is_valid(t_map *map);
t_map_error	map_run_checks(char *map);
void		find_neibours(t_map *map, t_list **to_visit, t_list **visited,
				t_list **accessible);
bool		is2d_inlist(t_list *list, t_2d *pos);
t_2d		*t2dclone(t_2d src);
char		*map_errstr(t_map_error err);
int			map_wallvar(t_map *map, t_2d pos);
int			**map_walllst(t_map *map);

#endif
