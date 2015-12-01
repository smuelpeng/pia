/*
  tests_example.h
  Copyright (c) J.J. Green 2015
*/

#include <pia.h>
#include "tests_pia.h"

CU_TestInfo tests_pia[] =
  {
    {"self", test_pia_self},
    {"redundant", test_pia_redundant},
    {"channel", test_pia_channel},
    {"bowtie", test_pia_bowtie},
    {"self-intersect", test_pia_self_intersect},
    {"half-rectangle", test_pia_half_rect},
    {"cross", test_pia_cross},
    {"drop shadow", test_pia_drop_shadow},
    {"rectangle-in-rectangle", test_pia_rect_in_rect},
    CU_TEST_INFO_NULL,
  };

extern void test_pia_self(void)
{
  point_t a[] = {{2, 3}, {2, 3}, {2, 3}, {2, 4}, {3, 3}, {2, 3}, {2, 3}};
  size_t na = sizeof(a)/sizeof(point_t);
  float area = pia_area(a, na, a, na);

  CU_ASSERT(area == 0.5f);
}

extern void test_pia_redundant(void)
{
  point_t a[] = {{2, 3}, {2, 3}, {2, 3}, {2, 4}, {3, 3}, {2, 3}, {2, 3}};
  point_t b[] = {{1, 1}, {1, 4}, {4, 4}, {4, 1}, {1, 1}};
  size_t na = sizeof(a)/sizeof(point_t);
  size_t nb = sizeof(b)/sizeof(point_t);
  float area = pia_area(a, na, b, nb);
  //printf("[%.8f]", area);
  CU_ASSERT(area == 0.5f);
}

extern void test_pia_channel(void)
{
  point_t a[] = {{1, 7}, {4, 7}, {4, 6}, {2, 6}, {2, 3}, {4, 3}, {4, 2}, {1, 2}};
  point_t b[] = {{3, 1}, {5, 1}, {5, 4}, {3, 4}, {3, 5}, {6, 5}, {6, 0}, {3, 0}};
  size_t na = sizeof(a)/sizeof(point_t);
  size_t nb = sizeof(b)/sizeof(point_t);
  float area = pia_area(a, na, b, nb);

  CU_ASSERT(area == 0.0f);
}

extern void test_pia_bowtie(void)
{
  point_t a[] = {{1, 1}, {1, 2}, {2, 1}, {2, 2}};
  point_t b[] = {{0, 0}, {0, 4}, {4, 4}, {4, 0}};
  size_t na = sizeof(a)/sizeof(point_t);
  size_t nb = sizeof(b)/sizeof(point_t);
  float area = pia_area(a, na, b, nb);

  CU_ASSERT(area == 0.0f);
}

extern void test_pia_self_intersect(void)
{
  point_t a[] = {{0, 0}, {3, 0}, {3, 2}, {1, 2}, {1, 1}, {2, 1}, {2, 3}, {0, 3}};
  point_t b[] = {{0, 0}, {0, 4}, {4, 4}, {4, 0}};
  size_t na = sizeof(a)/sizeof(point_t);
  size_t nb = sizeof(b)/sizeof(point_t);
  float area = pia_area(a, na, b, nb);

  CU_ASSERT(area == -9.0f);
}

extern void test_pia_half_rect(void)
{
  point_t a[] = {{0, 0}, {1, 0}, {0, 1}};
  point_t b[] = {{0, 0}, {0, 1}, {1, 1}, {1, 0}};
  size_t na = sizeof(a)/sizeof(point_t);
  size_t nb = sizeof(b)/sizeof(point_t);
  float area = pia_area(a, na, b, nb);

  CU_ASSERT(area == -0.5f);
}

extern void test_pia_cross(void)
{
  point_t a[] = {{1, 3}, {2, 3}, {2, 0}, {1, 0}};
  point_t b[] = {{0, 1}, {3, 1}, {3, 2}, {0, 2}};
  size_t na = sizeof(a)/sizeof(point_t);
  size_t nb = sizeof(b)/sizeof(point_t);
  float area = pia_area(a, na, b, nb);
  //printf("[%.8f]", area);
  CU_ASSERT(area == -1.0f);
}

extern void test_pia_drop_shadow(void)
{
  point_t a[] ={{0, 0}, {0, 2}, {2, 2}, {2, 0}};
  point_t b[] = {{1, 1}, {3, 1}, {3, 3}, {1, 3}};
  size_t na = sizeof(a)/sizeof(point_t);
  size_t nb = sizeof(b)/sizeof(point_t);
  float area = pia_area(a, na, b, nb);
  //printf("[%.8f]", area);
  CU_ASSERT(area == -1.0f);
}

extern void test_pia_rect_in_rect(void)
{
  point_t a[] = {{0, 0}, {0, 4}, {4, 4}, {4, 0}};
  point_t b[] = {{1, 1}, {1, 2}, {2, 2}, {2, 1}};
  size_t na = sizeof(a)/sizeof(point_t);
  size_t nb = sizeof(b)/sizeof(point_t);
  float area = pia_area(a, na, b, nb);

  CU_ASSERT(area == 1.0f);
}
