/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_options.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 15:49:49 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/31 15:53:11 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "audio.h"
#include "utils.h"

t_openalsource	*setlooping(t_openalsource *source, bool looping)
{
	if (looping)
	{
		log_debug("Setting source %u to loop", __FILE__, __LINE__,
			source->source);
		alSourcei(source->source, AL_LOOPING, AL_TRUE);
	}
	else
	{
		log_debug("Setting source %u to not loop", __FILE__, __LINE__,
			source->source);
		alSourcei(source->source, AL_LOOPING, AL_FALSE);
	}
	return (source);
}

void	setgain(t_openalsource *source, float gain)
{
	char	gain_str[16];

	snprintf(gain_str, sizeof(gain_str), "%.2f", gain);
	log_debug("Setting source %u gain to %s", __FILE__, __LINE__,
		source->source, gain_str);
	alSourcef(source->source, AL_GAIN, gain);
}

void	setpitch(t_openalsource *source, float pitch)
{
	char	pitch_str[16];

	snprintf(pitch_str, sizeof(pitch_str), "%.2f", pitch);
	log_debug("Setting source %u pitch to %s", __FILE__, __LINE__,
		source->source, pitch_str);
	alSourcef(source->source, AL_PITCH, pitch);
}
