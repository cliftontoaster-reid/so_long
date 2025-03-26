/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 15:07:40 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/25 16:33:45 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils.h"

void	log_error(char *format, char *file, int line, ...)
{
	va_list	args;

	ft_printf("\033[31m[ERROR] (%s:%d) ", file, line);
	va_start(args, line);
	ft_vprintf(format, args);
	va_end(args);
	ft_printf("\033[0m\n");
}
