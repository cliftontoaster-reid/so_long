/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_fmt_subchunk.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 14:34:38 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/31 14:34:55 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "audio.h"
#include <stdio.h>
#include <string.h>

inline int	read_riff_header(FILE *file, t_riff_header *riff)
{
	if (fread(riff, sizeof(t_riff_header), 1, file) != 1)
		return (0);
	if (strncmp((char *)riff->chunk_id, "RIFF", 4) != 0
		|| strncmp((char *)riff->format, "WAVE", 4) != 0)
		return (0);
	return (1);
}
