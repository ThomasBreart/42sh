/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 01:09:07 by tbreart           #+#    #+#             */
/*   Updated: 2016/11/18 01:09:21 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"


int			char_is_escape(char *str, int index)
{
	int		is_escape;

	if (index == 0)
		return (0);
	is_escape = 0;
	--index;
	while (index > 0 && str[index] == '\\')
	{
		if (is_escape == 0)
			is_escape = 1;
		else
			is_escape = 0;
		--index;
	}
	return (is_escape);
}
