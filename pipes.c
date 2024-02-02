/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glambrig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 12:56:20 by glambrig          #+#    #+#             */
/*   Updated: 2024/02/02 13:54:57 by glambrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	int stdout_cp;

	stdout_cp = dup(1);
	ft_putstr_fd("hello to stdout!", 1);
	ft_putstr_fd("hello to copy!", stdout_cp);
}