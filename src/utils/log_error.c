/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 15:07:40 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/06 15:23:23 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	log_error(char *msg, char *file, int line)
{
	ft_printf("\033[31m[ERROR] (%s:%d) %s\033[0m\n", file, line, msg);
}
