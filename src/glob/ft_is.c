
int			ft_iscntrl(int c)
{
	return (c >= 0 && c <= 31);
}

int			ft_isblank(int c)
{
	return (c == ' ' || c == '\t');
}

int			ft_isgraph(int c)
{
	if (c >= '!' && c <= '~')
		return (1);
	return (0);
}