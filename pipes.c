/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glambrig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 12:56:20 by glambrig          #+#    #+#             */
/*   Updated: 2024/02/09 17:21:39 by glambrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Handles '<<' operator.
	lst->next is the '<<' operator, and lst->next->next is the file to redirect from.
*/
int	redirect_input_delimitor(t_pars *lst)
{
	int		open_fd;
	pid_t	ch_pid;
	char	*rl_buff;

	//check killswitch instead of doing this
	if (!(lst->next) || !(lst->next->next))
		return (1);
	if (access("/tmp/a0987654321aaa.tmp", F_OK) == 0)	//If temp file of that name already exists
		unlink("/tmp/a0987654321aaa.tmp");	//Just delete it lmfao HORRIBLY TERRIBLE AND BAD
	open_fd = open("/tmp/a0987654321aaa.tmp", O_RDWR | O_CREAT);
	rl_buff = ft_strdup("");
	while(ft_strncmp(rl_buff, lst->next->next->DELIM, ft_strlen(lst->next->next->DELIM)) != 0)//rl_buff != lst->next->next->DELIM 
	{
		free(rl_buff);
		rl_buff = readline("> ");
		if (rl_buff == NULL)	//CTRL + D was pressed, execute command with what input we already have
			break ;
		if (ft_strncmp(rl_buff, lst->next->next->DELIM, ft_strlen(lst->next->next->DELIM)) != 0)
			ft_putstr_fd(rl_buff, open_fd);
	}
	free(rl_buff);
	close(open_fd);
	lst->next->next->isFile = true;
	lst->next->next->fl->file_exist = true;
	lst->next->next->fl->file_name = "/tmp/a0987654321aaa.tmp";
	lst->next->next->fl->auth_r = true;
	redirect_input(lst);
	unlink("/tmp/a0987654321aaa.tmp");
}

/*
	Handles '<' operator.
	lst->next is the '<' operator, and lst->next->next is the file to redirect from.
*/
int	redirect_input(t_pars *lst)
{
	int		open_fd;
	pid_t	ch_pid;
	int		fds[2];

	if (lst->next->next->fl->file_exist == false)
		return (ft_putendl_fd("Error: redirect input: nonexistant file.", 2), 1);
	if (lst->isCommand == false)
		return (ft_putendl_fd("Error: redirect input: input redirection to file instead of command.", 2), 1);
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
int	redirect_output(t_pars *lst, int input_fd)
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
			free_t_pars(&lst);
			exit(EXIT_FAILURE);
		}
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
		execve(lst->cmd->command_path, lst->cmd->name_options_args, NULL);
	}
	else if (ch_pid < 0)
	{
		perror("fork");
		free_t_pars(&lst);
		exit(EXIT_FAILURE);
	}
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

/*
	Handles the pipe '|' operator.
*/
void	pipes(t_pars *lst, int input_fd)
{
    int i;
    int **fds;
    pid_t *ch_pid;
    t_pars *temp;

	// Commented for testing, remove once parsing is joined to execution.
	// if (lst->prev->MasterKill == true)
	// {
	// 	free_t_pars(&lst);
	// 	ft_putendl_fd("Pipes: Error: invalid input.", 2);
	// 	return ;
	// }
	i = 0;
	fds = create_pipes(lst, &ch_pid);
	temp = lst;
    while (lst != NULL && lst->isCommand == true)
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
	// t_pars *command4 = ft_calloc(sizeof(t_pars), 1);

	// Set the necessary fields for each command
	command1->isCommand = true;
	command1->cmd = malloc(sizeof(t_command));
	command1->cmd->command_path = "/bin/rev";
	command1->cmd->name_options_args = malloc(sizeof(char*) * 2);
	command1->cmd->name_options_args[0] = "rev";
	command1->cmd->name_options_args[1] = NULL;
	command1->prev = NULL;
	command1->next = command2;

	command2->isCommand = false;
	command2->isDelim = true;
	command2->operator = malloc(sizeof(t_operator));
	command2->operator->redir_in_delim = true;
	command2->cmd = malloc(sizeof(t_command));
	command2->cmd->command_path = NULL;
	command2->cmd->name_options_args = malloc(sizeof(char*) * 1);
	command2->cmd->name_options_args[0] = NULL;
	command2->prev = command1;
	command2->next = command3;//

	command3->isFile = true;
	command3->fl = malloc(sizeof(t_file));
	command3->isDelim = true;
	command3->DELIM = ft_calloc(1, 4);
	command3->DELIM = "EOF";
	command3->cmd = malloc(sizeof(t_command));
	command3->cmd->command_path = NULL;
	command3->cmd->name_options_args = malloc(sizeof(char*) * 2);
	command3->cmd->name_options_args[0] = NULL;
	command3->prev = command2;
	command3->next = NULL;//command4

	// command4->isCommand = true;
	// command4->cmd = malloc(sizeof(t_command));
	// command4->cmd->command_path = "/bin/rev";
	// command4->cmd->name_options_args = malloc(sizeof(char*) * 3);
	// command4->cmd->name_options_args[0] = "rev";
	// command4->cmd->name_options_args[1] = NULL;
	// command4->prev = command3;
	// command4->next = NULL;

	// int i = 0;
	// t_pars *lst = command1;
	// t_pars *temp = lst;
	// while (lst->next)
	// {
	// 	if (lst->next->isPipe == true)
	// 		i++;
	// 	lst = lst->next;
	// }
	// lst = temp;


	//pipes(command1, -1);
	//redirect_output(command1, -1);
	redirect_input_delimitor(command1);

	// Free the allocated memory
	free(command1->cmd->name_options_args);
	free(command1->cmd);
	free(command1);
	free(command2->cmd->name_options_args);
	free(command2->cmd);
	free(command2->operator);
	free(command2);
	free(command3->cmd->name_options_args);
	free(command3->cmd);
	free(command3->fl);
	free(command3);
	// free(command4->cmd->name_options_args);
	// free(command4->cmd);
	// free(command4);
	return 0;
}
