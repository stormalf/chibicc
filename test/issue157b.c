// SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (C) 2002 Roman Zippel <zippel@linux-m68k.org>
 */

#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#include "lkc.h"

#define DEBUG_EXPR      0


enum string_value_kind {
        k_string,
        k_signed,
        k_unsigned,
};

union string_value {
        unsigned long long u;
        signed long long s;
};

void expr_calc_value(struct expr *e)
{
    union string_value lval = {}, rval = {};
 
}


int main() {
    return 0;
}