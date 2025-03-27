/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strerr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 13:01:16 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/18 18:21:58 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "utils.h"

static inline char	*owo(int errnum)
{
	if (errnum == MAP_ERROR_NONE)
	{
		return ("Success");
	}
	if (errnum == MAP_ERROR_SIZE)
	{
		return (ERR_MAP_ERROR_SIZE);
	}
	if (errnum == MAP_ERROR_CHAR)
	{
		return (ERR_MAP_ERROR_CHAR);
	}
	if (errnum == MAP_ERROR_OPEN)
	{
		return (ERR_MAP_ERROR_OPEN);
	}
	if (errnum == MAP_ERROR_PLAYER_NOT_FOUND)
	{
		return (ERR_MAP_ERROR_PLAYER_NOT_FOUND);
	}
	return ((void *)0);
}

static inline char	*uwu(int errnum)
{
	if (errnum == MAP_ERROR_PLAYER_MULTIPLE)
	{
		return (ERR_MAP_ERROR_PLAYER_MULTIPLE);
	}
	if (errnum == MAP_ERROR_COLLECTIBLE_NOT_FOUND)
	{
		return (ERR_MAP_ERROR_COLLECTIBLE_NOT_FOUND);
	}
	if (errnum == MAP_ERROR_EXIT_NOT_FOUND)
	{
		return (ERR_MAP_ERROR_EXIT_NOT_FOUND);
	}
	if (errnum == MAP_ERROR_EXIT_MULTIPLE)
	{
		return (ERR_MAP_ERROR_EXIT_MULTIPLE);
	}
	if (errnum == MAP_ERROR_INVALID_PATH)
	{
		return (ERR_MAP_ERROR_INVALID_PATH);
	}
	return ((void *)0);
}

char	*ft_strerr(int errnum)
{
	if (errnum >= MAP_ERROR_NONE && errnum <= MAP_ERROR_EXIT_MULTIPLE)
	{
		return (owo(errnum));
	}
	if (errnum >= MAP_ERROR_PLAYER_MULTIPLE && errnum <= MAP_ERROR_INVALID_PATH)
	{
		return (uwu(errnum));
	}
	return ("Unknown error");
}
