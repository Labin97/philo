/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yim <yim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 17:20:40 by gsmets            #+#    #+#             */
/*   Updated: 2023/03/09 13:41:09 by yim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_philo	*philo;
	t_arg	arg;

	if (argc != 5 && argc != 6)
		return (print_error("error argc", 1));
	if (init_argv(&arg, argc, argv))
		return (print_error("error argv init", 2));
	if (init_philo(&arg, &philo))
		return (print_error("error philo init", 3));
	if (philosophers(&arg, philo))
		return (print_error("error philosophers", 4));
	exit_launcher(&arg, philo);
	return (0);
}
