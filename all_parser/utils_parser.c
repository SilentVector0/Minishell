
#include "../minishell.h"

int	is_redirect(t_token *token, int	*nb)
{
	if (token[*nb].type == TOKEN_IN || token[*nb].type == TOKEN_OUT
		|| token[*nb].type == TOKEN_APPEND || token[*nb].type == TOKEN_HEREDOC)
		return (1);
	return (0);
}