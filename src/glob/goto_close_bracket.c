/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   goto_close_bracket.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 17:49:39 by mfamilar          #+#    #+#             */
/*   Updated: 2016/12/01 17:50:46 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_glob.h>

int			goto_close_bracket(const char *s)
{
	int		i;
	int		open;

	i = 0;
	open = 1;
	while (s[i])
	{
		if (s[i] == ']')
			open--;
		else if (s[i] == '[')
			open++;
		if (!open)
			return (i);
		i++;
	}
	return (i);
}
