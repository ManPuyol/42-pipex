/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manorteg <manorteg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 15:22:22 by manorteg          #+#    #+#             */
/*   Updated: 2025/03/13 22:49:55 by manorteg         ###   ########.fr       */
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

	if (strchr(cmd, '/') != NULL)
	{
		free_paths(paths);
		return (strdup(cmd));
	}

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
	if (path_env == NULL || !cmd)
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
		exit(errno);
	}
	free(cmd_path);
}

