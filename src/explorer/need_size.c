#include <explorer.h>

int				can_drawing(struct winsize *ws)
{
	int			cur;
	int			ret;

	ret = 1;
	cur = recalc_need_size(NULL, NULL);
	if (ws->ws_col < cur || ws->ws_row <= 3)
	{
		write(1, "\033c", 2);
		ret = 0;
	}
	if (ws->ws_col < cur)
	{
		write(1, "Bad size: ", 10);
		ft_putnbr_fd(cur, 2);
		write(1, " columns needed\n", 16);
	}
	if (ws->ws_row <= 3)
		write(1, "Bad size: more row needed\n", 26);
	return (ret);
}

int				get_offset(int offsets[6], t_file *f)
{
	int			offset;

	offset = 3 + 10 + 1 + 1 + 2 + 2 + 1 + 12 + 1;
	offset += offsets[0] + offsets[1] + offsets[2] +
			offsets[3] + offsets[4] + offsets[5];
	offset += f->p.len_name + f->p.len_nlink + f->p.len_usr + f->p.len_grp;
	offset += f->p.len_ma + f->p.len_mi + f->p.len_size;
	return (offset);
}

int				get_need_size(t_args *a, t_file *root)
{
	int			max;
	int			offset;

	max = 0;
	prepare(a, root);
	while (root)
	{
		offset = get_offset(a->offset, root);
		if (offset > max)
			max = offset;
		root = root->next;
	}
	return (max);
}

int				recalc_need_size(void *na, void *nf)
{
	static t_args	*a = NULL;
	static t_file	*f = NULL;

	if (na && nf)
	{
		a = na;
		f = nf;
	}
	return (get_need_size(a, f));
}
