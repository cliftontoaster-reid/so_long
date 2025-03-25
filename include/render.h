/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:16:40 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/25 15:54:49 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "data.h"
# include "map.h"

int			ft_rand_int(int x, int y);
t_2d		pos_scale(t_2d pos, t_2d size, int scale);

void		render(t_data *data, t_map *map);

t_img		*create_floor(t_data *data);
void		render_floor(t_data *data, t_map *map, t_2d pos, t_img *img);

void		setup_cosmetics(t_data *data);
void		render_cosmetics(t_data *data);
void		render_cosmetic(t_data *data, t_map *map, t_2d pos, t_img *img);

void		just_render_exit(t_data *data);
void		render_exit(t_data *data, t_map *map, t_2d pos, t_img *img);

typedef struct s_wall_vars
{
	uint8_t	n;
	t_2d	pos;
}			t_wall_vars;

void		just_render_walls(t_data *data);
void		render_wall(t_data *data, t_map *map, t_2d pos, t_img *img);

uint8_t		**compute_wall_connections(t_map *map);

/// @brief Finds the extended neighbours of a given position
///
/// This function is used to find the extended neighbours of a given position
/// in the map. This is used to determine the connections of the walls in the
/// map.
///
/// The return format is a uint8_t bitfield, where each bit represents a
/// neighbour. The neighbours are represented as follows:
///
/// 5 1 6
/// 3   4
/// 7 2 8
///
/// Therefore the bitfield is represented as follows:
///
/// 1 = 0000 0001
/// 2 = 0000 0010
/// 3 = 0000 0100
/// 4 = 0000 1000
/// 5 = 0001 0000
/// 6 = 0010 0000
/// 7 = 0100 0000
/// 8 = 1000 0000
///
/// @param map the map
/// @param x the x position
/// @param y the y position
/// @return the bitfield representing the neighbours
uint8_t		find_neighbours_extended(t_map *map, int x, int y);

/// Finds the neighbours of a given position
///
/// This function is used to find the neighbours of a given position in the map.
/// This is used to determine the connections of the walls in the map.
///
/// The return format is a uint8_t bitfield, where each bit represents a
/// neighbour. The neighbours are represented as follows:
///
///   1
/// 3   4
///   2
///
/// Therefore the bitfield is represented as follows:
///
/// 1 = 0000 0001
/// 2 = 0000 0010
/// 3 = 0000 0100
/// 4 = 0000 1000
///
/// @param map the map
/// @param x the x position
/// @param y the y position
/// @return the bitfield representing the neighbours
uint8_t		find_neighbours(t_map *map, int x, int y);

/// @brief Finds the extended neighbours of a given position
///
/// This function is used to find the extended neighbours of a given position
/// in the map. This is used to determine the connections of the walls in the
/// map.
///
/// The return format is a uint8_t bitfield, where each bit represents a
/// neighbour. The neighbours are represented as follows:
///
/// 5 1 6
/// 3   4
/// 7 2 8
///
/// Therefore the bitfield is represented as follows:
///
/// 1 = 0000 0001
/// 2 = 0000 0010
/// 3 = 0000 0100
/// 4 = 0000 1000
/// 5 = 0001 0000
/// 6 = 0010 0000
/// 7 = 0100 0000
/// 8 = 1000 0000
///
/// @param map the map
/// @param x the x position
/// @param y the y position
/// @return the bitfield representing the neighbours
uint8_t		find_neighbours_extended(t_map *map, int x, int y);

/// @brief Finds the off map neighbours of a given position
///
/// This function is used to find the off map neighbours of a given position
/// in the map. This is used to determine the connections of the walls in the
/// map.
///
/// The return format is a uint8_t bitfield, where each bit represents a
/// neighbour. The neighbours are represented as follows:
///
///   1
/// 3   4
///   2
///
/// Therefore the bitfield is represented as follows:
///
/// 1 = 0000 0001
/// 2 = 0000 0010
/// 3 = 0000 0100
/// 4 = 0000 1000
///
/// @param map the map
/// @param x the x position
/// @param y the y position
/// @return the bitfield representing the neighbours
uint8_t		find_neibours_border(t_map *map, int x, int y);

/// @brief Finds the off map extended neighbours of a given position
///
/// This function is used to find the off map extended neighbours of a given
/// position in the map. This is used to determine the connections of the walls
/// in the map.
///
/// The return format is a uint8_t bitfield, where each bit represents a
/// neighbour. The neighbours are represented as follows:
///
/// 5 1 6
/// 3   4
/// 7 2 8
///
/// Therefore the bitfield is represented as follows:
///
/// 1 = 0000 0001
/// 2 = 0000 0010
/// 3 = 0000 0100
/// 4 = 0000 1000
/// 5 = 0001 0000
/// 6 = 0010 0000
/// 7 = 0100 0000
/// 8 = 1000 0000
///
/// @param map the map
/// @param x the x position
/// @param y the y position
/// @return the bitfield representing the neighbours
uint8_t		find_neibours_border_extended(t_map *map, int x, int y);

/// @brief Returns the number of neighbours in a given bitfield
///
/// This function is used to count the number of neighbours in a given bitfield
/// representing the neighbours of a given position in the map.
///
/// @param neighbours the bitfield representing the neighbours
/// @return the number of neighbours
int			get_neighbour_count(uint8_t neighbours);

/// @brief Returns the number of neighbours in a given bitfield
///
/// This function is used to count the number of neighbours in a given bitfield
/// representing the neighbours of a given position in the map.
///
/// @param neighbours the bitfield representing the neighbours
/// @return the number of neighbours
int			get_neighbour_count_extended(uint8_t neighbours);
/// ALL DUN
t_img		*wall_hull(t_data *data);

#endif
