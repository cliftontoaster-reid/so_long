/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 11:18:01 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/06 15:20:23 by lfiorell         ###   ########.fr       */
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

// logging
void	log_error(char *msg, char *file, int line);
void	log_warning(char *msg, char *file, int line);
void	log_info(char *msg, char *file, int line);
void	log_debug(char *msg, char *file, int line);
#endif
