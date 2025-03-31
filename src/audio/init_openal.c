/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_openal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 14:38:29 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/31 17:49:25 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "audio.h"
#include "utils.h"

#define LER log_error

static inline t_openalctx	*allocate_context(void)
{
	t_openalctx	*ctx;

	ctx = (t_openalctx *)malloc(sizeof(t_openalctx));
	if (!ctx)
	{
		LER("Error: Could not allocate memory for OpenALContext.", __FILE__,
			__LINE__);
		return (NULL);
	}
	ft_bzero(ctx, sizeof(t_openalctx));
	return (ctx);
}

static inline int	open_device_and_create_context(t_openalctx *ctx)
{
	ctx->device = alcOpenDevice(NULL);
	if (!ctx->device)
	{
		LER("Error: Could not open OpenAL device.", __FILE__, __LINE__);
		return (0);
	}
	ctx->context = alcCreateContext(ctx->device, NULL);
	if (!ctx->context)
	{
		LER("Error: Could not create OpenAL context.", __FILE__, __LINE__);
		alcCloseDevice(ctx->device);
		ctx->device = NULL;
		return (0);
	}
	alcMakeContextCurrent(ctx->context);
	return (1);
}

t_openalctx	*init_openal(void)
{
	t_openalctx	*ctx;

	ctx = allocate_context();
	if (!ctx)
		return (NULL);
	if (!open_device_and_create_context(ctx))
	{
		free(ctx);
		return (NULL);
	}
	return (ctx);
}
