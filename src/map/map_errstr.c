/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_errstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 17:00:35 by lfiorell          #+#    #+#             */
/*   Updated: 2025/02/28 17:01:46 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

char	*map_errstr(t_map_error err)
{
	if (err == MAP_ERROR_NONE)
		return ("No error");
	else if (err == MAP_ERROR_SIZE)
		return (ERR_MAP_ERROR_SIZE);
	else if (err == MAP_ERROR_CHAR)
		return (ERR_MAP_ERROR_CHAR);
	else if (err == MAP_ERROR_OPEN)
		return (ERR_MAP_ERROR_OPEN);
	else if (err == MAP_ERROR_PLAYER_NOT_FOUND)
		return (ERR_MAP_ERROR_PLAYER_NOT_FOUND);
	else if (err == MAP_ERROR_PLAYER_MULTIPLE)
		return (ERR_MAP_ERROR_PLAYER_MULTIPLE);
	else if (err == MAP_ERROR_COLLECTIBLE_NOT_FOUND)
		return (ERR_MAP_ERROR_COLLECTIBLE_NOT_FOUND);
	else if (err == MAP_ERROR_EXIT_NOT_FOUND)
		return (ERR_MAP_ERROR_EXIT_NOT_FOUND);
	else if (err == MAP_ERROR_EXIT_MULTIPLE)
		return (ERR_MAP_ERROR_EXIT_MULTIPLE);
	else
		return ("Unknown error");
}
