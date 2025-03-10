/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 15:08:20 by lfiorell          #+#    #+#             */
/*   Updated: 2025/02/28 17:02:18 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

# include "img/set.h"
# include "libft.h"

typedef struct s_data
{
	void	*mlx;
	void	*win;
	t_set	*set;
}			t_data;

typedef enum e_trinary
{
	ZERO,
	ZONE,
	ZTWO,
}			t_trinary;

#endif
