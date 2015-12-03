/*
  tests_pia.h

  Copyright (c) J.J. Green 2015
*/

#ifndef TESTS_PIA_H
#define TESTS_PIA_H

#include <CUnit/CUnit.h>

extern CU_TestInfo tests_pia[];

extern void test_pia_self(void);
extern void test_pia_redundant(void);
extern void test_pia_channel(void);
extern void test_pia_bowtie(void);
extern void test_pia_self_intersect(void);
extern void test_pia_half_rect(void);
extern void test_pia_cross(void);
extern void test_pia_drop_shadow(void);
extern void test_pia_rect_in_rect(void);
extern void test_pia_degenerate(void);

#endif
