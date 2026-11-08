#ifndef _DESCRITIVE_H_
#define _DESCRITIVE_H_

#include "types.h"

/**
 * @brief Somatório dos valores
 * @param const lstat_dataset_t* dataset
 * @return double
 */
double stat_sum(const lstat_dataset_t* dataset);

/**
 * @brief Quantidade de observações
 * @param const lstat_dataset_t* dataset
 * @return size_t
 */
size_t stat_count(const lstat_dataset_t* dataset);

/**
 * @brief Menor valor
 * @param const lstat_dataset_t* dataset
 * @return double
 */
double stat_min(const lstat_dataset_t* dataset); 

/**
 * @brief Maior valor
 * @param const lstat_dataset_t* dataset
 * @return double
 */
double stat_max(const lstat_dataset_t* dataset);

/**
 * @brief Amplitude (maximo - minimo)
 * @param const lstat_dataset_t* dataset
 * @return double
 */
double stat_range(const lstat_dataset_t* dataset); 

/**
 * @brief Media aritimetica
 * @param const lstat_dataset_t* dataset
 * @return double
 */
double stat_mean(const lstat_dataset_t* dataset); 

/**
 * @brief Mediana
 * @param const lstat_dataset_t* dataset
 * @return double
 */
double stat_median(const lstat_dataset_t* dataset);

/**
 * @brief Moda
 * @param const lstat_dataset_t* dataset
 * @return double
 */
double stat_mode(const lstat_dataset_t* dataset);

/**
 * @brief Média geométrica
 * @param const lstat_dataset_t* dataset
 * @return double
 */
double stat_geometric_mean(const lstat_dataset_t* dataset);

/**
 * @brief Média harmônica
 * @param const lstat_dataset_t* dataset
 * @return double
 */
double stat_harmonic_mean(const lstat_dataset_t* dataset);

#endif
