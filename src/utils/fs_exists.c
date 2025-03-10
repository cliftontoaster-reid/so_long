/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fs_exists.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 11:20:58 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/04 14:28:55 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

bool	fs_exists(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (false);
	close(fd);
	return (true);
}
