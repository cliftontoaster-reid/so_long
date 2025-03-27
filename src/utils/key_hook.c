/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 15:03:21 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/27 16:32:46 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "utils.h"
#include <stdio.h>

static void	funnywall(void)
{
	char	*file_content;
	char	**messages;
	int		count;
	int		i;

	file_content = fs_read_file("assets/text/funnywall.txt");
	if (!file_content)
		return ;
	messages = ft_split(file_content, '\n');
	free(file_content);
	if (!messages)
		return ;
	count = 0;
	while (messages[count])
		count++;
	if (count > 0)
		log_warning("%s", __FILE__, __LINE__, messages[ft_rand_int(0, count)]);
	i = 0;
	while (messages[i])
		free(messages[i++]);
	free(messages);
}

static void	move(t_data *data, int x, int y)
{
	t_2d	new_pos;

	new_pos = posadd(data->player, x, y);
	if (data->map->map[new_pos.y][new_pos.x] == '1')
		return (funnywall());
	data->last_player = data->player;
	data->player = new_pos;
	data->moves++;
	render(data, data->map);
	log_debug("Player moved to %d, %d", __FILE__, __LINE__, data->player.x,
		data->player.y);
	log_info("Player has now made %d moves", __FILE__, __LINE__, data->moves);
}

int	key_hook(int kc, t_data *data)
{
	printf("Key pressed: %d\n", kc);
	(void)data;
	if (kc == 65307 || kc == 113)
		kthxbye(data);
	else if (kc == 100 || kc == 65363)
		move(data, 1, 0);
	else if (kc == 97 || kc == 65361)
		move(data, -1, 0);
	else if (kc == 119 || kc == 65362)
		move(data, 0, -1);
	else if (kc == 115 || kc == 65364)
		move(data, 0, 1);
	return (0);
}
