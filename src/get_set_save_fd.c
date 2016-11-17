/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_set_save_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 02:34:06 by tbreart           #+#    #+#             */
/*   Updated: 2016/11/17 02:34:21 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

t_save_fd	*get_set_save_fd(t_save_fd *save)
{
	static	t_save_fd	savecpy;

	if (save != NULL)
		savecpy = *save;
	return (&savecpy);
}
