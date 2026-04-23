#include "../minishell.h"

void	init_replace(int *i, int *k, int *l)
{
	*i = 0;
	*k = 0;
	*l = 0;
}

char	*special_case(char **envp, int len)
{
	char	*res;

	if (envp == NULL)
	{
		res = malloc (sizeof(char) * 1);
		res[0] = '\0';
	}
	if (len == 1)
	{
		res = malloc (sizeof(char) * 2);
		res[0] = '$';
		res[1] = '\0';
	}
	return (res);
}

int	case_interrog(t_parser *parser, int *new_size, int *i, int *j)
{
	if (parser->arg[*j][*i] == '$')
	{
		if (parser->arg[*j][(*i) + 1] == '?')
		{
			if (parser->arg[*j][(*i) + 2] != '\0')
				(*i) += 2;
			*new_size = 0;
			return (1);
		}
	}
	return (0);
}
