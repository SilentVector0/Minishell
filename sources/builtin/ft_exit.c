/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroduit <aroduit@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 07:59:50 by aroduit           #+#    #+#             */
/*   Updated: 2026/06/07 07:59:50 by aroduit          ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

long	ft_parse_exit(const char *nptr, long *out)
{
	long	res;
	long	sign;

	res = 0;
	sign = 1;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == ' ')
		nptr++;
	if (*nptr == '+' || *nptr == '-')
		if (*nptr++ == '-')
			sign = -1;
	while (*nptr >= '0' && *nptr <= '9')
	{
		if ((res * sign) > (LONG_MAX - (*nptr - '0')) / 10
			|| (res * sign) < (LONG_MIN + (*nptr - '0')) / 10)
			return (0);
		res = res * 10 + (*nptr++ - '0');
	}
	if (*nptr)
		return (0);
	*out = res * sign;
	return (1);
}

int	ft_exit(t_parser *parser, t_shell *shell)
{
	long	code;

	ft_putstr_fd("exit\n", 1);
	if (!parser->arg[1])
	{
		code = shell->exit_status;
		free_all(parser, shell);
		exit (code);
	}
	if (!ft_parse_exit(parser->arg[1], &code))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(parser->arg[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		free_all(parser, shell);
		exit(2);
	}
	if (parser->arg[2])
		return (ft_putstr_fd("minishell: exit: too many arguments\n", 2), 1);
	free_all(parser, shell);
	exit ((unsigned char)code);
}
