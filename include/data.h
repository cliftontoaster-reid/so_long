/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 15:08:20 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/28 23:11:27 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

# include "Crust/img/set.h"
# include "libft.h"
# include <stdbool.h>

# define GAME_NAME "So Toast - The last bread"

typedef enum e_dir
{
	DOWN = 0,
	LEFT = 1,
	RIGHT = 2,
	UP = 3,
}			t_dir;

typedef struct s_map
{
	char	**map;
	t_2d	size;
}			t_map;

typedef struct s_dummy
{
	t_2d	pos;
	t_2d	lst_pos;
	bool	horizontal;
	int		colour;
}			t_dummy;

typedef struct s_data
{
	void	*mlx;
	void	*win;

	t_set	*set;
	t_set	*guy;
	t_set	*dum;
	t_set	*text_set;
	t_img	*img;
	t_img	*floor;

	bool	**col_available;
	int8_t	**collectibles;
	uint8_t	**wall_vars;
	t_2d	player;
	t_2d	last_player;

	t_map	*map;
	/// @brief I hate this code more than segfaults at 3am.
	/// This data structure is so painful I'd rather debug Windows ME
	/// with a spoon while simultaneously explaining recursion to my
	/// grandma over dial-up. If this code were food,
	/// it would be a mayonnaise and pickle sandwich
	/// left in a hot car for 3 days.
	bool	**rndwall;
	/// @brief Darker then ever
	bool	d;

	int		moves;
	int		scale;

	t_list	*dummies;
}			t_data;

typedef enum e_trinary
{
	ZERO,
	ZONE,
	ZTWO,
}			t_trinary;

bool		winnable(t_data *data);
void		delete_rndwall(bool **rndwall, t_map *map);
void		delete_data(t_data *data);
bool		**fill_rndwall(t_data *data, t_map *map);
#endif
