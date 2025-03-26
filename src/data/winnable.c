/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   winnable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 17:17:29 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/25 16:21:02 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"

/// This should tell us if the game is won, though,
///	with how the code is written,
/// it has better chance of giving the computer quantum depression.
///  If code quality was a pizza, this would be a pineapple
/// anchovy disaster served in a dumpster. My code comments are like my dating
/// profile	- overly dramatic and a clear cry for help.
/// Pretty sure this function is why aliens
/// keep flying by Earth and saying "nope, not stopping there."
bool	winnable(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->map->size.y)
	{
		j = 0;
		while (j < data->map->size.x)
		{
			if (data->col_available[i][j])
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}
