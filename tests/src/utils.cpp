/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 10:35:19 by lfiorell          #+#    #+#             */
/*   Updated: 2025/03/11 11:24:20 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <CUnit/Basic.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // For dup, dup2, and close
#include <CUnit/Basic.h>

extern "C"
{
#include "utils.h"
#include "map.h"
}

void test_fs_exists(void)
{
    CU_ASSERT_TRUE(fs_exists((char *)"/etc/passwd"));
    CU_ASSERT_FALSE(fs_exists((char *)"/etc/gayass"));
}

void test_fs_read_file(void)
{
    char *content = fs_read_file((char *)"/etc/hostname");

    // trim lines at end of content
    for (size_t i = 0; i < strlen(content); i++)
    {
        if (content[i] == '\n')
        {
            content[i] = '\0';
            break;
        }
    }

    char hostname[HOST_NAME_MAX];
    char username[LOGIN_NAME_MAX];

    gethostname(hostname, HOST_NAME_MAX);
    (void)username;

    CU_ASSERT_STRING_EQUAL(content, hostname);
}

void test_ft_strerr(void)
{
    CU_ASSERT_STRING_EQUAL(ft_strerr(MAP_ERROR_NONE), (char *)"Success");
    CU_ASSERT_STRING_EQUAL(ft_strerr(MAP_ERROR_SIZE), ERR_MAP_ERROR_SIZE);
    CU_ASSERT_STRING_EQUAL(ft_strerr(MAP_ERROR_CHAR), ERR_MAP_ERROR_CHAR);
    CU_ASSERT_STRING_EQUAL(ft_strerr(MAP_ERROR_OPEN), ERR_MAP_ERROR_OPEN);
    CU_ASSERT_STRING_EQUAL(ft_strerr(MAP_ERROR_PLAYER_NOT_FOUND), ERR_MAP_ERROR_PLAYER_NOT_FOUND);
    CU_ASSERT_STRING_EQUAL(ft_strerr(MAP_ERROR_PLAYER_MULTIPLE), ERR_MAP_ERROR_PLAYER_MULTIPLE);
    CU_ASSERT_STRING_EQUAL(ft_strerr(MAP_ERROR_COLLECTIBLE_NOT_FOUND), ERR_MAP_ERROR_COLLECTIBLE_NOT_FOUND);
    CU_ASSERT_STRING_EQUAL(ft_strerr(MAP_ERROR_EXIT_NOT_FOUND), ERR_MAP_ERROR_EXIT_NOT_FOUND);
    CU_ASSERT_STRING_EQUAL(ft_strerr(MAP_ERROR_EXIT_MULTIPLE), ERR_MAP_ERROR_EXIT_MULTIPLE);
    CU_ASSERT_STRING_EQUAL(ft_strerr(MAP_ERROR_INVALID_PATH), ERR_MAP_ERROR_INVALID_PATH);
    CU_ASSERT_STRING_EQUAL(ft_strerr(INT_MAX), (char *)"Unknown error");
}

#define BUFFER_SIZE 256

// Helper function to capture output from a given function call
static void capture_output(void (*log_func)(char *, char *, int),
                           const char *msg, const char *file, int line,
                           char *buffer, size_t buf_size)
{
    // Create a temporary file to capture stdout
    FILE *temp_fp = tmpfile();
    CU_ASSERT_PTR_NOT_NULL_FATAL(temp_fp);

    // Save the original stdout file descriptor
    int stdout_fd = dup(fileno(stdout));
    CU_ASSERT(stdout_fd != -1);

    // Redirect stdout to the temporary file
    fflush(stdout);
    if (dup2(fileno(temp_fp), fileno(stdout)) == -1)
    {
        CU_FAIL("Failed to redirect stdout");
        fclose(temp_fp);
        return;
    }

    // Call the logging function
    log_func((char *)msg, (char *)file, line);
    fflush(stdout);

    // Restore original stdout
    dup2(stdout_fd, fileno(stdout));
    close(stdout_fd);

    // Read the captured output into buffer
    fseek(temp_fp, 0, SEEK_SET);
    size_t nread = fread(buffer, 1, buf_size - 1, temp_fp);
    buffer[nread] = '\0';
    fclose(temp_fp);
}

void test_log_warning(void)
{
    char buffer[BUFFER_SIZE] = {0};
    capture_output(log_warning, "Test warning", "testfile.c", 42, buffer, BUFFER_SIZE);

    const char *expected = "\033[33m[WARNING] (testfile.c:42) Test warning\033[0m\n";
    CU_ASSERT_STRING_EQUAL(buffer, expected);
}

void test_log_info(void)
{
    char buffer[BUFFER_SIZE] = {0};
    capture_output(log_info, "Test info", "testfile.c", 42, buffer, BUFFER_SIZE);

    const char *expected = "\033[36m[INFO] (testfile.c:42) Test info\033[0m\n";
    CU_ASSERT_STRING_EQUAL(buffer, expected);
}

void test_log_debug(void)
{
    char buffer[BUFFER_SIZE] = {0};
    capture_output(log_debug, "Test debug", "testfile.c", 42, buffer, BUFFER_SIZE);

    const char *expected = "\033[35m[DEBUG] (testfile.c:42) Test debug\033[0m\n";
    CU_ASSERT_STRING_EQUAL(buffer, expected);
}

void test_log_error(void)
{
    char buffer[BUFFER_SIZE] = {0};
    capture_output(log_error, "Test error", "testfile.c", 42, buffer, BUFFER_SIZE);

    const char *expected = "\033[31m[ERROR] (testfile.c:42) Test error\033[0m\n";
    CU_ASSERT_STRING_EQUAL(buffer, expected);
}

void run_utils_tests(void)
{
    CU_pSuite suite = CU_add_suite("utils", NULL, NULL);

    CU_add_test(suite, "fs_exists", test_fs_exists);
    CU_add_test(suite, "fs_read_file", test_fs_read_file);
    CU_add_test(suite, "ft_strerr", test_ft_strerr);
    CU_add_test(suite, "log_error", test_log_error);
    CU_add_test(suite, "log_warning", test_log_warning);
    CU_add_test(suite, "log_info", test_log_info);
    CU_add_test(suite, "log_debug", test_log_debug);
}