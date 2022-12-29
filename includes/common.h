#pragma once

#include "callbacks.h"
#include "string_callbacks.h"

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <sys/types.h>
#include <stdio.h>

#define LOG(...)                                                       \
    do                                                                 \
    {                                                                  \
        fprintf(stderr, "%s:%d %s(): ", __FILE__, __LINE__, __func__); \
        fprintf(stderr, __VA_ARGS__);                                  \
        fprintf(stderr, "\n");                                         \
    } while (0);
