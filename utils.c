/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yim <yim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 18:59:07 by gsmets            #+#    #+#             */
/*   Updated: 2023/03/13 15:24:11 by yim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	long int	n;
	int			sign;

	n = 0;
	sign = 1;
	while ((*str <= 13 && *str >= 9) || *str == 32)
		str++;
	if (*str == '-')
		return (-1);
	else if (*str == '+')
		str++;
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
			n = n * 10 + (*str++ - '0');
		else
			return (-1);
	}
	return ((int)(n * sign));
}

long long	timestamp(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

long long	time_diff(long long past, long long pres)
{
	return (pres - past);
}

void	smart_sleep(long long time, t_arg *arg)
{
	long long	i;

	i = timestamp();
	while (1)
	{
		pthread_mutex_lock(&(arg->print));
		if (arg->dieded)
		{
			pthread_mutex_unlock(&(arg->print));
			break ;
		}
		pthread_mutex_unlock(&(arg->print));
		if (time_diff(i, timestamp()) >= time)
			break ;
		usleep(50);
	}
}

void	action_print(t_arg *arg, int id, char *string, int flag)
{
	pthread_mutex_lock(&(arg->print));
	if (!(arg->dieded))
	{
		printf("%lli ", timestamp() - arg->start_time);
		printf("%i ", id + 1);
		printf("%s\n", string);
	}
	if (flag)
		arg->dieded = 1;
	pthread_mutex_unlock(&(arg->print));
	return ;
}
