/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:49:19 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/10/08 13:12:45 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static void	open_files(int *fdedge, char *file1, char *file2);
static void	first_child(int *fdedge, int *fdpipe, char *argv, char **envp);
static void	second_child(int *fdedge, int *fdpipe, char *argv, char **envp);
static void	parent_process(int *fdpipe, int *fdedge, int *pid);

int	pipex(char **argv, char **envp)
{
	int		fdedge[2];
	int		fdpipe[2];
	int		pid[2];

	open_files(fdedge, argv[1], argv[4]);
	if (pipe(fdpipe) == FAILURE)
		return (perror("pipe"), EXIT_FAILURE);
	pid[0] = fork();
	if (pid[0] == FAILURE)
		return (perror("fork"), EXIT_FAILURE);
	else if (pid[0] == PID_WHEN_CHILD)
		first_child(fdedge, fdpipe, argv[2], envp);
	else
	{
		pid[1] = fork();
		if (pid[1] == FAILURE)
			return (perror("fork"), EXIT_FAILURE);
		else if (pid[1] == PID_WHEN_CHILD)
			second_child(fdedge, fdpipe, argv[3], envp);
		else
			parent_process(fdpipe, fdedge, pid);
	}
	return (EXIT_SUCCESS);
}

static void	open_files(int *fdedge, char *file1, char *file2)
{
	fdedge[0] = open(file1, O_RDONLY);
	if (fdedge[0] == FAILURE)
	{
		ft_putstr_fd("bash: ", STDERR_FILENO);
		perror(file1);
	}
	fdedge[1] = open(file2, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fdedge[1] == FAILURE)
	{
		ft_putstr_fd("bash: ", STDERR_FILENO);
		perror(file2);
	}
}

static void	first_child(int *fdedge, int *fdpipe, char *argv, char **envp)
{
	close_wrap(fdedge[1]);
	close_wrap(fdpipe[0]);
	if (fdedge[0] == FAILURE)
	{
		close_wrap(fdpipe[1]);
		exit(EXIT_FAILURE);
	}
	dup2_wrap(fdedge[0], STDIN_FILENO);
	dup2_wrap(fdpipe[1], STDOUT_FILENO);
	close_wrap(fdedge[0]);
	close_wrap(fdpipe[1]);
	execute(argv, envp);
	exit(EXIT_FAILURE);
}

static void	second_child(int *fdedge, int *fdpipe, char *argv, char **envp)
{
	close_wrap(fdedge[0]);
	close_wrap(fdpipe[1]);
	if (fdedge[1] == FAILURE)
	{
		close_wrap(fdpipe[0]);
		exit(EXIT_FAILURE);
	}
	dup2_wrap(fdpipe[0], STDIN_FILENO);
	dup2_wrap(fdedge[1], STDOUT_FILENO);
	close_wrap(fdedge[1]);
	close_wrap(fdpipe[0]);
	execute(argv, envp);
	exit(EXIT_FAILURE);
}

static void	parent_process(int *fdpipe, int *fdedge, int *pid)
{
	int	status[2];

	close_wrap(fdpipe[0]);
	close_wrap(fdpipe[1]);
	close_wrap(fdedge[0]);
	close_wrap(fdedge[1]);
	if (waitpid(pid[0], &status[0], 0) == FAILURE)
		perror("waitpid");
	if (waitpid(pid[1], &status[1], 0) == FAILURE)
		perror("waitpid");
	if (WEXITSTATUS(status[1]) && WEXITSTATUS(status[1]))
		exit(WEXITSTATUS(status[1]));
}
