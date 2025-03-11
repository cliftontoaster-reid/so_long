/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 11:27:24 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/11 12:30:34 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <CUnit/Basic.h>

extern "C"
{
#include "map.h"
#include "data.h"
}

void test_map_from_str(void)
{
    t_map *map;
    char *str;

    str = (char *)"111\n1P1\n111\n";
    map = map_from_str(str);
    CU_ASSERT_PTR_NOT_NULL_FATAL(map);
    CU_ASSERT_EQUAL(map->size.x, 3);
    CU_ASSERT_EQUAL(map->size.y, 3);
    CU_ASSERT_STRING_EQUAL(map->map[0], (char *)"111");
    CU_ASSERT_STRING_EQUAL(map->map[1], (char *)"1P1");
    CU_ASSERT_STRING_EQUAL(map->map[2], (char *)"111");
    map_free(map);
}

void test_map_find_player(void)
{
    t_map *map;
    char *str;
    t_2d player;

    str = (char *)"111\n1P1\n111\n";
    map = map_from_str(str);
    player = map_find_player(map);
    CU_ASSERT_EQUAL(player.x, 1);
    CU_ASSERT_EQUAL(player.y, 1);
    map_free(map);
}

void test_map_find_exit(void)
{
    t_map *map;
    char *str;
    t_2d exit;

    str = (char *)"111\n1E1\n111\n";
    map = map_from_str(str);
    exit = map_find_exit(map);
    CU_ASSERT_EQUAL(exit.x, 1);
    CU_ASSERT_EQUAL(exit.y, 1);
    map_free(map);
}

void test_map_find_collectibles(void)
{
    t_map *map;
    char *str;
    t_list *collectibles;
    t_2d *collectible;

    str = (char *)"1111\n1CC1\n1111\n";

    map = map_from_str(str);

    collectibles = map_find_collectibles(map);

    collectible = (t_2d *)collectibles->content;

    CU_ASSERT_EQUAL(collectible->x, 1);
    CU_ASSERT_EQUAL(collectible->y, 1);

    collectible = (t_2d *)collectibles->next->content;

    CU_ASSERT_EQUAL(collectible->x, 2);
    CU_ASSERT_EQUAL(collectible->y, 1);

    map_free(map);
    ft_lstclear(&collectibles, free);
}

void test_map_is_size_valid(void)
{
    char *str;

    str = (char *)"111\n1P1\n111\n";
    CU_ASSERT_TRUE(map_is_size_valid(str));
    str = (char *)"111\n1P\n111\n";
    CU_ASSERT_FALSE(map_is_size_valid(str));
    str = (char *)"111\n1P1\n11\n";
    CU_ASSERT_FALSE(map_is_size_valid(str));
}

void test_map_is_char_valid(void)
{
    t_map map;
    char *str;

    str = (char *)"111\n1P1\n111\n";
    map.map = ft_split(str, '\n');
    map.size.x = 3;
    map.size.y = 3;

    CU_ASSERT_TRUE(map_is_char_valid(&map));
    str = (char *)"111\n1P1\n1X1\n";
    map.map = ft_split(str, '\n');

    CU_ASSERT_FALSE(map_is_char_valid(&map));
    str = (char *)"111\n1P1\n1X1\n";
    map.map = ft_split(str, '\n');
    map.size.x = 3;
    map.size.y = 2;

    CU_ASSERT_TRUE(map_is_char_valid(&map));
}

void test_map_is_closed(void)
{
    t_map map;
    char *str;

    str = (char *)"111\n1P1\n111\n";
    map.map = ft_split(str, '\n');
    map.size.x = 3;
    map.size.y = 3;

    CU_ASSERT_TRUE(map_is_closed(&map));
    str = (char *)"111\n1P \n111\n";
    map.map = ft_split(str, '\n');

    CU_ASSERT_FALSE(map_is_closed(&map));
    str = (char *)"111\n11P\n111\n";
    map.map = ft_split(str, '\n');
    map.size.x = 3;
    map.size.y = 2;

    CU_ASSERT_FALSE(map_is_closed(&map));
}

void test_map_is_player(void)
{
    t_map map;
    char *str;

    str = (char *)"111\n1P1\n111\n";
    map.map = ft_split(str, '\n');
    map.size.x = 3;
    map.size.y = 3;

    CU_ASSERT_EQUAL(map_is_player(&map), ZERO);

    str = (char *)"111\n1 1\n111\n";
    map.map = ft_split(str, '\n');
    CU_ASSERT_EQUAL(map_is_player(&map), ZONE);
}

void test_map_is_collectible(void)
{
    t_map map;
    char *str;

    str = (char *)"111\n1C1\n111\n";
    map.map = ft_split(str, '\n');
    map.size.x = 3;
    map.size.y = 3;

    CU_ASSERT_TRUE(map_is_collectible(&map));

    str = (char *)"111\n1 1\n111\n";
    map.map = ft_split(str, '\n');
    CU_ASSERT_FALSE(map_is_collectible(&map));
}

void test_map_is_exit(void)
{
    t_map map;
    char *str;

    str = (char *)"111\n1E1\n111\n";
    map.map = ft_split(str, '\n');
    map.size.x = 3;
    map.size.y = 3;

    CU_ASSERT_EQUAL(map_is_exit(&map), ZERO);

    str = (char *)"111\n1 1\n111\n";
    map.map = ft_split(str, '\n');
    CU_ASSERT_EQUAL(map_is_exit(&map), ZONE);
}

void test_map_is_valid(void)
{
    t_map *map;
    char *str;

    str = (char *)"1111111111111\n10010000000C1\n1000011111001\n1P0011E000001\n1111111111111";
    map = map_from_str(str);

    CU_ASSERT_TRUE(map_is_valid(map));

    str = (char *)"1111111111111111111111111111111111\n10P000C00000000C000000000000000001\n1000000000000000000000000000000001\n10000C00011111111111100000C0000001\n1000000001E000C0000100000000000001\n1000000001000000000100000000000001\n10000C0001000C00000100000000000001\n1000000001111111111100000000000001\n100000000000000000000000C000000001\n10000C00000000000000000000000C0001\n1111111111111111111111111111111111";
    map = map_from_str(str);

    CU_ASSERT_FALSE(map_is_valid(map));
}

void test_find_neibours(void)
{
    t_map map;
    char *str;
    t_list *to_visit;
    t_list *visited;
    t_list *accessible;

    str = (char *)"111\n1P1\n111\n";
    map.map = ft_split(str, '\n');
    map.size.x = 3;
    map.size.y = 3;

    t_2d pos = {1, 1};

    to_visit = ft_lstnew(t2dclone(pos));
    visited = NULL;
    accessible = NULL;

    find_neibours(&map, &to_visit, &visited, &accessible);

    CU_ASSERT_PTR_NOT_NULL(to_visit);
    CU_ASSERT_PTR_NULL(visited);
    CU_ASSERT_PTR_NOT_NULL(accessible);

    ft_lstclear(&to_visit, free);
    ft_lstclear(&visited, free);
    ft_lstclear(&accessible, free);
}

void test_map_wallvar(void)
{
    t_map map;
    char *str;
    int wallvar;

    str = (char *)"111\n1P1\n111\n";
    map.map = ft_split(str, '\n');
    map.size.x = 3;
    map.size.y = 3;

    t_2d pos = {1, 1};

    wallvar = map_wallvar(&map, pos);

    CU_ASSERT_EQUAL(wallvar, 0);

    str = (char *)"111\n111\n111\n";
    map.map = ft_split(str, '\n');

    wallvar = map_wallvar(&map, pos);

    CU_ASSERT_EQUAL(wallvar, 0x1 | 0x2 | 0x4 | 0x8);

    str = (char *)"101\n111\n101\n";
    map.map = ft_split(str, '\n');

    wallvar = map_wallvar(&map, pos);

    CU_ASSERT_EQUAL(wallvar, 0x2 | 0x4);
}

void test_map_walllst(void)
{
    t_map map;
    char *str;
    int **walllst;

    str = (char *)"111\n1P1\n111\n";
    map.map = ft_split(str, '\n');
    map.size.x = 3;
    map.size.y = 3;

    walllst = map_walllst(&map);

    CU_ASSERT_EQUAL(walllst[0][0], 0x4 | 0x8);
    CU_ASSERT_EQUAL(walllst[0][1], 0x2 | 0x4);
    CU_ASSERT_EQUAL(walllst[0][2], 0x2 | 0x8);
    CU_ASSERT_EQUAL(walllst[1][0], 0x1 | 0x8);
    CU_ASSERT_EQUAL(walllst[1][1], 0);
    CU_ASSERT_EQUAL(walllst[1][2], 0x1 | 0x8);
    CU_ASSERT_EQUAL(walllst[2][0], 0x1 | 0x4);
    CU_ASSERT_EQUAL(walllst[2][1], 0x2 | 0x4);
    CU_ASSERT_EQUAL(walllst[2][2], 0x1 | 0x2);
}

void run_map_checks(void)
{
    CU_pSuite suite;

    suite = CU_add_suite("Map", NULL, NULL);
    CU_ADD_TEST(suite, test_map_from_str);
    CU_ADD_TEST(suite, test_map_find_player);
    CU_ADD_TEST(suite, test_map_find_exit);
    CU_ADD_TEST(suite, test_map_find_collectibles);
    CU_ADD_TEST(suite, test_map_is_size_valid);
    CU_ADD_TEST(suite, test_map_is_char_valid);
    CU_ADD_TEST(suite, test_map_is_closed);
    CU_ADD_TEST(suite, test_map_is_player);
    CU_ADD_TEST(suite, test_map_is_collectible);
    CU_ADD_TEST(suite, test_map_is_exit);
    CU_ADD_TEST(suite, test_map_is_valid);
    CU_ADD_TEST(suite, test_find_neibours);
    CU_ADD_TEST(suite, test_map_wallvar);
    CU_ADD_TEST(suite, test_map_walllst);
}