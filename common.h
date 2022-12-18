#pragma once

#define LOG(...)                                                       \
    do                                                                 \
    {                                                                  \
        fprintf(stderr, "%s:%d %s(): ", __FILE__, __LINE__, __func__); \
        fprintf(stderr, __VA_ARGS__);                                  \
        fprintf(stderr, "\n");                                         \
    } while (0);
