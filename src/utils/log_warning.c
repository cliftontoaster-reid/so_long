/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_warning.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 15:08:47 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/06 15:23:21 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	log_warning(char *msg, char *file, int line)
{
	ft_printf("\033[33m[WARNING] (%s:%d) %s\033[0m\n", file, line, msg);
}
