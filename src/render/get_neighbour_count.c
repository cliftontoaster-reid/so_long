/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_neighbour_count.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 11:28:14 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/18 11:28:29 by lfiorell         ###   ########.fr       */
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
inline int	get_neighbour_count(uint8_t neighbours)
{
	int	count;

	count = 0;
	if (neighbours & 0b00000001)
		count++;
	if (neighbours & 0b00000010)
		count++;
	if (neighbours & 0b00000100)
		count++;
	if (neighbours & 0b00001000)
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
	if (neighbours & 0b00010000)
		count++;
	if (neighbours & 0b00100000)
		count++;
	if (neighbours & 0b01000000)
		count++;
	if (neighbours & 0b10000000)
		count++;
	return (count);
}
