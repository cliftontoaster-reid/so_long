/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 11:18:01 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/27 10:20:41 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "libft.h"
# include <fcntl.h>
# include <stdbool.h>
# include <unistd.h>

bool	fs_exists(char *path);
char	*fs_read_file(char *path);
char	*ft_strerr(int errnum);
void	*freenull(void *ptr, void (*f)(void *));

# ifndef LOG_LEVEL
#  define LOG_LEVEL 0
# endif

// logging

# define LOG_LEVEL_ERROR 3
# define LOG_LEVEL_WARNING 2
# define LOG_LEVEL_INFO 1
# define LOG_LEVEL_DEBUG 0

void	log_error(char *format, char *file, int line,
			...) __attribute__((format(printf, 1, 4)));
void	log_warning(char *format, char *file, int line,
			...) __attribute__((format(printf, 1, 4)));
void	log_info(char *format, char *file, int line,
			...) __attribute__((format(printf, 1, 4)));
void	log_debug(char *format, char *file, int line,
			...) __attribute__((format(printf, 1, 4)));
#endif
