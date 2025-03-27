/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 14:04:11 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/27 14:20:52 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	key_hook(int kc, t_data *data)
{
	log_debug("Key pressed: %d", __FILE__, __LINE__, kc);
	(void)data;
	if (kc == 65307)
		kthxbye(data);
	return (0);
}
