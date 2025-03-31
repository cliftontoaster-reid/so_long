/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_wav_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 15:41:53 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/31 15:43:49 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "audio.h"

void	free_wav_file(t_wav_file *wav_file)
{
	if (!wav_file)
		return ;
	if (wav_file->data)
	{
		free(wav_file->data);
		wav_file->data = NULL;
	}
}
