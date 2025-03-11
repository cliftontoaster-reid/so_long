/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fs_read_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 11:27:03 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/11 13:09:50 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <fcntl.h>
#include <unistd.h>

#define BUFSIZE 1024

/*
 * Helper function that concatenates two strings.
 * It frees the first string (s1) and returns a newly allocated
 * string containing s1 followed by s2. If allocation fails,
	it frees s1 and returns NULL.
 */
char	*strjoinfree(char *s1, const char *s2)
{
	size_t	len1;
	size_t	len2;
	char	*new_str;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	new_str = malloc(len1 + len2 + 1);
	if (!new_str)
	{
		free(s1);
		return (NULL);
	}
	if (s1)
		ft_memcpy(new_str, s1, len1);
	if (s2)
		ft_memcpy(new_str + len1, s2, len2);
	new_str[len1 + len2] = '\0';
	free(s1);
	return (new_str);
}

/*
 * Reads data chunks from a file descriptor and appends to the result buffer.
 * Returns 1 on success, 0 on error.
 */
int	fs_read_chunks(int fd, char **result)
{
	char	buffer[BUFSIZE];
	ssize_t	bytes_read;
	char	*temp;

	bytes_read = read(fd, buffer, BUFSIZE - 1);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		temp = strjoinfree(*result, buffer);
		if (!temp)
			return (0);
		*result = temp;
		bytes_read = read(fd, buffer, BUFSIZE - 1);
	}
	if (bytes_read < 0)
		return (0);
	return (1);
}

/*
 * Reads data from a file descriptor into a dynamically allocated buffer.
 * Returns the buffer on success, or NULL on error.
 * Does not close the file descriptor.
 */
char	*fs_read_fd(int fd)
{
	char	*result;

	if (fd < 0)
		return (NULL);
	result = malloc(1);
	if (!result)
		return (NULL);
	result[0] = '\0';
	if (!fs_read_chunks(fd, &result))
	{
		free(result);
		return (NULL);
	}
	return (result);
}

/*
 * Reads an entire file into a dynamically allocated, null-terminated buffer.
 * Returns the buffer on success, or NULL on error.
 */
char	*fs_read_file(char *path)
{
	int		fd;
	char	*result;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (NULL);
	result = fs_read_fd(fd);
	close(fd);
	return (result);
}
