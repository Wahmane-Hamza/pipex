/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwahmane <hwahmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 12:09:27 by hwahmane          #+#    #+#             */
/*   Updated: 2025/01/03 16:17:05 by hwahmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    int id = fork();
    int id2 = fork();


    if (id == 0)
    {
        printf("child 0\n");
        if (id2 == 0)
            printf("child 01\n");
        else if (id2 > 0)
            printf("child 001\n");
    }
    else
    {
        printf("parent \n");
        if (id2 == 0)
            printf("child 02\n");
        else if (id2 > 0)
            printf("child 002\n");
    }
}
