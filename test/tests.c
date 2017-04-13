/*
  tests.c
  unit test case loader

  Copyright (c) J.J. Green 2015
*/

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include <CUnit/CUnit.h>

#include "tests_pia.h"

static CU_SuiteInfo suites[] =
  {
    {"pia", NULL, NULL, tests_pia},
    CU_SUITE_INFO_NULL,
  };

extern void tests_load(void)
{
  assert(NULL != CU_get_registry());
  assert(!CU_is_test_running());

  if (CU_register_suites(suites) != CUE_SUCCESS)
    {
      fprintf(stderr, "suite registration failed - %s\n",
              CU_get_error_msg());
      exit(EXIT_FAILURE);
    }
}
