/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_struct_fts.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 08:22:54 by flverge           #+#    #+#             */
/*   Updated: 2024/02/06 12:23:10 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// void	init_pars_struct(t_pars **pars)
// {
// 	t_pars *current;

// 	current = *pars;
// 	current->test = 'X'; // to delete in the .h as well
// 	current->command = false;
// 	current->file = false;
// 	current->pipe = false;
// 	current->red_in = false;
// 	current->red_in_delim = false;
// 	current->red_in = false;
// 	current->red_out_app = false;
	
// }

void	utils_init_struct(t_utils **utils, int len)
{
	t_utils *current;

	current = *utils;

	current->result = (char **)ft_calloc(sizeof(char *), len + 1);
	if (!current->result)
		exit(-1); // ! maybe freeing shit right here
	current->to_allocate = NULL;
	current->i = 0;
	current->j = 0;
	current->k = 0;
	current->starting_quote = 0;
	current->end_quote = 0;
	current->real_len = 0;
}