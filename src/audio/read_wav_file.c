/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_wav_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 13:48:49 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/31 14:35:31 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "audio.h"
#include "utils.h"
#include <stdio.h>
#include <string.h>

#define LER log_error

static inline int	read_data_subchunk(FILE *file, t_data_subchunk *dataHeader,
		unsigned char **data)
{
	while (1)
	{
		if (fread(dataHeader, sizeof(t_data_subchunk), 1, file) != 1)
			return (0);
		if (strncmp((char *)dataHeader->subchunk_2id, "data", 4) == 0)
			break ;
		fseek(file, dataHeader->subchunk_2size, SEEK_CUR);
	}
	*data = (unsigned char *)malloc(dataHeader->subchunk_2size);
	if (!(*data))
		return (0);
	if (fread(*data, dataHeader->subchunk_2size, 1, file) != 1)
	{
		free(*data);
		return (0);
	}
	return (1);
}

static inline ALenum	determine_audio_format(unsigned short numChannels,
		unsigned short bitsPerSample)
{
	if (numChannels == 1)
	{
		if (bitsPerSample == 8)
			return (AL_FORMAT_MONO8);
		else
			return (AL_FORMAT_MONO16);
	}
	else if (numChannels == 2)
	{
		if (bitsPerSample == 8)
			return (AL_FORMAT_STEREO8);
		else
			return (AL_FORMAT_STEREO16);
	}
	return (0);
}

static inline bool	readwavdata(t_wav_file *wav_file, char *filename)
{
	FILE	*file;

	file = fopen(filename, "rb");
	if (!file)
	{
		LER("Error: Could not open file %s", __FILE__, __LINE__, filename);
		return (true);
	}
	if (!read_riff_header(file, &wav_file->riff) || !read_fmt_subchunk(file,
			&wav_file->fmt) || !read_data_subchunk(file, &wav_file->data_header,
			&wav_file->data))
	{
		LER("Error: Invalid WAV file format", __FILE__, __LINE__);
		fclose(file);
		return (true);
	}
	fclose(file);
	return (false);
}

t_wav_data	read_wav_file(const char *filename)
{
	t_wav_data	wav;
	t_wav_file	wav_file;

	memset(&wav, 0, sizeof(wav));
	memset(&wav_file, 0, sizeof(wav_file));
	if (readwavdata(&wav_file, (char *)filename))
	{
		wav.data = NULL;
		return (wav);
	}
	wav.data = wav_file.data;
	wav.data_size = wav_file.data_header.subchunk_2size;
	wav.sample_rate = wav_file.fmt.sample_rate;
	wav.format = determine_audio_format(wav_file.fmt.num_channels,
			wav_file.fmt.bits_per_sample);
	if (wav.format == 0)
	{
		LER("Error: Unsupported audio format.", __FILE__, __LINE__);
		free(wav_file.data);
		wav.data = NULL;
	}
	return (wav);
}
