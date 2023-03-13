/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yim <yim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 18:30:58 by gsmets            #+#    #+#             */
/*   Updated: 2023/03/09 15:24:41 by yim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>

typedef struct s_arg
{
	int					ph_num;
	int					must_eat_count;
	int					dieded;
	int					finish_eat;
	u_int64_t			time_to_die;
	u_int64_t			time_to_eat;
	u_int64_t			time_to_sleep;
	u_int64_t			start_time;
	pthread_mutex_t		moniter;
	pthread_mutex_t		*forks;
	pthread_mutex_t		print;
}	t_arg;

typedef struct s_philo
{
	int					id;
	int					left;
	int					right;
	int					eat_count;
	u_int64_t			last_eat_time;
	t_arg				*arg;	
	pthread_t			thread;
}	t_philo;

//error
int			print_error(char *str, int errno);
int			error_manager(int error);

//init
int			init_philo(t_arg *arg, t_philo **philo);
int			init_argv(t_arg *arg, int argc, char *argv[]);

//utils
int			ft_atoi(const char *str);
void		action_print(t_arg *arg, int id, char *string, int flag);
long long	timestamp(void);
long long	time_diff(long long past, long long pres);
void		smart_sleep(long long time, t_arg *arg);

//launcher
int			philosophers(t_arg *arg, t_philo *philo);
void		exit_launcher(t_arg *arg, t_philo *philo);
#endif
