/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glambrig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 12:56:20 by glambrig          #+#    #+#             */
/*   Updated: 2024/02/08 12:41:20 by glambrig         ###   ########.fr       */
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
// void	pipes(t_pars *lst, int fd_stdin)
// {
// 	t_pars 	*temp;
// 	int		*ch_pid;
// 	int		**fds;
// 	int		i; //for fork
// 	int		k; //for dup

// 	if (lst->isCommand == false)
// 		return ;

// 	//Allocate space
// 	ch_pid = ft_calloc(sizeof(int), lstlen(lst));
// 	fds = ft_calloc(sizeof(int *), lstlen(lst));
// 	i = 0;
// 	while (i < lstlen(lst))
// 		fds[i++] = ft_calloc(sizeof(int), 2 + 1);
// 	i = 0;
// 	temp = lst;

// 	//Create pipe
// 	if (pipe(fds[i]) < 0)
// 	{
// 		free(ch_pid);
// 		free_arr((void **)fds, lstlen(lst));
// 		perror("pipe");
// 		exit(EXIT_FAILURE);
// 	}

// 	if (lst->prev != NULL)	//If this is not the first command
// 	{
// 		if (dup2(fd_stdin, fds[i][0]) < 0)
// 		{
// 			free(ch_pid);
// 			free_arr((void **)fds, lstlen(lst));
// 			perror("dup2");
// 			exit(EXIT_FAILURE);
// 		}
// 		close(fd_stdin);
// 	}
// 	//Fork
// 	k = 0;
// 	ch_pid[k] = fork();
// 	if (ch_pid[k] < 0)
// 	{
// 		free(ch_pid);
// 		free_arr((void **)fds, lstlen(lst));
// 		perror("fork");
// 		exit(EXIT_FAILURE);
// 	}
// 	//Redirect STDOUT, and execute command
// 	else if (ch_pid[k] == 0)
// 	{
// 		if (dup2(fds[i][1], STDOUT_FILENO) < 0)
// 		{
// 			free(ch_pid);
// 			free_arr((void **)fds, lstlen(lst));
// 			perror("dup2");
// 			exit(EXIT_FAILURE);
// 		}
// 		//Close the pipes, becaue STDOUT points to where we want, and we don't need the second identical fd open
// 		close(fds[i][1]);
// 		close(fds[i][0]);
// 		execve(lst->cmd->command_path, lst->cmd->name_options_args, NULL);
// 	}
// 	//Second fork
// 	ch_pid[++k] = fork();
// 	if (ch_pid[k] < 0)
// 	{
// 		free(ch_pid);
// 		free_arr((void **)fds, lstlen(lst));
// 		perror("fork");
// 		exit(EXIT_FAILURE);
// 	}
// 	//Second redirection, redirecting STDIN for 2nd command
// 	////////////////////
// 	else if (ch_pid[k] == 0)
// 	{
// 		lst = lst->next;
// 		dup2(fds[i][0], STDIN_FILENO);
// 		close(fds[i][0]);
// 		if (another_pipe_next(lst) == true)
// 		{
// 			int fds_next[2];
// 			pipe(fds_next);
// 			pid_t next_pid = fork();
// 			if (next_pid == 0)
// 			{
// 				dup2(fds_next[1], STDOUT_FILENO);
// 				close(fds_next[0]);
// 				close(fds_next[1]);
// 				execve(lst->cmd->command_path, lst->cmd->name_options_args, NULL);
// 			}
// 			else
// 			{
// 				close(fds_next[1]);
// 				pipes(lst, fds_next[0]);	//Recursive call to pipes(), will redirect the 2nd command's STDOUT to the 3rd's STDIN
// 				wait(NULL);
// 			}
// 		}
// 		else
// 		{
// 			execve(lst->cmd->command_path, lst->cmd->name_options_args, NULL);
// 		}
// 	}
// 	while (i < lstlen(lst))
// 	{
// 		wait(NULL);
// 		close(fds[i][0]);
// 		close(fds[i][1]);
// 		i++;
// 	}

// 	//Free allocated memory
// 	lst = temp;
// 	free(ch_pid);
// 	free_arr((void **)fds, lstlen(lst));
// }

/*
	Allocates space for fds and child pid array,
		and creates the pipe links in fds
*/
int	**create_pipes(t_pars *lst, pid_t **ch_pid)
{
    int		len;
    int		i;
    int 	**fds;

	len = lstlen(lst);
	*ch_pid = ft_calloc(sizeof(pid_t), len);
	fds = ft_calloc(sizeof(int *), len);
	i = 0;
    while (i < len)
    {
        fds[i] = ft_calloc(sizeof(int), 2);
        if (pipe(fds[i]) == -1)
        {
            perror("pipe");
			free_t_pars(&lst);
			free_arr((void **)fds, sizeof(fds) / sizeof(fds[0]));
            exit(EXIT_FAILURE);
        }
		i++;
    }
    return (fds);
}

/*
	Handles '>' and '>>' operators.
*/
int	redirect_output(t_pars *lst, int input_fd)
{
	int		i;
	int		fd[2];
	int		open_fd;
	pid_t	ch_pid;
	char	*buff;

	if (pipe(fd) < 0)
    {
		perror("pipe");
		free_t_pars(&lst);
		exit(EXIT_FAILURE);
	}
	if (dup2(input_fd, fd[0]) < 0)
	{
		perror("dup2");
		free_t_pars(&lst);
		exit(EXIT_FAILURE);
	}
	close(fd[0]);
	ch_pid = fork();
	if (ch_pid == 0)
	{
		if (lst->next->fl->file_exist && lst->next->fl->auth_w == true && lst->next->which_redir == '>')
			open_fd = open(lst->next->fl->file_name, O_WRONLY | O_CREAT);
		else if (lst->next->fl->file_exist && lst->next->fl->auth_w == true && lst->next->which_redir == '>>')
			open_fd = open(lst->next->fl->file_name, O_WRONLY | O_APPEND | O_CREAT);
		else
			return (ft_putendl_fd("Error, insufficient permissions.", 2), 1);
		while (i == 1)
			i = read(input_fd, &buff, 1); //buff uninitalized here, fix
		if (i == -1)
			return (ft_putendl_fd("Error, read() call failed.", 2), 1);
		ft_putstr_fd(buff, open_fd);	
	}
	else if (ch_pid < 0)
	{
		perror("fork");
		free_t_pars(&lst);
		exit(EXIT_FAILURE);
	}
	close(fd[0]);
	close(fd[1]);
	wait(NULL);
}

/*
	Handles the pipe '|' operator.
*/
void	pipes(t_pars *lst, int input_fd)
{
    int i;
    int **fds;
    pid_t *ch_pid;
    t_pars *temp;

	if (lst->prev->killswitch == true)
	{
		free_t_pars(&lst);
		ft_putendl_fd("Pipes: Error: invalid input.", 2);
		return ;
	}
	i = 0;
	fds = create_pipes(lst, &ch_pid);
	temp = lst;
    while (lst != NULL)
    {
        ch_pid[i] = fork();
        if (ch_pid[i] == 0)
        {
            if (input_fd != -1)	//If it's not the first time pipes() is called, we redirect STDIN
            {
                dup2(input_fd, STDIN_FILENO);
                close(input_fd);
            }
            if (lst->next != NULL && lst->next->next != NULL && lst->next->next->isCommand == true)	//If it's not the last node, we redirect STDOUT
                dup2(fds[i][1], STDOUT_FILENO);
            close(fds[i][0]);	//We close Read end of pipe because we never use it. We only use input_fd/STDIN.
            if (i != 0)	//Closes the Write end of the previous pipe, if it exists
                close(fds[i - 1][1]);
            execve(lst->cmd->command_path, lst->cmd->name_options_args, NULL);
        }
        else if (ch_pid[i] < 0)	//Error
        {
            perror("fork");
			free_arr((void **)fds, sizeof(fds) / sizeof(fds[0]));
			free(ch_pid);
            exit(EXIT_FAILURE);
        }
        close(fds[i][1]);
        if (i != 0)
            close(fds[i - 1][0]);
        input_fd = fds[i][0];
        i++;
        lst = lst->next;
    }
	i = 0;
    close(fds[0][0]);
    while (i < lstlen(temp))
    {
        wait(NULL);
        // close(fds[i][0]);
        i++;
    }
    // Free allocated memory
    free(ch_pid);
    free_arr((void **)fds, lstlen(temp));
}

int main(void) {
	// Create a sample linked list of commands
	t_pars *command1 = ft_calloc(sizeof(t_pars), 1);
	t_pars *command2 = ft_calloc(sizeof(t_pars), 1);
	t_pars *command3 = ft_calloc(sizeof(t_pars), 1);
	t_pars *command4 = ft_calloc(sizeof(t_pars), 1);

	// Set the necessary fields for each command
	command1->isCommand = true;
	command1->cmd = malloc(sizeof(t_command));
	command1->cmd->command_path = "/bin/ls";
	command1->cmd->name_options_args = malloc(sizeof(char*) * 2);
	command1->cmd->name_options_args[0] = "ls";
	command1->cmd->name_options_args[1] = NULL;
	command1->prev = NULL;
	command1->next = command2;

	command2->isCommand = true;
	command2->cmd = malloc(sizeof(t_command));
	command2->cmd->command_path = "/usr/bin/grep";
	command2->cmd->name_options_args = malloc(sizeof(char*) * 3);
	command2->cmd->name_options_args[0] = "grep";
	command2->cmd->name_options_args[1] = "a";
	command2->cmd->name_options_args[2] = NULL;
	command2->prev = command1;
	command2->next = command3;//

	command3->isCommand = true;
	command3->cmd = malloc(sizeof(t_command));
	command3->cmd->command_path = "/bin/rev";
	command3->cmd->name_options_args = malloc(sizeof(char*) * 2);
	command3->cmd->name_options_args[0] = "rev";
	command3->cmd->name_options_args[1] = NULL;
	command3->prev = command2;
	command3->next = command4;//

	command4->isCommand = true;
	command4->cmd = malloc(sizeof(t_command));
	command4->cmd->command_path = "/bin/rev";
	command4->cmd->name_options_args = malloc(sizeof(char*) * 3);
	command4->cmd->name_options_args[0] = "rev";
	command4->cmd->name_options_args[1] = NULL;
	command4->prev = command3;
	command4->next = NULL;

	int i = 0;
	t_pars *lst = command1;
	t_pars *temp = lst;
	while (lst->next)
	{
		if (lst->next->isPipe == true)
			i++;
		lst = lst->next;
	}
	lst = temp;

	pipes(command1, -1);

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
	// free(command4->cmd->name_options_args);
	// free(command4->cmd);
	// free(command4);
	return 0;
}
