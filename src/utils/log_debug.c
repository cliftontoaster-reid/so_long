/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_debug.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 15:10:06 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/06 15:22:54 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	log_debug(char *msg, char *file, int line)
{
	ft_printf("\033[35m[DEBUG] (%s:%d) %s\033[0m\n", file, line, msg);
}
