#include "../minishell.h"

t_parser	*new_node(void)
{
	t_parser	*parser;

	parser = malloc(sizeof(t_parser));
	if (!parser)
		return (NULL);
	parser = ft_memset(parser, 0, sizeof(t_parser));
	return (parser);
}
