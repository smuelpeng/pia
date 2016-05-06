/*
  tests.h
  unit test case loader

  Copyright (c) J.J. Green 2015
*/

#include <stdio.h>
#include <stdlib.h>

#include <CUnit/Basic.h>

#include "tests.h"

int main(void)
{
  CU_BasicRunMode mode = CU_BRM_VERBOSE;
  CU_ErrorAction error_action = CUEA_IGNORE;
  setvbuf(stdout, NULL, _IONBF, 0);

  if (CU_initialize_registry())
    {
      fprintf(stderr,"failed to initialise registry\n");
      return EXIT_FAILURE;
    }

  tests_load();
  CU_basic_set_mode(mode);
  CU_set_error_action(error_action);

  int
    status = CU_basic_run_tests(),
    nfail = CU_get_number_of_failures();

  CU_cleanup_registry();
  printf("\nSuite returned %d.\n", status);

  return (nfail > 0 ? EXIT_FAILURE : EXIT_SUCCESS);
}
