/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/11 14:42:14 by fjacquem          #+#    #+#             */
/*   Updated: 2016/05/11 14:42:15 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "implemt.h"

char	*ft_getenv(char **env, char *name)
{
	char	*ret;

	while (*env && ft_strncmp(name, *env, ft_strclen(*env, '=')))
		env++;
	if (!*env)
		return (NULL);
	if ((ret = ft_strchr(*env, '=')))
		return (ret + 1);
	return (*env);
}
