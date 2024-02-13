/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glambrig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 12:56:20 by glambrig          #+#    #+#             */
/*   Updated: 2024/02/13 15:46:13 by glambrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
	Handles '<<' operator.
	lst->next is the '<<' op., and lst->next->next is the file to redirect from.
*/
int	redirect_input_delimitor(t_pars *lst)
{
	int		open_fd;
	pid_t	ch_pid;
	char	*rl_buff;

	//check_masterkill(lst); UNCOMMENT
	if (access("/tmp/a0987654321aaa.tmp", F_OK) == 0)
		unlink("/tmp/a0987654321aaa.tmp");
	open_fd = open("/tmp/a0987654321aaa.tmp", O_RDWR | O_CREAT, S_IWUSR | S_IRUSR);
	ch_pid = fork();
	if (ch_pid == -1)
		return (perror("fork"), exit(EXIT_FAILURE), 1);
	if (ch_pid == 0)
	{
		signal(SIGINT, (sighandler_t)SIGINT);
		rl_buff = ft_strdup("");
		while (ft_strncmp(rl_buff, lst->next->next->here_doc,
				ft_strlen(lst->next->next->here_doc)) != 0)
		{
			free(rl_buff);
			rl_buff = readline("> ");
			if (rl_buff == NULL)
				break ;
			if (ft_strncmp(rl_buff, lst->next->next->here_doc,
					ft_strlen(lst->next->next->here_doc)) != 0)
				ft_putendl_fd(rl_buff, open_fd);
		}
		free(rl_buff);
		close(open_fd);
		lst->next->next->isFile = true;
		lst->next->next->fl->file_exist = true;
		lst->next->next->fl->file_name = "/tmp/a0987654321aaa.tmp";
		lst->next->next->fl->auth_r = true;
		redirect_input(lst);
		close(open_fd);
	}
	wait(NULL);
	close(open_fd);
	unlink("/tmp/a0987654321aaa.tmp");
}

/*
	Handles '<' operator.
	lst->next is the '<' op., and lst->next->next is the file to redirect from.
*/
int	redirect_input(t_pars *lst)
{
	int		open_fd;
	pid_t	ch_pid;
	int		fds[2];

	if (lst->next->next->fl->file_exist == false)
		return (ft_putendl_fd("Error: redirect input: nonexistant file.", 2), 1);
	if (lst->isCommand == false)
		return (ft_putendl_fd("Error: redirect input: redir to file.", 2), 1);
	open_fd = open(lst->next->next->fl->file_name, O_RDONLY, S_IRUSR);
	if (open_fd == -1)
		return (perror("open"), 1);
	dup2(open_fd, STDIN_FILENO);
	if (close(open_fd) == -1)
		return (perror("close"), 1);
	ch_pid = fork();
	if (ch_pid == 0)
		execve(lst->cmd->command_path, lst->cmd->name_options_args, NULL);
	else if (ch_pid < 0)
	{
		perror("fork");
		free_t_pars(&lst);
		exit(EXIT_FAILURE);
	}
	wait(NULL);
}

/*
	Handles '>' and '>>' operators.
	lst->next is the '>'/'>>' operator, and lst->next->next is the file to redirect to.
*/
int	redirect_output(t_pars *lst, t_all *all, int input_fd)
{
	int		i;
	int		fd[2];
	int		open_fd;
	pid_t	ch_pid;

	if (pipe(fd) < 0)
    {
		perror("pipe");
		free_t_pars(&lst);
		exit(EXIT_FAILURE);
	}
	if (input_fd >= 0)
	{
		if (dup2(input_fd, fd[0]) < 0)
		{
			perror("dup2");
			close(fd[0]);
			free_t_pars(&lst);
			exit(EXIT_FAILURE);
		}
		close(fd[0]);
	}
	close(fd[0]);
	ch_pid = fork();
	if (ch_pid == 0)
	{
		if (lst->next == NULL)
			return (ft_putendl_fd("Error, next is null.", 2), 1);
		else if (lst->next->next == NULL)
			return (ft_putendl_fd("Error, next next is null.", 2), 1);
		if (lst->next && lst->next->next && lst->next->next->fl->auth_w == true && lst->next->operator->redir_out == true)
			open_fd = open(lst->next->next->fl->file_name, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
		else if (lst->next && lst->next->next && lst->next->next->fl->auth_w == true && lst->next->operator->redir_out_app == true)
			open_fd = open(lst->next->next->fl->file_name, O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR);
		else
			return (ft_putendl_fd("Error, insufficient permissions.", 2), 1);
		dup2(open_fd, fd[1]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		close(open_fd);
		//close(STDOUT_FILENO);
		if (lst->cmd->isBuiltin == true)
			exec_builtin(lst, all->env_lst);//add env_list to t_pars
		else
			execve(lst->cmd->command_path, lst->cmd->name_options_args, NULL);
	}
	else if (ch_pid < 0)
	{
		perror("fork");
		free_t_pars(&lst);
		exit(EXIT_FAILURE);
	}
	if (input_fd != -1)
		close(input_fd);
	close(fd[1]);
	wait(NULL);
}

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

void	pipes_child_func(t_pars *lst, int input_fd, int **fds, int i)
{
	if (input_fd != -1)
    {
		dup2(input_fd, STDIN_FILENO);
        close(input_fd);
    }
    if (lst->next != NULL && lst->next->next != NULL && lst->next->next->isCommand == true)	//If it's not the last node, we redirect STDOUT
        dup2(fds[i][1], STDOUT_FILENO);
    close(fds[i][0]);	//We close Read end of pipe because we never use it. We only use input_fd/STDIN.
    if (i != 0)	//Closes the Write end of the previous pipe, if it exists
        close(fds[i - 1][1]);
	if (lst->cmd->isBuiltin == true)
		exec_builtin(lst);
	else
    	execve(lst->cmd->command_path, lst->cmd->name_options_args, NULL);
}

/*
	Handles the pipe '|' operator.
	Input_fd is -1 when pipes() called for the first time,
		meaning we don't redirect input this iteration.
*/
int	pipes(t_pars *lst, int input_fd)
{
    int 	i;
	int		len;
    int 	**fds;
    pid_t 	*ch_pid;

	//check_masterkill(lst);
	i = 0;
	fds = create_pipes(lst, &ch_pid);
	len = lstlen(lst); // minus num_of_pipes. lstlen is too long
    while (lst != NULL && lst->isCommand == true)
	{
        ch_pid[i] = fork();
        if (ch_pid[i] == 0)
			pipes_child_func(lst, input_fd, fds, i);
        else if (ch_pid[i] < 0)
			fork_error(fds, &ch_pid);
        close(fds[i][1]);
        if (i != 0)
            close(fds[i - 1][0]);
        input_fd = fds[i++][0];
		if (lst->next && lst->next->isOperator == true && lst->next->operator->pipe == true && lst->next->next)
        	lst = lst->next->next;	//to skip the pipe operator and go to the next cmd
		else
			break ;
    }
    while (len-- >= 0)
        wait(NULL);
	return (close(fds[0][0]), free(ch_pid), free_arr((void **)fds, len), 0);//len can't be passed for free_arr
}
