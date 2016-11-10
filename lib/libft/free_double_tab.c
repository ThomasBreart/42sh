/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_double_tab.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/25 21:17:01 by tbreart           #+#    #+#             */
/*   Updated: 2016/10/11 03:50:38 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	free_double_tab(char **taab)
{
	char	**tmp;

	if (taab == NULL)
		return ;
	tmp = taab;
	while (*tmp != NULL)
	{
		free(*tmp);
		++tmp;
	}
	ft_memdel((void**)&taab);
}
