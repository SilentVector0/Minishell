#include "../minishell.h"

static int	count_new(char *content)
{
	int		i;
	int		count;
	char	quote;

	count = 0;
	i = 0;
	while (content[i])
	{
		if (content[i] == '\'' || content[i] == '\"')
		{
			quote = content[i++];
			while (content[i] && quote != content[i])
			{
				count++;
				i++;
			}
			i++;
		}
		else
		{
			count++;
			i++;
		}
	}
	return (count);
}

char	*filter_dup(char *content)
{
	char	*res;
	int		i;
	int		count;
	char	quote;

	i = 0;
	count = 0;
	res = malloc(sizeof(char) * count_new(content) + 1);
	while (content[i])
	{
		if (content[i] == '\'' || content[i] == '\"')
		{
			quote = content[i++];
			while (content[i] && content[i] != quote)
				res[count++] = content[i++];
			i++;
		}
		else
		{
			res[count++] = content[i++];
		}
	}
	res[count] = '\0';
	return (res);
}
