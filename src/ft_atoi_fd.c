/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_fd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/07 07:24:53 by tbreart           #+#    #+#             */
/*   Updated: 2016/06/07 07:25:11 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int	ft_issspace(int c)
{
	if ((c == ' ')
			|| (c == '\t')
			|| (c == '\n')
			|| (c == '\v')
			|| (c == '\f')
			|| (c == '\r'))
		return (1);
	return (0);
}

int			ft_atoi_fd(const char *str)
{
	char	*ptr;
	int		i;
	int		nb;

	ptr = (char*)str;
	i = 0;
	nb = 0;
	while (ft_issspace(ptr[i]))
		i++;
	while (ft_isdigit(ptr[i]))
		nb = nb * 10 + ptr[i++] - '0';
	return (nb);
}
