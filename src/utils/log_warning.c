/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_warning.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 15:08:47 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/27 09:54:31 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils.h"

void	log_warning(char *format, char *file, int line, ...)
{
	va_list	args;

	if (LOG_LEVEL > LOG_LEVEL_WARNING)
		return ;
	ft_printf("\033[33m[WARNING] (%s:%d) ", file, line);
	va_start(args, line);
	ft_vprintf(format, args);
	va_end(args);
	ft_printf("\033[0m\n");
}
