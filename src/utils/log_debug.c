/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_debug.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 15:10:06 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/25 16:27:45 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils.h"
#include <stdarg.h>

void	log_debug(char *format, char *file, int line, ...)
{
	va_list	args;

	ft_printf("\033[35m[DEBUG] (%s:%d) ", file, line);
	va_start(args, line);
	ft_vprintf(format, args);
	va_end(args);
	ft_printf("\033[0m\n");
}
