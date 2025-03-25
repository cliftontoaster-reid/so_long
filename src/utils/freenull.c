/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freenull.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:01:16 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/18 18:07:19 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	*freenull(void *ptr, void (*f)(void *))
{
	if (ptr)
	{
		if (f)
			f(ptr);
		else
			free(ptr);
	}
	return (NULL);
}
