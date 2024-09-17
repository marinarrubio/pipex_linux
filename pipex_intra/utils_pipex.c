/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marubio- <marubio-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 12:46:08 by marubio-          #+#    #+#             */
/*   Updated: 2023/10/20 12:14:33 by marubio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * The function ft_perror prints an error message to stderr and exits 
 * the program.
 * 
 * @param str The parameter "str" is a pointer to a character array, which is
 * typically used to store a string.
 */
void	ft_perror(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

/**
 * The function ft_which_error prints a given string to the standard error 
 * output and exits the program with a failure status.
 * 
 * @param str The parameter "str" is a pointer to a character array, 
 * which represents the error message that will be printed to the standard
 * error output.
 */
void	ft_which_error(char *str)
{
	ft_putstr_fd(str, 2);
	exit(EXIT_FAILURE);
}

/**
 * The function "check_path" checks if the "PATH" variable is defined 
 * in the environment and returns its index if found, otherwise it displays 
 * an error message and exits the program.
 * 
 * @param envp The parameter `envp` is a pointer to an array of strings, 
 * where each string represents
 * an environment variable. In this case, the function is searching for the 
 * environment variable `PATH` within this array.
 * 
 * @return the index of the "PATH=" string in the envp array.
 */
int	check_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (i);
		i++;
	}
	ft_which_error("There is no PATH defined in the enviroment\n");
	exit (127);
	return (i);
}

/**
 * The function `get_path_from_envp` takes a command and an environment 
 * variable array and returns the
 * full path of the command if it exists in one of the directories
 *  specified in the environment variable.
 * 
 * @param cmd A string representing the command that we want to find the 
 * path for.
 * @param envp An array of strings representing the environment variables.
 * 
 * @return a pointer to a character array (char *) that represents the 
 * path to the executable file
 * specified by the "cmd" parameter. If the file is found in one of the 
 * directories specified in the
 * "envp" parameter, the function returns the path to that file. If the 
 * file is not found, the function returns 0.
 */
char	*get_path_from_envp(char *cmd, char **envp)
{
	int		i;
	char	**path;
	char	*create_path;
	char	*path_cmd;

	i = check_path(envp);
	if (!envp || !*envp)
		ft_perror(NULL);
	path = ft_split(envp[i] + 5, ':');
	if (!path || !*path)
		ft_perror(NULL);
	i = 0;
	while (path[i])
	{
		create_path = ft_strjoin(path[i], "/");
		path_cmd = ft_strjoin(create_path, cmd);
		free(create_path);
		if (access(path_cmd, F_OK & R_OK) == 0)
			return (path_cmd);
		free(path_cmd);
		i++;
	}
	return (0);
}
