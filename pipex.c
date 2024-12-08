/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manorteg <manorteg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 15:22:22 by manorteg          #+#    #+#             */
/*   Updated: 2024/12/08 12:02:23 by manorteg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_path_env(char *envp[])
{
	int	i;

	i = -1;
	while (envp[++i])
		if (strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
	return (NULL);
}

void	free_paths(char **paths)
{
	int	i;

	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
}

char	*check_command_in_paths(char *cmd, char **paths)
{
	int		i;
	char	*temp_path;
	char	*full_path;

	i = 0;
	while (paths[i])
	{
		temp_path = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(temp_path, cmd);
		free(temp_path);
		if (access(full_path, X_OK) == 0)
		{
			free_paths(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	return (NULL);
}

char	*get_command_path(char *cmd, char *envp[])
{
	char	*path_env;
	char	**paths;
	char	*full_path;

	path_env = find_path_env(envp);
	if (path_env == NULL)
		return (NULL);
	paths = ft_split(path_env, ':');
	full_path = check_command_in_paths(cmd, paths);
	if (full_path)
		return (full_path);
	free_paths(paths);
	return (NULL);
}

void	execute_command(char *cmd, char *envp[])
{
	char	**args;
	char	*cmd_path;

	args = ft_split(cmd, ' ');
	cmd_path = get_command_path(args[0], envp);
	if (cmd_path == NULL)
	{
		fprintf(stderr, "bash: %s: command not found\n", args[0]);
		exit(EXIT_FAILURE);
	}
	if (execve(cmd_path, args, envp) == -1)
	{
		fprintf(stderr, "bash: %s: %s\n", args[0], strerror(errno));
		exit(EXIT_FAILURE);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	int		pipe_fd[2];
	pid_t	pid1;
	pid_t	pid2;
	int		infile;
	int		outfile;
	int		status;

	if (argc != 5)
	{
		fprintf(stderr, "Usage: %s infile cmd1 cmd2 outfile\n", argv[0]);
		return (EXIT_FAILURE);
	}
	// Open files
	infile = open(argv[1], O_RDONLY);
	if (infile < 0)
		fprintf(stderr, "bash: %s: %s\n", argv[1], strerror(errno));
	outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile < 0)
		fprintf(stderr, "bash: %s: %s\n", argv[4], strerror(errno));
	// Create pipe
	if (pipe(pipe_fd) == -1)
	{
		fprintf(stderr, "bash: pipe: %s\n", strerror(errno));
		close(infile);
		close(outfile);
		return (EXIT_FAILURE);
	}
	// First child process
	pid1 = fork();
	if (pid1 == -1)
	{
		fprintf(stderr, "bash: fork: %s\n", strerror(errno));
		close(infile);
		close(outfile);
		return (EXIT_FAILURE);
	}
	if (pid1 == 0 && infile >= 0)
	{
		// Child 1 process (cmd1)
		printf("Child 1 process\n");
		dup2(infile, STDIN_FILENO);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[0]);
		close(infile);
		close(outfile);
		execute_command(argv[2], envp);
	}
	// Second child process
	pid2 = fork();
	if (pid2 == -1)
	{
		fprintf(stderr, "bash: fork: %s\n", strerror(errno));
		close(infile);
		close(outfile);
		return (EXIT_FAILURE);
	}
	if (pid2 == 0 && outfile >= 0)
	{
		// Child 2 process (cmd2)
		printf("Child 2 process\n");
		dup2(pipe_fd[0], STDIN_FILENO);
		dup2(outfile, STDOUT_FILENO);
		close(pipe_fd[1]);
		close(infile);
		close(outfile);
		execute_command(argv[3], envp);
	}
	// Parent process
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	close(infile);
	close(outfile);
	waitpid(pid1, &status, 0);
	if (WIFEXITED(status))
		printf("Child 1 exited with status %d\n", WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		printf("Child 1 killed by signal %d\n", WTERMSIG(status));
	waitpid(pid2, &status, 0);
	if (WIFEXITED(status))
		printf("Child 2 exited with status %d\n", WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		printf("Child 2 killed by signal %d\n", WTERMSIG(status));
	return (EXIT_SUCCESS);
}
