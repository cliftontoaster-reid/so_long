/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_openal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 18:10:25 by creid             #+#    #+#             */
/*   Updated: 2025/03/31 17:54:10 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "audio.h"

void	free_openal(t_openalctx *ctx)
{
	if (ctx)
	{
		if (ctx->context)
		{
			alcMakeContextCurrent(NULL);
			alcDestroyContext(ctx->context);
			ctx->context = NULL;
		}
		if (ctx->device)
		{
			alcCloseDevice(ctx->device);
			ctx->device = NULL;
		}
		free(ctx);
	}
}
