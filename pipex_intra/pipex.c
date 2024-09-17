/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marubio- <marubio-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 18:09:52 by marubio-          #+#    #+#             */
/*   Updated: 2024/09/17 12:40:37 by marubio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * The function `run_command` takes a command and an environment variable array,
 * splits the command into individual arguments, checks if the command is a
 * relative or absolute path, gets the path from the environment variable if
 * necessary, and executes the command.
 *
 * @param cmd The `cmd` parameter is a string that represents the command to
 * be executed. It can be a full path to an executable file or a command name
 * that needs to be searched in the directories specified in the `envp`
 * parameter.
 * @param envp The `envp` parameter is an array of strings that represents
 * the environment variables.
 */
void	run_command(char *cmd, char **envp)
{
	char	**cmds;
	char	*path;

	cmds = ft_split(cmd, ' ');
	if (!ft_strncmp(cmds[0], "./", 2) || !ft_strncmp(cmds[0], "../", 3)
		|| cmds[0][0] == '/' || (access(cmd, F_OK) == 0))
		path = cmds[0];
	else
		path = get_path_from_envp(*cmds, envp);
	execve(path, cmds, envp);
	ft_perror(cmds[0]);
}

/**
 * The function `child_process` redirects input and output streams
 * and runs a command with the given arguments and environment variables.
 *
 * @param fd The parameter "fd" is a pointer to an integer array.
 * It is used to pass file descriptors for communication between the
 * parent and child processes. The array should have two elements, where
 * fd[0] represents the file descriptor for reading and fd[1] represents the
 * file descriptor for writing.
 * @param av An array of strings representing the command-line arguments.
 * The first element (av[0]) is
 * typically the name of the program being executed, and the subsequent
 * elements are the arguments passed to the program.
 * @param envp The `envp` parameter is an array of strings that represents
 * the environment variable for the child process.
 */
void	child_process(int *fd, char **av, char **envp)
{
	int	fd_child;

	close(fd[0]);
	fd_child = open(av[1], O_RDONLY, 0644);
	if (fd_child == -1)
		ft_perror(NULL);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	dup2(fd_child, STDIN_FILENO);
	close(fd_child);
	run_command(av[2], envp);
}

/**
 * The function child2_process takes in file descriptors,
 * command line arguments, and environment
 * variables, and redirects the input and output streams before
 * running a command.
 *
 * @param fd The parameter `fd` is an array of file descriptors.
 * It is used for inter-process
 * communication between the parent process and child processes.
 * The array contains two file
 * descriptors: `fd[0]` is used for reading from the parent process,
 * and `fd[1]` is used for writing
 * @param av The `av` parameter is an array of strings that represents
 * the command-line arguments
 * passed to the program. The first element `av[0]` is typically the name
 * of the program itself, and
 * the subsequent elements `av[1]`, `av[2]`, etc. are the arguments
 * @param envp The `envp` parameter is an array of strings that represents
 * the environment variables
 * for the child process.
 */
void	child2_process(int *fd, char **av, char **envp)
{
	int	fd_parent;

	close(fd[1]);
	fd_parent = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_parent == -1)
		ft_perror(NULL);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	dup2(fd_parent, STDOUT_FILENO);
	close(fd_parent);
	run_command(av[3], envp);
}

/**
 * The main function creates two child processes and uses pipes
 * to communicate between them.
 *
 * @param ac The parameter `ac` represents the number of command-line
 * arguments passed to the program.
 * @param av The `av` parameter is an array of strings that represents
 * the command-line arguments
 * passed to the program. The first element `av[0]` is the name of the
 * program itself, and the
 * subsequent elements `av[1]` to `av[ac-1]` are the arguments
 * @param envp The `envp` parameter is an array of strings that represents
 * the environment variables
 * passed to the program.
 *
 * @return The main function is returning 0.
 */
int	main(int ac, char **av, char **envp)
{
	int		pipefd[2];
	pid_t	child1;
	pid_t	child2;

	if (ac != 5)
		return (ft_putstr_fd("Error: Wrong number of arguments\n", 2), 0);
	if (pipe(pipefd) == -1)
		ft_perror("error");
	child1 = fork();
	if (child1 < 0)
		ft_perror("Fork: ");
	if (child1 == 0)
		child_process(pipefd, av, envp);
	child2 = fork();
	if (child2 < 0)
		ft_perror("Fork: ");
	if (child2 == 0)
		child2_process(pipefd, av, envp);
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(child1, NULL, 0);
	waitpid(child2, NULL, 0);
	return (0);
}
