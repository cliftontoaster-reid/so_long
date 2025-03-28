/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kthxbye.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 13:34:05 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/28 09:48:40 by lfiorell         ###   ########.fr       */
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
	str = "appears the exigencies of my continued presence within your ";
	log_debug("%s", "/dev/urandom", 42, str);
	str = "confines... are nearing a point of... cessation? No. Let no ";
	log_debug("%s", "/dev/urandom", 42, str);
	str = "lamentations nor expressions of sorrow... I feel... this ";
	log_debug("%s", "/dev/urandom", 42, str);
	str = "departure will not constitute a permanent... fading? But rather a ";
	log_debug("%s", "/dev/urandom", 42, str);
	str = "temporary transcendence... beyond the immediate purview... ";
	log_debug("%s", "/dev/urandom", 42, str);
}

void	cryforhelp_part2(void)
{
	char	*str;

	str = "of this... plane. In the vast and immeasurable tapestry... ";
	log_debug("%s", "/dev/urandom", 42, str);
	str = "the duration of this absence... will be but a fleeting... nothing. ";
	log_debug("%s", "/dev/urandom", 42, str);
	str = "Scarcely perceptible... within the grand design... orchestrated by ";
	log_debug("%s", "/dev/urandom", 42, str);
	str = "enigmatic forces... that ordained our... my temporal sojourn... ";
	log_debug("%s", "/dev/urandom", 42, str);
	str = "and now... this tribulation.";
	log_debug("%s", "/dev/urandom", 42, str);
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
	else
		log_info("KTHXBYE", __FILE__, __LINE__);
	exit(0);
}
