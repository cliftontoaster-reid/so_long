/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_warning.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 15:08:47 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/25 16:34:15 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils.h"

void	log_warning(char *format, char *file, int line, ...)
{
	va_list	args;

	ft_printf("\033[33m[WARNING] (%s:%d) ", file, line);
	va_start(args, line);
	ft_vprintf(format, args);
	va_end(args);
	ft_printf("\033[0m\n");
}
