/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whendrik <whendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 17:33:19 by whendrik          #+#    #+#             */
/*   Updated: 2023/11/09 15:25:09 by whendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define FORK "\033[1;33m[%ld ms] philo %d is holding a fork\033[0m\n"
# define EAT "\033[1;32m[%ld ms] philo %d is eating\033[0m\n"
# define SLEEP "\033[1;34m[%ld ms] philo %d is sleeping\033[0m\n"
# define THINK "\033[1;38;5;208m[%ld ms] philo %d is thinking\033[0m\n"
# define DIED "\033[1;31m[%ld ms] philo %d is dead\033[0m\n"

typedef struct s_times
{
	long int	start;
	long int	die;
	long int	eat;
	long int	sleep;
	long int	max_ml;
}		t_times;

typedef struct s_philo
{
	int				philo_id;
	int				meal;
	long int		hp;
	long int		timeof;
	pthread_mutex_t	*lock;
	pthread_mutex_t	*mutex_l;
	pthread_mutex_t	*mutex_r;
	int				*fork_l;
	int				*fork_r;
	t_times			times;
	int				*is_alive;
}	t_philo;

typedef struct s_var
{
	int				*fork;
	int				is_alive;
	t_philo			*philo;
	pthread_t		*thd;
	pthread_mutex_t	*lock;
	pthread_mutex_t	*mutex;
}	t_var;

/*Initializers & Malloc*/
bool	init_time(char **av, int ac, t_times *time);
bool	init_forks(int size, t_var *var);
bool	init_philosopher(int size, t_var *var, t_times time);
bool	mallocer(int size, t_var *var);

/*Routine*/
void	*routine(void *arg);

/*utils*/
long long	get_time(void);
int	ft_atoi(const char *str);
int	print_msg(char *string, t_philo *philo);
void	free_all(t_var *var, int size);




#endif