/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newsource.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 14:48:15 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/31 15:49:17 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "audio.h"
#include "utils.h"

t_openalsource	*newsource(t_openalctx *ctx, t_wav_data *wav)
{
	t_openalsource	*src;

	(void)ctx;
	src = (t_openalsource *)malloc(sizeof(t_openalsource));
	if (!src)
	{
		log_error("Error: Could not allocate memory for AudioSource.", __FILE__,
			__LINE__);
		return (NULL);
	}
	alGenBuffers(1, &src->buffer);
	alBufferData(src->buffer, wav->format, wav->data, wav->data_size,
		wav->sample_rate);
	alGenSources(1, &src->source);
	alSourcei(src->source, AL_BUFFER, src->buffer);
	alSourcef(src->source, AL_GAIN, 1.0f);
	alSourcef(src->source, AL_PITCH, 1.0f);
	alSourcei(src->source, AL_LOOPING, AL_FALSE);
	return (src);
}
