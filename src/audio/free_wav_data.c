/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_wav_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 14:47:25 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/31 17:43:00 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "audio.h"
#include "libft.h"

void	free_wav_data(t_wav_data *wavData)
{
	if (wavData)
	{
		if (wavData->data)
			free(wavData->data);
		free(wavData);
	}
}
