/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_str_in_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 07:12:38 by tbreart           #+#    #+#             */
/*   Updated: 2016/11/03 07:12:49 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

char	*add_str_in_str(char *dest, char *src, int position)
{
	char	*new_str;

	new_str = s_strnew(ft_strlen(dest) + ft_strlen(src), __FILE__);
	ft_strncat(new_str, dest, position);
	ft_strcat(new_str, src);
	ft_strcat(new_str, dest + position);
	return (new_str);
}
