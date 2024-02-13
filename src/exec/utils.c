/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glambrig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 17:34:17 by glambrig          #+#    #+#             */
/*   Updated: 2024/02/13 16:27:04 by glambrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_arr(void **array, int size)
{
	int	i;

	if (array == NULL)
		return ;
	i = 0;
	while (i < size)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

size_t	lstlen(t_pars *lst)
{
	size_t	res;
	t_pars	*temp;

	temp = lst;
	res = 0;
	while (lst)
	{
		res++;
		lst = lst->next;
	}
	lst = temp;
	return (res);
}

/*Returns the number of elements in a given void ** array.*/
size_t	size_of_ptr_ptr(void **arr)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	while (arr[i] != NULL)
	{
		len++;
		i++;
	}
	return (len);
}

void	fork_error(int **fds, pid_t **ch_pid)
{
	perror("fork");
	free_arr((void **)fds, size_of_ptr_ptr((void **)fds));
	free(*ch_pid);
	exit(EXIT_FAILURE);
}