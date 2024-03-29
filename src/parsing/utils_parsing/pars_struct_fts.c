/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_struct_fts.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 08:22:54 by flverge           #+#    #+#             */
/*   Updated: 2024/03/02 10:33:09 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

t_utils	*utils_init_struct(int len)
{
	t_utils	*current;

	current = malloc(sizeof(t_utils));
	if (!current)
		exit(-1);
	current->result = ft_calloc((len + 1), sizeof(char *));
	if (!current->result)
		exit(-1);
	current->result[len] = 0;
	current->i = 0;
	current->j = 0;
	current->k = 0;
	current->starting_quote = 0;
	current->end_quote = 0;
	current->real_len = 0;
	return (current);
}
