/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarino <lemarino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 18:06:23 by lemarino          #+#    #+#             */
/*   Updated: 2025/07/14 15:29:32 by lemarino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**delete_var(char **envp, int *i)
{
	char	**nenv;
	int		j;

	j = 0;
	nenv = ft_calloc(ft_mtrxlen(envp), sizeof(char *));
	while (j < *i)
	{
		nenv[j] = ft_strdup(envp[j]);
		free(envp[j]);
		j++;
	}
	if (j == *i)
	{
		free(envp[j]);
		(*i)++;
	}
	while (envp[*i])
	{
		nenv[j] = ft_strdup(envp[*i]);
		j++;
		free(envp[j]);
		(*i)++;
	}
	return (free(envp), nenv);
}

// Looks for the target Variable in the Environment.
char	**take_aim(char **envp, char *target)
{
	int		i;
	char	*var_name;
	char	**tmp;

	i = 0;
	var_name = NULL;
	while (envp[i])
	{
		var_name = ft_until_chr(envp[i], '=');
		if (!var_name)
			return (ft_putstr_fd(RED"Malloc failure"NO_ALL, 2), envp);
		if (ft_strncmp(var_name, target, ft_strlen(target)) == 0)
		{
			tmp = delete_var(envp, &i);
			if (!tmp)
				return (free(var_name), NULL);
			free(var_name);
			return (tmp);
		}
		i++;
		free(var_name);
	}
	return (envp);
}

int	ft_unset(t_msh *msh, char **cmd)
{
	int		i;
	char	*target;

	i = 1;
	target = NULL;
	while (cmd[i])
	{
		target = ft_strdup(cmd[i]);
		if (!target)
		{
			ft_putstr_fd(RED"Malloc failure"NO_ALL, 2);
			return (1);
		}
		msh->envp2 = take_aim(msh->envp2, target);
		if (!msh->envp2)
		{
			ft_putstr_fd(RED"Malloc failure"NO_ALL, 2);
			return (1);
		}
		i++;
	}
	return (free(target), 0);
}
