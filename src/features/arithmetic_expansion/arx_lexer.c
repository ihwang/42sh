/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arx_lexer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rklein <rklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 08:36:54 by rklein            #+#    #+#             */
/*   Updated: 2021/03/28 14:35:22 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		ft_arx_final_result(char **arx_token, long long int *res)
{
	int		i;
	int		len;
	char	*cmb;

	i = 0;
	len = 0;
	while (arx_token[i])
	{
		len += ft_strlen(arx_token[i]);
		i++;
	}
	cmb = ft_memalloc(sizeof(char) * (len + 1));
	i = 0;
	while (arx_token[i])
	{
		ft_strcat(cmb, arx_token[i]);
		i++;
	}
	*res = ft_atolli(cmb);
	free(cmb);
	ft_arraydel(arx_token);
	return (1);
}

int		ft_arx_token_exp(char **arx_token, long long int *res)
{
	int				i;
	long long int	t_res;
	char			*tmp;

	i = -1;
	while (arx_token[++i])
	{
		if (!(ft_expand_arx(ft_strdup(arx_token[i]), &t_res)))
		{
			ft_arraydel(arx_token);
			return (0);
		}
		else
		{
			tmp = arx_token[i];
			arx_token[i] = ft_llitoa(t_res);
			free(tmp);
		}
	}
	return (ft_arx_final_result(arx_token, res));
}

int		ft_bracket_check(char *exp, int qc)
{
	char	stack[1024];
	int		q;
	int		i[2];

	ft_bzero(stack, 1024);
	i[0] = 0;
	i[1] = -1;
	q = 0;
	while (exp[++i[1]])
	{
		if (exp[i[1]] == 34 && is_inhibitors(exp, i[1], exp[i[1]]))
			q = q ? 0 : 1;
		if ((exp[i[1]] == '(' && !qc) || (exp[i[1]] == '(' && (qc && !q)))
			stack[i[0]++] = exp[i[1]];
		else if ((exp[i[1]] == ')' && !qc) || (exp[i[1]] == ')' && (qc && !q)))
		{
			if (i[0] > 0 && stack[i[0] - 1] == '(')
				stack[--i[0]] = '\0';
			else
				return (-1);
		}
	}
	if (stack[0])
		return (0);
	return (1);
}

char	**ft_expsplit(char *arx)
{
	char	**arx_token;
	char	*exp;
	char	*tmp;
	int		i;

	arx_token = ft_strsplit(arx, '$');
	i = -1;
	while (arx_token[++i])
	{
		exp = ft_strjoin("$", arx_token[i]);
		tmp = arx_token[i];
		arx_token[i] = exp;
		free(tmp);
	}
	free(arx);
	return (arx_token);
}

void	ft_arx_token_move(char **arx_token, int i)
{
	char	*tmp;

	while (arx_token[++i])
	{
		if (arx_token[i + 1])
		{
			tmp = arx_token[i];
			arx_token[i] = ft_strdup(arx_token[i + 1]);
			free(tmp);
		}
		else
		{
			free(arx_token[i]);
			arx_token[i] = NULL;
		}
	}
}
