/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 10:19:26 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/11 11:39:52 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include "../tests.hpp"

int main(int argc, char const *argv[])
{
    (void)argc;
    (void)argv;

    CU_initialize_registry();

    run_utils_tests();
    run_map_checks();

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return 0;
}
