/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_openal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 14:46:24 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/31 14:46:43 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "audio.h"

void	free_openal(t_openalctx *ctx)
{
	if (ctx)
	{
		if (ctx->context)
			alcDestroyContext(ctx->context);
		if (ctx->device)
			alcCloseDevice(ctx->device);
		free(ctx);
	}
}
