/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jump_quote.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 06:30:22 by dthan             #+#    #+#             */
/*   Updated: 2020/12/31 17:43:52 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void jump_quote(char *input, int *i, char quote_type)
{
	(*i)++;
	while (input[*i])
	{
		if (input[*i] == quote_type && is_real_quote(input, *i))
			break;
		(*i)++;
	}
}
