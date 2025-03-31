/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   playmusic.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 17:07:51 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/31 17:18:30 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "audio.h"
#include "utils.h"

t_openalsource	*playmusic(t_openalctx *ctx, const char *filename)
{
	t_wav_data		wav_file;
	t_openalsource	*source;

	wav_file = read_wav_file(filename);
	if (wav_file.data == NULL)
	{
		log_error("Error: Could not read WAV file %s", __FILE__, __LINE__,
			filename);
		return (NULL);
	}
	source = newsource(ctx, &wav_file);
	if (source == NULL)
	{
		log_error("Error: Could not create OpenAL source", __FILE__, __LINE__);
		free_wav_data(&wav_file);
		return (NULL);
	}
	setgain(source, 0.5f);
	setpitch(source, 1.0f);
	setlooping(source, true);
	playsource(source);
	free_wav_data(&wav_file);
	return (source);
}
