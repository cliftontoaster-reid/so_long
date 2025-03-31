/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freesource.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 14:50:25 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/31 14:50:46 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "audio.h"

void	freesource(t_openalsource *src)
{
	if (src)
	{
		alDeleteSources(1, &src->source);
		alDeleteBuffers(1, &src->buffer);
		free(src);
	}
	ft_bzero(src, sizeof(t_openalsource));
}
