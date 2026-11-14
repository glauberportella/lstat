#ifndef _TYPES_H_
#define _TYPES_H_

#include <stdlib.h>


// ERROR CODES

#define EALLOCATION    0x0000
#define ENULLDATASET   0x1000
#define EEMPTYDATASET  0x1001

/**
 * Dataset
 */
typedef struct {
    const double *data;
    size_t size;
} lstat_dataset_t;

typedef struct {
    const double *x;
    const double *y;
    size_t size;
} lstat_pair_t;

typedef struct {
    const double *data;
    size_t rows;
    size_t cols;
} lstat_matrix_t;

typedef struct {
    double *data;
    size_t size;
} lstat_vector_t;

typedef struct {
    size_t count;
    double mean;
    double m2;
} lstat_online_t;

typedef struct {
    size_t count;
    double mean_x;
    double mean_y;
    double co_moment;
    double m2_x;
    double m2_y;
} lstat_online_pair_t;

typedef struct {
  double value;
  double freq;
} lstat_freq_t;

#endif
