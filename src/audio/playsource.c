/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   playsource.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 15:15:06 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/31 15:40:52 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "audio.h"
#include "utils.h"

void	playsource(t_openalsource *source)
{
	log_debug("Playing source %u", __FILE__, __LINE__, source->source);
	alSourcePlay(source->source);
}

void	pausesource(t_openalsource *source)
{
	log_debug("Pausing source %u", __FILE__, __LINE__, source->source);
	alSourcePause(source->source);
}

void	stopsource(t_openalsource *source)
{
	log_debug("Stopping source %u", __FILE__, __LINE__, source->source);
	alSourceStop(source->source);
}
