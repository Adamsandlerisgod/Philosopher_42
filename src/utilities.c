/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whendrik <whendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 17:44:28 by whendrik          #+#    #+#             */
/*   Updated: 2023/11/09 17:32:28 by whendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

void	free_all(t_var *var, int size)
{
	int	i;

	i = 0;
	free(var->philo);
	free(var->thd);
	free(var->fork);
	while (i < size)
		pthread_mutex_destroy(&var->mutex[i++]);
	free(var->mutex);
	pthread_mutex_destroy(var->lock);
	free(var->lock);
}

int	print_msg(char *string, t_philo *philo)
{
	pthread_mutex_lock(philo->lock);
	if (*philo->is_alive == 1)
	{
		philo->timeof = get_time();
		printf(string,
			(philo->timeof - philo->times.start) / 1000, philo->philo_id);
		pthread_mutex_unlock(philo->lock);
		return (1);
	}
	pthread_mutex_unlock(philo->lock);
	return (0);
}

int	ft_atoi(const char *str)
{
	int	res;
	int	i;
	int	sign;

	res = 0;
	i = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] <= '9' && str[i] >= '0')
	{
		res = (res * 10) + (str[i] - '0');
		i++;
	}
	return (res * sign);
}
