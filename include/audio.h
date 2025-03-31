/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 13:14:27 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/31 15:49:30 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AUDIO_H
# define AUDIO_H

# include "AL/al.h"
# include "AL/alc.h"
# include "data.h"
# include <stdio.h>
# include <stdlib.h>

typedef struct s_openalctx
{
	ALCdevice		*device;
	ALCcontext		*context;
}					t_openalctx;

typedef struct s_openalsource
{
	ALuint			source;
	ALuint			buffer;
}					t_openalsource;

// Structures for reading the WAV file header
typedef struct t_riff_header
{
	/// "RIFF"
	unsigned char	chunk_id[4];
	unsigned int	chunk_size;
	/// "WAVE"
	unsigned char	format[4];
}					t_riff_header;

typedef struct t_fmt_subchunk
{
	/// "fmt "
	unsigned char	subchunk_1id[4];
	unsigned int	subchunk_1size;
	unsigned short	audio_format;
	unsigned short	num_channels;
	unsigned int	sample_rate;
	unsigned int	byte_rate;
	unsigned short	block_align;
	unsigned short	bits_per_sample;
}					t_fmt_subchunk;

typedef struct t_data_subchunk
{
	/// "data"
	unsigned char	subchunk_2id[4];
	unsigned int	subchunk_2size;
}					t_data_subchunk;

// Structure to hold the loaded WAV data
typedef struct t_wav_data
{
	ALenum			format;
	ALsizei			sample_rate;
	ALsizei			data_size;
	unsigned char	*data;
}					t_wav_data;

typedef struct t_wav_file
{
	t_riff_header	riff;
	t_fmt_subchunk	fmt;
	t_data_subchunk	data_header;
	unsigned char	*data;
}					t_wav_file;

t_openalctx			*init_openal(void);
void				free_openal(t_openalctx *ctx);

t_wav_data			read_wav_file(const char *filename);
void				free_wav_data(t_wav_data *wav);
void				free_wav_file(t_wav_file *wav_file);

int					read_riff_header(FILE *file, t_riff_header *riff);
int					read_fmt_subchunk(FILE *file, t_fmt_subchunk *fmt);

t_openalsource		*newsource(t_openalctx *ctx, t_wav_data *wav);
void				freesource(t_openalsource *source);

void				playsource(t_openalsource *source);
void				pausesource(t_openalsource *source);
void				stopsource(t_openalsource *source);

t_openalsource		*setlooping(t_openalsource *source, bool looping);
void				setgain(t_openalsource *source, float gain);
void				setpitch(t_openalsource *source, float pitch);

#endif
