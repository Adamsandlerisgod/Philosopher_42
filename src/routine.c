/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whendrik <whendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 23:01:36 by whendrik          #+#    #+#             */
/*   Updated: 2023/11/09 17:31:19 by whendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

bool	death_check(t_philo *philo)
{
	// printf("death check a\n");
	// printf("philo->isalive = %d \n", philo->is_alive);
	// printf("death check post lock a\n");
	if (philo->hp < get_time())
	{
		pthread_mutex_lock(philo->lock);
		if (*(philo->is_alive) == 0)
		{
		// printf("WHY the fuck am I here \n");
			pthread_mutex_unlock(philo->lock);
			return (0);
		}
		else
			*(philo->is_alive) = 0;
		pthread_mutex_unlock(philo->lock);
		philo->timeof = get_time();
		printf(DIED, (philo->timeof - philo->times.start) / 1000, philo->philo_id);
		return (0);
	}
	
	// printf("death check pre unlock a\n");
	// printf("get_time = %lld : philo hp = %ld\n", get_time(), philo->hp);
	// printf("death check b\n");
	
	// printf("death check c\n");
	return (1);	
}

bool	is_sleeping(t_philo *philo)
{
	if (!(print_msg(SLEEP, philo)))
		return(0);
	if ((get_time() - philo->timeof) < philo->times.sleep)
	{
		if (!(death_check(philo)))
			return (0);
		usleep(50);
	}
	if (!(print_msg(THINK, philo)))
		return (0);
	return (1);
}

bool	is_eating(t_philo *philo)
{
	if (!(print_msg(EAT, philo)))
		return (0);
	philo->hp = philo->timeof + philo->times.die;
	while ((get_time() - philo->timeof) < philo->times.eat)
	{
		// printf("wait for eat\n");
		if (!death_check(philo))
			return (0);
		usleep(50);
	}
	pthread_mutex_lock(philo->mutex_l);
	pthread_mutex_lock(philo->mutex_r);
	*(philo->fork_l) = 0;
	// printf("FORK CHANGE\n");
	*(philo->fork_r) = 1;
	pthread_mutex_unlock(philo->mutex_l);
	pthread_mutex_unlock(philo->mutex_r);
	if (philo->times.max_ml > 0)
	{
		philo->meal += 1;
		if (philo->meal == philo->times.max_ml)
			return (0);
	}
	return (1);

}

bool	take_fork(pthread_mutex_t *mutex, t_philo *philo, int *fork, int nb)
{
	while (death_check(philo))
	{
		pthread_mutex_lock(mutex);
		// printf("fork = %d and nb = %d \n", *fork, nb);	
		if (*fork == nb)
		{
			pthread_mutex_unlock(mutex);
			if (!(print_msg(FORK, philo)))
				return (0);
			return (1);
		}
		pthread_mutex_unlock(mutex);
		usleep(50);
	}
	return (0);
}



void	*routine(void *arg)
{
	t_philo	*philo;

	// printf("HOLA BITCHES\n");
	philo = (t_philo *)arg;
	// printf("WACKA \n");
	philo->hp = philo->times.start + philo->times.die;
	// printf("philo fork_l = %d	: philo fork_r = %d\n", *philo->fork_l, *philo->fork_r);
	// usleep(100);
	// exit(1);
	// printf("philo->hp = %ld\n", philo->hp);
	while(death_check(philo) == 1)
	{
		// printf("post_death check[%d] = philo fork_l = %d	: philo fork_r = %d\n", philo->philo_id, *philo->fork_l, *philo->fork_r);
		// usleep(2000);
		// exit(1);
		if (take_fork(philo->mutex_l, philo, philo->fork_l, 1) == 0)
			break ;
		if (death_check (philo) == 1 && take_fork(philo->mutex_r, philo, philo->fork_r, 0) == 0)
			break ;
		if (death_check (philo) == 1 && !is_eating(philo))
			break ;
		if (death_check (philo) == 1 && !is_sleeping(philo))
			break ;
	}
	return (NULL);
}