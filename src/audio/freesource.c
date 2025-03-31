/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freesource.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 14:50:25 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/31 17:33:11 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "audio.h"

void	freesource(t_openalsource *src)
{
	if (src)
	{
		stopsource(src);
		alDeleteSources(1, &src->source);
		alDeleteBuffers(1, &src->buffer);
		free(src);
	}
}

void	freesrcidx(t_list *srcs, int idx)
{
	int	i;

	i = 0;
	while (srcs && i < idx)
	{
		srcs = srcs->next;
		i++;
	}
	if (srcs)
		ft_lstdelone(srcs, (void (*)(void *))freesource);
}
