/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/22 08:37:04 by tbreart           #+#    #+#             */
/*   Updated: 2016/07/25 23:30:15 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_BONUS_H
# define FT_BONUS_H

/*
**	add_hash.c
*/
int		add_bin_to_hashtable(char *bin, char *fullpath_bin);

/*
**	builtin_bonus.c
*/
int		builtin_bonus(void);

/*
**	builtin_change_prompt.c
*/
int		builtin_change_prompt(t_list *elem);

/*
**	builtin_goto.c
*/
int		builtin_goto(t_list *elem, char ***env);

/*
**	find_shell_lvl.c
*/
char	*find_shlvl(char **taab);

/*
**	hash.c
*/
char	*check_hashtable(char *bin, char **env);
int		hash_content(char *str);

/*
**	key_search_hist.c
*/
char	***get_tab_hist(void);
int		ft_key_search_hist(t_historic *termcaps, char **entry);

/*
**	meta_check_shellvar.c
*/
void	check_shell_variable(char **entry, char *tmp, char **env);

/*
**	meta_check_tild.c
*/
void	check_tild(char **entry);

/*
**	metacharacters.c
*/
int		convert_metacharacters(t_list *elem, char **env);
void	edit_line_meta(char **entry, char *value, int pos_key, int len_key);

/*
**	s_strsplit_with_quote.c
*/
char	**s_strsplit_with_quote(char *s, char c, const char *filename);

#endif
