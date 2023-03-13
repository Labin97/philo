/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yim <yim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 18:47:47 by gsmets            #+#    #+#             */
/*   Updated: 2023/03/13 15:21:10 by yim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutex_argv(t_arg *arg)
{
	int	i;

	if (pthread_mutex_init(&(arg->print), NULL))
		return (1);
	if (pthread_mutex_init(&(arg->moniter), NULL))
		return (1);
	arg->forks = malloc(sizeof(pthread_mutex_t) * arg->ph_num);
	if (arg->forks == NULL)
		return (1);
	i = 0;
	while (i < arg->ph_num)
	{
		if (pthread_mutex_init(&(arg->forks[i]), NULL))
			return (1);
		i++;
	}
	return (0);
}

int	init_argv(t_arg *arg, int argc, char *argv[])
{
	memset(arg, 0, sizeof(t_arg));
	arg->ph_num = ft_atoi(argv[1]);
	arg->time_to_die = (unsigned long long)ft_atoi(argv[2]);
	arg->time_to_eat = (unsigned long long)ft_atoi(argv[3]);
	arg->time_to_sleep = (unsigned long long)ft_atoi(argv[4]);
	arg->start_time = 0;
	if (arg->ph_num <= 0 || arg->time_to_die < 0 || \
		arg->time_to_eat < 0 || arg->time_to_sleep < 0)
		return (1);
	if (argc == 6)
	{
		arg->must_eat_count = ft_atoi(argv[5]);
		if (arg->must_eat_count <= 0)
			return (1);
	}
	else
		arg->must_eat_count = -1;
	if (init_mutex_argv(arg))
		return (1);
	return (0);
}

int	init_philo(t_arg *arg, t_philo **philo)
{
	int	i;

	i = 0;
	*philo = malloc(sizeof(t_philo) * arg->ph_num);
	if (*philo == NULL)
		return (1);
	while (i < arg->ph_num)
	{
		(*philo)[i].id = i;
		(*philo)[i].left = i;
		(*philo)[i].right = (i + 1) % arg->ph_num;
		(*philo)[i].eat_count = 0;
		(*philo)[i].last_eat_time = timestamp();
		(*philo)[i].arg = arg;
		i++;
	}
	return (0);
}
