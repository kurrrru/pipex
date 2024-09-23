/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:49:19 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/09/23 15:54:08 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utils.h"

void	open_files(int *fdedge, char *file1, char *file2)
{
	fdedge[0] = open(file1, O_RDONLY);
	if (fdedge[0] == -1)
	{
		write(2, "bash: ", 6);
		perror(file1);
	}
	fdedge[1] = open(file2, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fdedge[1] == -1)
	{
		write(2, "bash: ", 6);
		perror(file2);
	}
}

void	first_child(int *fdedge, int *fdpipe, char *argv, char **envp)
{
	close_wrap(fdedge[1]);
	close_wrap(fdpipe[0]);
	if (fdedge[0] == -1)
	{
		close_wrap(fdpipe[1]);
		exit(1);
	}
	dup2(fdedge[0], STDIN_FILENO);
	dup2(fdpipe[1], STDOUT_FILENO);
	close_wrap(fdedge[0]);
	close_wrap(fdpipe[1]);
	execute(argv, envp);
	exit(EXIT_FAILURE);
}

void	second_child(int *fdedge, int *fdpipe, char *argv, char **envp)
{
	close_wrap(fdedge[0]);
	close_wrap(fdpipe[1]);
	if (fdedge[1] == -1)
	{
		close_wrap(fdpipe[0]);
		exit(1);
	}
	dup2(fdpipe[0], STDIN_FILENO);
	dup2(fdedge[1], STDOUT_FILENO);
	close_wrap(fdedge[1]);
	close_wrap(fdpipe[0]);
	execute(argv, envp);
	exit(EXIT_FAILURE);
}

void	parent_process(int *fdpipe, int *fdedge, int *pid)
{
	int	status[2];

	close_wrap(fdpipe[0]);
	close_wrap(fdpipe[1]);
	close_wrap(fdedge[0]);
	close_wrap(fdedge[1]);
	if (waitpid(pid[0], &status[0], 0) == -1)
		perror("waitpid");
	if (waitpid(pid[1], &status[1], 0) == -1)
		perror("waitpid");
}

int	main(int argc, char **argv, char **envp)
{
	int		fdedge[2];
	int		fdpipe[2];
	int		pid[2];

	if (argc != 5)
		return (write(2, "Usage: ./pipex file1 cmd1 cmd2 file2\n", 37), 1);
	open_files(fdedge, argv[1], argv[4]);
	if (pipe(fdpipe) == -1)
		return (perror("pipe"), 1);
	pid[0] = fork();
	if (pid[0] == -1)
		perror("fork");
	else if (pid[0] == 0)
		first_child(fdedge, fdpipe, argv[2], envp);
	else
	{
		pid[1] = fork();
		if (pid[1] == -1)
			perror("fork");
		else if (pid[1] == 0)
			second_child(fdedge, fdpipe, argv[3], envp);
		else
			parent_process(fdpipe, fdedge, pid);
	}
	return (0);
}
