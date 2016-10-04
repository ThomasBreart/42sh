/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hash.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/09 13:24:02 by mfamilar          #+#    #+#             */
/*   Updated: 2016/09/26 08:50:29 by Marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		ft_hash(char *name)
{
	int	hash;
	int	bash;
	int first;
	int	indice;

	hash = 1;
	bash = 0;
	indice = 1;
	while (name[indice - 1])
	{
		if (indice == 1)
			first = name[indice - 1];
		hash = (hash + name[indice - 1]) % 65521;
		bash = (bash + hash) * first % 65521;
		indice++;
	}
	return ((bash << 16) | hash);
}

char	*hash_cmd(char *cmd)
{
	char			*fullpath;
	t_hash_tree		*tree;
	int				ret;

	ret = ft_hash(cmd);
	tree = ft_stock_tree(NULL);
	fullpath = search_node(tree, ret);
	return (fullpath);
}
