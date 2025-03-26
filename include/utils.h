/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 11:18:01 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/25 16:35:07 by lfiorell         ###   ########.fr       */
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

// logging
void	log_error(char *format, char *file, int line,
			...) __attribute__((format(printf, 1, 4)));
void	log_warning(char *format, char *file, int line,
			...) __attribute__((format(printf, 1, 4)));
void	log_info(char *format, char *file, int line,
			...) __attribute__((format(printf, 1, 4)));
void	log_debug(char *format, char *file, int line,
			...) __attribute__((format(printf, 1, 4)));
#endif
