/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whendrik <whendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 20:24:54 by whendrik          #+#    #+#             */
/*   Updated: 2023/11/21 20:45:45 by whendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

bool	arg_check(int ac, char **av)
{
	int	i;

	i = 0;
	if (ac > 6 || ac < 5)
		return (printf("%s", ERR_1), 0);
	while (i != ac)
	{
		if (ft_strlen(av[i]) == 0 || ft_strlen(av[i]) > 10)
			return (printf("%s", ERR_2), 0);
		if (ft_atoi(av[i]) < 0)
			return (printf("%s", ERR_2), 0);
		i++;
	}
	if (ft_atoi(av[1]) > 200 || ft_atoi(av[1]) < 1 || ft_atoi(av[2]) < 60
		|| ft_atoi(av[3]) < 60 || ft_atoi(av[4]) < 60)
		return (printf("%s", ERR_2), 0);
	if (ac == 6 && ft_atoi(av[ac - 1]) < 1)
		return (printf("%s", ERR_2), 0);
	return (1);
}
