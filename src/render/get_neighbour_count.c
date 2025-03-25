/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_neighbour_count.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 11:28:14 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/25 15:57:26 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

/// @brief Returns the number of neighbours in a given bitfield
///
/// This function is used to count the number of neighbours in a given bitfield
/// representing the neighbours of a given position in the map.
///
/// @param neighbours the bitfield representing the neighbours
/// @return the number of neighbours
int	get_neighbour_count(uint8_t neighbours)
{
	int	count;

	count = 0;
	if (neighbours & 1)
		count++;
	if (neighbours & 2)
		count++;
	if (neighbours & 4)
		count++;
	if (neighbours & 8)
		count++;
	return (count);
}

/// @brief Returns the number of neighbours in a given bitfield
///
/// This function is used to count the number of neighbours in a given bitfield
/// representing the neighbours of a given position in the map.
///
/// @param neighbours the bitfield representing the neighbours
/// @return the number of neighbours
int	get_neighbour_count_extended(uint8_t neighbours)
{
	int	count;

	count = get_neighbour_count(neighbours);
	if (neighbours & 16)
		count++;
	if (neighbours & 32)
		count++;
	if (neighbours & 64)
		count++;
	if (neighbours & 128)
		count++;
	return (count);
}
