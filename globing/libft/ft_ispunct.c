/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ispunct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 20:28:58 by mfamilar          #+#    #+#             */
/*   Updated: 2015/12/03 20:32:20 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_ispunct(int c)
{
	if ((c >= '!' && c <= '/') || (c >= ':' && c <= '@') || (c >= '[' &&
			c <= 96) || (c >= '{' && c <= '~'))
		return (1);
	return (0);
}