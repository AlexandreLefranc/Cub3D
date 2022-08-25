/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alefranc <alefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 18:13:01 by alefranc          #+#    #+#             */
/*   Updated: 2022/08/25 18:13:09 by alefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_all	*init_all(void)
{
	t_all	*all;

	all = ft_calloc(sizeof(*all), 1);
	if (all == NULL)
		return (NULL);
	return (all);
}
