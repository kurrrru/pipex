/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:49:19 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/09/22 20:55:16 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utils.h"

void	open_files(int *fdegde, char *file1, char *file2)
{
	fdegde[0] = open(file1, O_RDONLY);
	if (fdegde[0] == -1)
	{
		write(2, "bash: ", 6);
		perror(file1);
	}
	fdegde[1] = open(file2, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fdegde[1] == -1)
	{
		write(2, "bash: ", 6);
		perror(file2);
	}
}

void	first_child(int *fdegde, int *fdpipe, char **argv, char **envp)
{
	close(fdpipe[0]);
	dup2(fdegde[0], 0);
	dup2(fdpipe[1], 1);
	close(fdegde[0]);
	close(fdpipe[1]);
	execute(argv[2], envp);
	exit(1);
}

void	second_child(int *fdegde, int *fdpipe, char **argv, char **envp)
{
	close(fdpipe[1]);
	dup2(fdegde[1], 1);
	dup2(fdpipe[0], 0);
	close(fdegde[1]);
	close(fdpipe[0]);
	execute(argv[3], envp);
	exit(1);
}

int	main(int argc, char **argv, char **envp)
{
	int		i;
	int		fdegde[2];
	int		fdpipe[2];
	int		pid;

	if (argc != 5)
	{
		write(2, "Usage: ./pipex file1 cmd1 cmd2 file2\n", 37);
		return (1);
	}
	open_files(fdegde, argv[1], argv[4]);
	if (pipe(fdpipe) == -1)
	{
		perror("pipe");
		return (1);
	}
	i = -1;
	while (++i < 2)
	{
		if (i == 0 && fdegde[0] == -1)
		{
			close(fdpipe[1]);
			continue ;
		}
		if (i == 1 && fdegde[1] == -1)
			continue ;
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
		}
		if (pid == 0)
		{
			if (i == 0)
				first_child(fdegde, fdpipe, argv, envp);
			else
				second_child(fdegde, fdpipe, argv, envp);
		}
		else
		{
			waitpid(pid, NULL, 0);
			if (i == 0)
				close(fdpipe[1]);
			else
				close(fdpipe[0]);
		}
	}
	close(fdegde[0]);
	close(fdegde[1]);
	return (0);
}
