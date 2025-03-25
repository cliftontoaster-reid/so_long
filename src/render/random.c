/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:18:19 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/25 13:51:15 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static int	ft_rand_init(void)
{
	static int	fd = -1;

	if (fd == -1)
	{
		fd = open("/dev/random", O_RDONLY);
		if (fd == -1)
		{
			perror("open");
			exit(EXIT_FAILURE);
		}
	}
	return (fd);
}

static uint32_t	ft_rand_uint32(void)
{
	int				fd;
	unsigned char	buffer[4];
	ssize_t			bytes_read;
	uint32_t		brrrrr;

	fd = ft_rand_init();
	bytes_read = read(fd, buffer, 4);
	if (bytes_read != 4)
	{
		perror("read");
		exit(EXIT_FAILURE);
	}
	brrrrr = 0;
	brrrrr |= (uint32_t)buffer[0] << 24;
	brrrrr |= (uint32_t)buffer[1] << 16;
	brrrrr |= (uint32_t)buffer[2] << 8;
	brrrrr |= (uint32_t)buffer[3];
	return (brrrrr);
}

int	ft_rand_int(int x, int y)
{
	int			temp;
	uint64_t	range;
	uint64_t	limit;
	uint32_t	num;

	if (x > y)
	{
		temp = x;
		x = y;
		y = temp;
	}
	range = (uint64_t)y - (uint64_t)x + 1;
	if (range == 0)
		return (x);
	limit = ((uint64_t)UINT32_MAX + 1) / range * range;
	while (1)
	{
		num = ft_rand_uint32();
		if (num < limit)
			break ;
	}
	return ((int)((int64_t)x + (int64_t)(num % range)));
}

float	ft_rand_float(void)
{
	static int		fd = -1;
	unsigned char	buffer[4];
	ssize_t			bytes_read;
	uint32_t		num;

	if (fd == -1)
	{
		fd = open("/dev/random", O_RDONLY);
		if (fd == -1)
		{
			perror("open");
			exit(EXIT_FAILURE);
		}
	}
	bytes_read = read(fd, buffer, 4);
	if (bytes_read != 4)
	{
		perror("read");
		exit(EXIT_FAILURE);
	}
	num = 0;
	num |= (uint32_t)buffer[0] << 24 | (uint32_t)buffer[1] << 16;
	num |= (uint32_t)buffer[2] << 8 | (uint32_t)buffer[3];
	return ((float)num / 4294967296.0f);
}
