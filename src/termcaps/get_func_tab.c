/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_func_tab.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/17 23:03:31 by tbreart           #+#    #+#             */
/*   Updated: 2016/12/06 12:43:27 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static void	normilol2(t_func_tab **funcs)
{
	t_func_tab	*tmp;

	tmp = *funcs;
	tmp[18].k = KEY_EOF;
	tmp[18].f = &ft_key_eof;
	tmp[19].k = KEY_TAB;
	tmp[19].f = &ft_key_tab;
//	tmp[20].k = KEY_CTRL_R;
//	tmp[20].f = &ft_key_search_hist;
	tmp[20].k = KEY_CTRL_E;
	tmp[20].f = &ft_key_selection_mode;
	tmp[21].k = KEY_NOPE;
	tmp[21].f = NULL;
}

static void	normilol(t_func_tab **funcs)
{
	t_func_tab	*tmp;

	normilol2(funcs);
	tmp = *funcs;
	tmp[8].k = KEY_HOME;
	tmp[8].f = &ft_key_home;
	tmp[9].k = KEY_END;
	tmp[9].f = &ft_key_end;
	tmp[10].k = KEY_CTRL_P;
	tmp[10].f = &ft_key_paste;
	tmp[11].k = KEY_CTRL_K;
	tmp[11].f = &ft_key_cut_part;
	tmp[12].k = KEY_CTRL_U;
	tmp[12].f = &ft_key_cut_all;
	tmp[13].k = KEY_CTRL_T;
	tmp[13].f = &ft_key_copy_all;
	tmp[14].k = KEY_CTRL_H;
	tmp[14].f = &ft_key_copy_part;
	tmp[15].k = KEY_DEL;
	tmp[15].f = &ft_key_del;
	tmp[16].k = KEY_SUPP;
	tmp[16].f = &ft_key_supp;
	tmp[17].k = KEY_RET;
	tmp[17].f = &ft_key_ret;
}

t_func_tab	*get_func_tab(void)
{
	static t_func_tab *funcs = NULL;

	if (funcs == NULL)
	{
		funcs = (t_func_tab*)s_memalloc(sizeof(t_func_tab) * 22, __FILE__);
		normilol(&funcs);
		funcs[0].k = KEY_LEFT;
		funcs[0].f = &ft_key_left;
		funcs[1].k = KEY_RIGHT;
		funcs[1].f = &ft_key_right;
		funcs[2].k = KEY_UP;
		funcs[2].f = &ft_key_up;
		funcs[3].k = KEY_DOWN;
		funcs[3].f = &ft_key_down;
		funcs[4].k = KEY_SHIFT_LEFT;
		funcs[4].f = &ft_key_shift_left;
		funcs[5].k = KEY_SHIFT_RIGHT;
		funcs[5].f = &ft_key_shift_right;
		funcs[6].k = KEY_SHIFT_UP;
		funcs[6].f = &ft_key_shift_up;
		funcs[7].k = KEY_SHIFT_DOWN;
		funcs[7].f = &ft_key_shift_down;
		normilol(&funcs);
	}
	return (funcs);
}
