/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_print.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarino <lemarino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 18:04:54 by lemarino          #+#    #+#             */
/*   Updated: 2025/07/14 16:23:56 by lemarino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	str_swap(char **s1, char **s2)
{
	char	*tmp;

	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}

// Returns a copy of ENVP sorted according to ASCII.
char	**ft_sortenvp(char	**envp)
{
	char	**sorted_envp;
	size_t	i;
	size_t	j;
	size_t	l;

	i = 0;
	j = 0;
	l = ft_mtrxlen(envp);
	sorted_envp = ft_envp_dup(envp);
	if (!sorted_envp)
		return (NULL);
	while (j++ < l)
	{
		while (sorted_envp[i + 1])
		{
			if (ft_strcmp(sorted_envp[i], sorted_envp[i + 1]) > 0)
				str_swap(&sorted_envp[i], &sorted_envp[i + 1]);
			i++;
		}
		i = 0;
	}
	return (sorted_envp);
}

// Prints Environment Vars in ASCII order with their value in double quotes.
void	print_declarex(char **envp2)
{
	int		i;
	char	*tmp;
	char	**sorted_envp;

	i = -1;
	sorted_envp = ft_sortenvp(envp2);
	if (!sorted_envp)
		return ;
	while (sorted_envp[++i])
	{
		ft_printf("declare -x ");
		tmp = ft_until_chr(sorted_envp[i], '=');
		if (!tmp)
			return ;
		ft_printf("%s", tmp);
		free(tmp);
		if (ft_strchr(sorted_envp[i], '='))
		{
			ft_printf("\"");
			ft_printf("%s", ft_strchr2(sorted_envp[i], '='));
			ft_printf("\"");
		}
		ft_printf("\n");
	}
	free_dpc(sorted_envp);
}
