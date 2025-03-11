/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fs_read_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 11:27:03 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/11 11:22:29 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
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

	len1 = s1 ? strlen(s1) : 0;
	len2 = s2 ? strlen(s2) : 0;
	new_str = malloc(len1 + len2 + 1);
	if (!new_str)
	{
		free(s1);
		return (NULL);
	}
	if (s1)
		memcpy(new_str, s1, len1);
	if (s2)
		memcpy(new_str + len1, s2, len2);
	new_str[len1 + len2] = '\0';
	free(s1);
	return (new_str);
}

/*
 * Reads data from a file descriptor into a dynamically allocated buffer.
 * Returns the buffer on success, or NULL on error.
 * Does not close the file descriptor.
 */
char	*fs_read_fd(int fd)
{
	char	buffer[BUFSIZE];
	ssize_t	bytes_read;
	char	*temp;
	char	*result;

	if (fd < 0)
		return (NULL);
	result = malloc(1);
	if (!result)
		return (NULL);
	result[0] = '\0';
	while ((bytes_read = read(fd, buffer, BUFSIZE - 1)) > 0)
	{
		buffer[bytes_read] = '\0';
		temp = strjoinfree(result, buffer);
		if (!temp)
			return (NULL);
		result = temp;
	}
	if (bytes_read < 0)
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
