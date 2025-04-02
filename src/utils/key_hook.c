/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 15:03:21 by lfiorell          #+#    #+#             */
/*   Updated: 2025/04/02 11:56:46 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "artificial_stupidity.h"
#include "mlx.h"
#include "render.h"
#include "utils.h"
#include <X11/X.h>
#include <stdio.h>

char	**load_file(char *filepath)
{
	char	*file_content;
	char	**lines;

	file_content = fs_read_file(filepath);
	if (!file_content)
		return (NULL);
	lines = ft_split(file_content, '\n');
	free(file_content);
	return (lines);
}

void	funnywall(void)
{
	char	**messages;
	int		count;
	int		i;

	messages = load_file("assets/text/funnywall.txt");
	if (!messages)
		return ;
	count = 0;
	while (messages[count])
		count++;
	if (count > 0)
	{
		i = ft_rand_int(0, count);
		log_warning("%s [%x]", __FILE__, __LINE__, messages[i - 1], i);
	}
	i = 0;
	while (messages[i])
		free(messages[i++]);
	free(messages);
}

static void	scale_change(t_data *data, int change)
{
	data->scale += change;
	if (data->scale < 1)
		data->scale = 1;
	else if (data->scale > 10)
		data->scale = 10;
	mlx_destroy_window(data->mlx, data->win);
	data->win = mlx_new_window(data->mlx, data->img->width * data->scale,
			data->img->height * data->scale, GAME_NAME);
	mlx_hook(data->win, DestroyNotify, StructureNotifyMask, (int (*)())vkthxbye,
		data);
	mlx_key_hook(data->win, key_hook, data);
	crust_img_drop(data->img);
	data->img = crust_img_new(data->mlx, data->floor->width * data->scale,
			data->floor->height * data->scale);
	render(data, data->map);
}

int	key_hook(int kc, t_data *data)
{
	(void)data;
	if (kc == 65307 || kc == 113)
		kthxbye(data);
	else if (kc == 65451)
		scale_change(data, 1);
	else if (kc == 65453)
		scale_change(data, -1);
	move_dummies(data);
	if (kc == 100 || kc == 65363)
		move(data, 1, 0);
	else if (kc == 97 || kc == 65361)
		move(data, -1, 0);
	else if (kc == 119 || kc == 65362)
		move(data, 0, -1);
	else if (kc == 115 || kc == 65364)
		move(data, 0, 1);
	log_debug("Key pressed: %x", __FILE__, __LINE__, kc);
	if (didummies_reach_player(data))
	{
		log_error("Dummies kissed player", __FILE__, __LINE__);
		kthxbye(data);
	}
	return (0);
}
