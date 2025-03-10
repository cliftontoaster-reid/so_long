/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 15:09:51 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/06 15:23:22 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	log_info(char *msg, char *file, int line)
{
	ft_printf("\033[36m[INFO] (%s:%d) %s\033[0m\n", file, line, msg);
}
