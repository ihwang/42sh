/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rklein <rklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 20:28:05 by rklein            #+#    #+#             */
/*   Updated: 2021/03/28 14:38:20 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	ft_arx_lexer(char *arx, long long int *res)
{
	char	**arx_token;
	char	*exp;
	char	*tmp;
	int		i;

	arx_token = ft_expsplit(arx);
	i = -1;
	while (arx_token[++i])
	{
		if (!(ft_bracket_check(arx_token[i], 1)))
		{
			exp = ft_strjoin(arx_token[i], arx_token[i + 1]);
			tmp = arx_token[i];
			arx_token[i] = exp;
			free(tmp);
			ft_arx_token_move(arx_token, i);
			i = -1;
		}
	}
	return (ft_arx_token_exp(arx_token, res));
}

int	ft_arx(t_process *p)
{
	int					i;
	int					len;
	long long int		res;
	char				*tmp;

	i = -1;
	while (p->av[++i])
	{
		len = ft_strlen(p->av[i]);
		if (ft_strnequ(p->av[i], "$((", 3) && p->av[i][len - 2] == ')' && \
		p->av[i][len - 1] == ')')
		{
			if (!(ft_arx_lexer(ft_strdup(p->av[i]), &res)))
				return (EXIT_FAILURE);
			tmp = p->av[i];
			p->av[i] = ft_llitoa(res);
			free(tmp);
		}
	}
	return (EXIT_SUCCESS);
}
