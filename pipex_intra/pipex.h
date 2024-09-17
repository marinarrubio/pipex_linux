/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marubio- <marubio-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 18:10:00 by marubio-          #+#    #+#             */
/*   Updated: 2024/09/17 12:41:24 by marubio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <limits.h>
# include <string.h>

/*utils_pipex*/
void	ft_perror(char *str);
void	ft_which_error(char *str);
int		check_path(char **envp);
char	*get_path_from_envp(char *cmd, char **envp);

/*pipex*/
void	run_command(char *cmd, char **envp);
void	child_process(int *fd, char **av, char **envp);
void	child2_process(int *fd, char **av, char **envp);
int		main(int ac, char **av, char **envp);

/*lib*/
char	**ft_split(const char *s, char c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_putstr_fd(const char *s, int fd);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *str);

#endif