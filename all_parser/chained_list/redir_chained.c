#include "../minishell.h"

t_redir	*new_redir_node(void)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir = ft_memset(redir, 0, sizeof(t_redir));
	return (redir);
}

t_redir	*attach_redir_node(t_redir *current)
{
	t_redir	*new;

	new = new_redir_node();
	current->r_next = new;
	return (new);
}
