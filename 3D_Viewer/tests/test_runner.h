#ifndef _3DVIEWER_TESTS_TEST_RUNNER_H

#define _3DVIEWER_TESTS_TEST_RUNNER_H

#include <check.h>

#define ARRAY_SIZE(arr) sizeof(arr) / sizeof(arr[0])

Suite* obj_parser_suite();
Suite* affine_suite();

#endif /** _3DVIEWER_TESTS_TEST_RUNNER_H **/
