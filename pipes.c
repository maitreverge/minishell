/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glambrig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 12:56:20 by glambrig          #+#    #+#             */
/*   Updated: 2024/02/06 12:58:25 by glambrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//ex. command arg arg operator command arg

int	lstlen(t_pars *lst)
{
	int		res;
	t_pars 	*temp;

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

/*
	Checks if there's another command after the initial two
	ex. checks for c in (a | b | c)
*/
bool	another_pipe_next(t_pars *lst)
{
	t_pars *temp;

	temp = lst;
	while (lst->next)
	{
		if (lst->next->isCommand== true)
			return (true);
		lst = lst->next;
	}
	lst = temp;
	return (false);
}

//Pipe, then fork, then dup2
void	pipes(t_pars *lst)
{
	t_pars 	*temp;
	int		*ch_pid;
	int		**fds;
	int		i; //for fork
	int		k; //for dup

	if (lst->isCommand != true)
		return ;

	//Allocate space
	ch_pid = ft_calloc(sizeof(int), lstlen(lst));
	fds = ft_calloc(sizeof(int *), lstlen(lst));
	i = 0;
	while (i < lstlen(lst))
		fds[i++] = ft_calloc(sizeof(int), 2 + 1);
	i = 0;
	temp = lst;
	
	//Create pipe
	if (pipe(fds[i]) < 0)
	{
		free(ch_pid);
		free_arr((void **)fds, lstlen(lst));
		perror("pipe");
		exit(EXIT_FAILURE);
	}

	//Fork
	k = 0;
	ch_pid[k] = fork();
	if (ch_pid[k] < 0)
	{
		free(ch_pid);
		free_arr((void **)fds, lstlen(lst));
		perror("fork");
		exit(EXIT_FAILURE);
	}
	//Redirect STDOUT, and execute command
	else if (ch_pid[k] == 0)
	{
		dup2(fds[i][1], STDOUT_FILENO);
		//Close the pipes, becaue STDOUT points to where we want, and we don't need the second identical fd open
		close(fds[i][1]);
		close(fds[i][0]);
		execve(lst->cmd->command_path, lst->cmd->name_options_args, NULL);
	}
	//Second fork
	ch_pid[++k] = fork();
	if (ch_pid[k] < 0)
	{
		free(ch_pid);
		free_arr((void **)fds, lstlen(lst));
		perror("fork");
		exit(EXIT_FAILURE);
	}
	//Second redirection, redirecting STDIN for 2nd command
	else if (ch_pid[k] == 0)
	{
		lst = lst->next;
		dup2(fds[i][0], STDIN_FILENO);
		if (another_pipe_next(lst) == true)
		{
			//ch_pid[++k] = fork();
			//if (ch_pid[k] == 0)
			pipes(lst);	//Recursive call to pipes(), will redirect the 2nd command's STDOUT to the 3rd's STDIN
			close(fds[i][0]);
			close(fds[i][1]);
		}
		else
		{
			close(fds[i][0]);
			close(fds[i][1]);
			execve(lst->cmd->command_path, lst->cmd->name_options_args, NULL);
		}
	}
	while (i < lstlen(lst))
	{
		wait(NULL);	
		close(fds[i][0]);
		close(fds[i][1]);
		i++;
	}

	//Free allocated memory
	lst = temp;
	free(ch_pid);
	free_arr((void **)fds, lstlen(lst));
}

int main(void) {
	// Create a sample linked list of commands
	t_pars *command1 = malloc(sizeof(t_pars));
	t_pars *command2 = malloc(sizeof(t_pars));
	t_pars *command3 = malloc(sizeof(t_pars));

	// Set the necessary fields for each command
	command1->isCommand = true;
	command1->cmd = malloc(sizeof(t_command));
	command1->cmd->command_path = "/bin/ls";
	command1->cmd->name_options_args = malloc(sizeof(char*) * 2);
	command1->cmd->name_options_args[0] = "ls";
	command1->cmd->name_options_args[1] = NULL;
	command1->next = command2;

	command2->isCommand = true;
	command2->cmd = malloc(sizeof(t_command));
	command2->cmd->command_path = "/usr/bin/grep";
	command2->cmd->name_options_args = malloc(sizeof(char*) * 3);
	command2->cmd->name_options_args[0] = "grep";
	command2->cmd->name_options_args[1] = "pipe";
	command2->cmd->name_options_args[2] = NULL;
	command2->next = command3;

	command3->isCommand = true;
	command3->cmd = malloc(sizeof(t_command));
	command3->cmd->command_path = "/usr/bin/wc";
	command3->cmd->name_options_args = malloc(sizeof(char*) * 2);
	command3->cmd->name_options_args[0] = "wc";
	command3->cmd->name_options_args[1] = NULL;
	command3->next = NULL;

	// Call the pipes function
	pipes(command1);

	// Free the allocated memory
	free(command1->cmd->name_options_args);
	free(command1->cmd);
	free(command1);
	free(command2->cmd->name_options_args);
	free(command2->cmd);
	free(command2);
	free(command3->cmd->name_options_args);
	free(command3->cmd);
	free(command3);

	return 0;
}
