/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fs_read_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 11:27:03 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/04 14:29:26 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static inline char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*new;

	new = ft_strjoin(s1, s2);
	if (!new)
		return (NULL);
	free(s1);
	return (new);
}

char	*fs_read_file(char *path)
{
	int		fd;
	int		ret;
	char	buffer[256];
	char	*file;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (NULL);
	file = ft_strdup("");
	if (!file)
		return (NULL);
	ret = read(fd, buffer, 255);
	while (ret > 0)
	{
		buffer[ret] = '\0';
		file = ft_strjoin_free(file, buffer);
		if (!file)
			return (NULL);
		ret = read(fd, buffer, 255);
	}
	close(fd);
	return (file);
}
