/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yim <yim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 15:19:34 by gsmets            #+#    #+#             */
/*   Updated: 2023/03/13 15:53:30 by yim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eats(t_philo *philo, t_arg *arg)
{
	pthread_mutex_lock(&(arg->forks[philo->left]));
	action_print(arg, philo->id, "has taken a fork", 0);
	pthread_mutex_lock(&(arg->forks[philo->right]));
	action_print(arg, philo->id, "has taken a fork", 0);
	pthread_mutex_lock(&(arg->moniter));
	action_print(arg, philo->id, "is eating", 0);
	philo->last_eat_time = timestamp();
	(philo->eat_count)++;
	pthread_mutex_unlock(&(arg->moniter));
	smart_sleep(arg->time_to_eat, arg);
	pthread_mutex_unlock(&(arg->forks[philo->left]));
	pthread_mutex_unlock(&(arg->forks[philo->right]));
}

void	*p_thread(void *void_philoopher)
{
	t_philo	*philo;
	t_arg	*arg;

	philo = (t_philo *)void_philoopher;
	arg = philo->arg;
	if (philo->id % 2)
		usleep(arg->time_to_eat / 2);
	while (1)
	{
		philo_eats(philo, arg);
		pthread_mutex_lock(&(arg->print));
		if (philo->eat_count == arg->must_eat_count || arg->dieded)
		{
			arg->finish_eat++;
			pthread_mutex_unlock(&(arg->print));
			break ;
		}
		pthread_mutex_unlock(&(arg->print));
		action_print(arg, philo->id, "is sleeping", 0);
		smart_sleep(arg->time_to_sleep, arg);
		action_print(arg, philo->id, "is thinking", 0);
	}
	return (NULL);
}

void	exit_launcher(t_arg *arg, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < arg->ph_num)
		pthread_mutex_destroy(&(arg->forks[i]));
	pthread_mutex_destroy(&(arg->print));
	pthread_mutex_destroy(&(arg->moniter));
	free(philo);
}

void	monitering(t_arg *arg, t_philo *p)
{
	int	i;

	while (1)
	{
		i = -1;
		while (++i < arg->ph_num && !(arg->dieded))
		{
			pthread_mutex_lock(&(arg->moniter));
			if (timestamp() - p[i].last_eat_time > arg->time_to_die)
				action_print(arg, i, "died", 1);
			if (arg->ph_num == 1 && arg->dieded)
				pthread_mutex_unlock(&(arg->forks[0]));
			pthread_mutex_unlock(&(arg->moniter));
			usleep(100);
		}
		pthread_mutex_lock(&(arg->print));
		if (arg->dieded || (arg->must_eat_count != -1 \
			&& arg->finish_eat >= arg->ph_num))
		{
			pthread_mutex_unlock(&(arg->print));
			break ;
		}
		pthread_mutex_unlock(&(arg->print));
	}
}

int	philosophers(t_arg *arg, t_philo *philo)
{
	int				i;

	i = 0;
	arg->start_time = timestamp();
	while (i < arg->ph_num)
	{
		if (pthread_create(&(philo[i].thread), NULL, p_thread, &(philo[i])))
			return (1);
		i++;
	}
	monitering(arg, philo);
	i = -1;
	while (++i < arg->ph_num)
		pthread_join(philo[i].thread, NULL);
	return (0);
}
