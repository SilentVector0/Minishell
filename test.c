#include "minishell.h"

char	*filter_dup(char *content)
{
	int	i;
	int	count;
	char *res;

	i = 0;
	count = 0;
	while(content[i])
	{
		if (content[i] != '\'' && content[i] != '\"')
			count++;
		i++;
	}
	res = malloc(sizeof(char) * count + 1);
	i = 0;
	count = 0;
	while (content[i])
	{
		if (content[i] != '\'' && content[i] != '\"')
		{
			res[count] = content[i];
			count++;
		}
		i++;
	}
	res[count] = '\0';
	return (res);
}

int main(void)
{
	char *test = "\"hello\"\'world\'";
	printf("%s\n", filter_dup(test));
}