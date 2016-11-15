/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_token.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 15:26:17 by tbreart           #+#    #+#             */
/*   Updated: 2016/11/15 15:28:08 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int		is_token_llr(t_list *elem)
{
		if (elem != NULL && elem->type == LEX_LL_R)
			return (1);
		return (0);
}
