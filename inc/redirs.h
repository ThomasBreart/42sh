/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/22 10:52:08 by tbreart           #+#    #+#             */
/*   Updated: 2016/11/30 20:30:10 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_REDIRS_H
# define FT_REDIRS_H

# define PIPE_EXIT		0
# define PIPE_ENTRY		1

/*
**	check_fd_parent.c
*/
int		check_fd_parent(char *s, t_save_fd *save);

/*
**	cmd_pipe.c
*/
int		cmd_pipe(t_list *elem, char ***env, t_list *prog, t_save_fd *save);

/*
**	exec_aggregator_fd.c
*/
int		exec_aggregator_fd(char *s, t_save_fd *save);

/*
**exec_lc.c
*/
int		redir_file_lc(t_list *elem, t_save_fd *save, char **env);
int		exec_lc(t_list *elem, char ***env, t_list *prog, t_save_fd *save);

/*
**	exec_llc.c
*/
int		exec_llc(t_list *elem, char ***env, t_list *prog, t_save_fd *save);
int		redir_file_llc(t_list *elem, t_save_fd *save);

/*
**	exec_llc.c
*/
int		redir_llc_read_loop_gnl(t_historic *termcaps, t_list *elem, int fd);
int		redir_llc_read_loop_tty(t_historic *termcaps, t_list *elem, int fd);

/*
**exec_rc.c
*/
int		redir_file_rc(t_list *elem, t_save_fd *save, char **env);
int		exec_rc(t_list *elem, char ***env, t_list *prog, t_save_fd *save);

/*
**exec_rrc.c
*/
int		redir_file_rrc(t_list *elem, t_save_fd *save, char **env);
int		exec_rrc(t_list *elem, char ***env, t_list *prog, t_save_fd *save);

/*
**	redir_sub.c
*/
int		exec_redir_sub(t_list *elem, t_save_fd *save, t_list **current);

#endif
