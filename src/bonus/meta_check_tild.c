/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meta_check_tild.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/14 20:54:58 by tbreart           #+#    #+#             */
/*   Updated: 2016/07/26 00:21:31 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	check_tild(char **entry)
{
	int		i;
	char	*value;
	char	*tmp;
	char	***env;

	tmp = *entry;
	env = get_env();
	i = 0;
	if ((value = ft_getenv("HOME", *env)) == NULL)
		return ;
	while (tmp[i] != '\0')
	{
		if (tmp[i] == '~' && (i == 0 || tmp[i - 1] == ' ') &&
				(tmp[i + 1] == '/' || tmp[i + 1] == ' ' || tmp[i + 1] == '\0'))
		{
			edit_line_meta(entry, value, i, 1);
			tmp = *entry;
			i = 0;
		}
		i++;
	}
	free(value);
}
