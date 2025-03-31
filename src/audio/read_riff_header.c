/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_riff_header.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 14:34:58 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/31 14:35:12 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "audio.h"
#include <stdio.h>
#include <string.h>

inline int	read_fmt_subchunk(FILE *file, t_fmt_subchunk *fmt)
{
	if (fread(fmt, sizeof(t_fmt_subchunk), 1, file) != 1)
		return (0);
	if (strncmp((char *)fmt->subchunk_1id, "fmt ", 4) != 0)
		return (0);
	if (fmt->subchunk_1size > 16)
		fseek(file, fmt->subchunk_1size - 16, SEEK_CUR);
	return (1);
}
