#include <stdio.h>
#include <assert.h>

#include "lstat.h"

void test_descritive_return_double(
    const lstat_dataset_t* dataset, 
    const char* funcname, 
    double (*functotest)(const lstat_dataset_t*), 
    double expected
) {
  printf("-- TEST: test_%s --\n", funcname);

  double value = functotest(dataset);
  assert(value == expected);
  printf("OK\n");

  printf("-------------------------\n");
}

void test_descritive_return_size_t(
    const lstat_dataset_t* dataset, 
    const char* funcname, 
    size_t (*functotest)(const lstat_dataset_t*), 
    double expected
) {
  printf("-- TEST: test_%s --\n", funcname);

  size_t value = functotest(dataset);
  assert(value == expected);
  printf("OK\n");

  printf("-------------------------\n");
}

int main() {
  const double data1[5] = {1.0, 2.0, 3.0, 4.0, 5.0};
  const double data2[6] = {1.0, 1.0, 2.0, 3.0, 4.0, 4.0};
  const double data3[3] = {120.50, 45.90, 10.30};

  lstat_dataset_t dataset1 = {
    .data = data1,
    .size = 5
  };

  lstat_dataset_t dataset2 = {
    .data = data2,
    .size = 6
  };
  
  lstat_dataset_t dataset3 = {
    .data = data3,
    .size = 3
  };
 
  printf("LSTAT - Little Statistical Library\n");

  // -- test: stat_sum()
  test_descritive_return_double(&dataset1, "stat_sum", stat_sum, 15);
  test_descritive_return_double(&dataset2, "stat_sum", stat_sum, 15);

  // -- test: stat_count() 
  test_descritive_return_size_t(&dataset1, "stat_count", stat_count, 5);
  test_descritive_return_size_t(&dataset2, "stat_count", stat_count, 6);
  
  // -- test: stat_min()
  test_descritive_return_double(&dataset1, "stat_min", stat_min, 1.0);
  test_descritive_return_double(&dataset3, "stat_min", stat_min, 10.30);
  
  // -- test: stat_max()
  test_descritive_return_double(&dataset1, "stat_max", stat_max, 5.0);
  test_descritive_return_double(&dataset2, "stat_max", stat_max, 4.0);
  test_descritive_return_double(&dataset3, "stat_max", stat_max, 120.50);

  // -- test: stat_range()
  test_descritive_return_double(&dataset1, "stat_range", stat_range, 4.0);
  test_descritive_return_double(&dataset2, "stat_range", stat_range, 3.0);
  test_descritive_return_double(&dataset3, "stat_range", stat_range, 110.20);

  // -- test: stat_mean()
  test_descritive_return_double(&dataset1, "stat_mean", stat_mean, 3.0);
  test_descritive_return_double(&dataset2, "stat_mean", stat_mean, 2.5);
  test_descritive_return_double(&dataset3, "stat_mean", stat_mean, 58.90);


  return 0;
}
