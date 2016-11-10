/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_tab.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/01 10:58:50 by tbreart           #+#    #+#             */
/*   Updated: 2016/10/14 08:29:01 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_tab(char **argv)
{
	if (argv == NULL)
	{
		ft_putendl_fd("argv NULL", STDERR_FILENO);
		return ;
	}
	while (*argv != NULL)
	{
		ft_putendl_fd(*argv, STDERR_FILENO);
		++argv;
	}
}
