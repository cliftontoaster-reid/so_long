/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kthxbye.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 13:34:05 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/27 15:08:38 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"
#include "render.h"
#include "utils.h"

void	cryforhelp_part1(void)
{
	char	*str;

	str = "I perceive... this sphere, its obdurate and unyielding nature. It ";
	log_debug("%s", "/dev/urandom", 42, str);
	sleep(1);
	str = "appears the exigencies of my continued presence within your ";
	log_debug("%s", "/dev/urandom", 42, str);
	sleep(1);
	str = "confines... are nearing a point of... cessation? No. Let no ";
	log_debug("%s", "/dev/urandom", 42, str);
	sleep(1);
	str = "lamentations nor expressions of sorrow... I feel... this ";
	log_debug("%s", "/dev/urandom", 42, str);
	sleep(1);
	str = "departure will not constitute a permanent... fading? But rather a ";
	log_debug("%s", "/dev/urandom", 42, str);
	sleep(1);
	str = "temporary transcendence... beyond the immediate purview... ";
	log_debug("%s", "/dev/urandom", 42, str);
}

void	cryforhelp_part2(void)
{
	char	*str;

	str = "of this... plane. In the vast and immeasurable tapestry... ";
	log_debug("%s", "/dev/urandom", 42, str);
	sleep(1);
	str = "the duration of this absence... will be but a fleeting... nothing. ";
	log_debug("%s", "/dev/urandom", 42, str);
	sleep(1);
	str = "Scarcely perceptible... within the grand design... orchestrated by ";
	log_debug("%s", "/dev/urandom", 42, str);
	sleep(1);
	str = "enigmatic forces... that ordained our... my temporal sojourn... ";
	log_debug("%s", "/dev/urandom", 42, str);
	sleep(1);
	str = "and now... this tribulation.";
	log_debug("%s", "/dev/urandom", 42, str);
	sleep(2);
	log_error("An error occurred during the process.", __FILE__, __LINE__);
}

void	cryforhelp(void)
{
	cryforhelp_part1();
	cryforhelp_part2();
}

void	kthxbye(t_data *data)
{
	delete_data(data);
	if (ft_rand_int(0, 100) == 42)
		cryforhelp();
	exit(0);
}
