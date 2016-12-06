/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_shell_lvl.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/23 17:36:23 by tbreart           #+#    #+#             */
/*   Updated: 2016/06/23 17:36:35 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

char	*find_shlvl(char **taab)
{
	int		i;
	char	**tmp;
	char	*s;

	tmp = taab;
	i = 0;
	while (*tmp != NULL)
	{
		if (ft_strncmp_complete(*tmp, "SHLVL",
					len_before_thischar(*tmp, '=')) == 0)
		{
			i = ft_atoi(*tmp + 6);
			break ;
		}
		tmp++;
	}
	i++;
	s = s_itoa(i, __FILE__);
	return (s);
}
