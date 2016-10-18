/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/18 15:27:19 by mfamilar          #+#    #+#             */
/*   Updated: 2016/10/18 15:40:56 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int	get_len_of_int(int nb)
{
	int	i;

	i = 0;
	while (nb > 0)
	{
		nb /= 10;
		i++;
	}
	return (i);
}

int	history_usage(void)
{
	ft_putstr_fd("history: usage: history [-c] [-d offset] [n] or", 2);
	ft_putstr_fd("history -awrn [filename] or history -ps arg [arg...]\n", 2);
	return (1);
}
