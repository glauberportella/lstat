# Definição de tipos de dados

## 1. Estatística descritiva

**Tipo principal**: vetor de observações numéricas.

```c
double values[] = {10.0, 20.0, 30.0, 40.0, 50.0};
size_t size = 5;
```

**Modelo conceitual:**

```c
typedef struct {
    const double *data;
    size_t size;
} lstat_dataset_t;
```

Operação|Entrada|Retorno
--------|-------|-------
Sum|Dataset|double
Count|Dataset|size_t
Min|Dataset|double
Max|Dataset|double
Range|Dataset|double
Mean|Dataset|double
Median|Dataset|double
Mode|Dataset|double
Geometric mean|Dataset|double
Harmonic mean|Dataset|double

##2. Medidas de dispersão

**Tipo principal**: vetor de observações numéricas.

Utiliza o mesmo lstat_dataset_t da primeira parte.

Operação	Entrada	Retorno
Variance	Dataset	double
Sample variance	Dataset	double
Stddev	Dataset	double
Sample stddev	Dataset	double
MAD	Dataset	double
Median absolute deviation	Dataset	double
IQR	Dataset	double
CV	Dataset	double

Não precisa criar outro tipo de dado.
3. Posição e distribuição dos dados
Tipo principal: vetor de observações e parâmetros numéricos.
Operação	Entrada adicional	Retorno
Quantile	double q	double
Percentile	double p	double
Quartile	unsigned int q	double
Z-score	double value	double
Skewness	—	double
Kurtosis	—	double

Exemplo:
double q = 0.75;
double result = lstat_quantile(&dataset, q);


4. Associação entre variáveis
Tipo principal: pares de observações e matrizes.

Aqui precisamos introduzir um novo conceito: múltiplas variáveis observadas simultaneamente.

Exemplo:
Observação	Altura	Peso
1	1.70	65
2	1.80	80
3	1.75	72
4	1.65	58

Modelo:
typedef struct {
    const double *x;
    const double *y;
    size_t size;
} lstat_pair_t;


Para matrizes:
typedef struct {
    const double *data;
    size_t rows;
    size_t cols;
} lstat_matrix_t;


Operação	Entrada	Retorno
Covariance	Pair	double
Sample covariance	Pair	double
Correlation	Pair	double
Rank correlation	Pair	double
Covariance matrix	Matrix	Matrix
Correlation matrix	Matrix	Matrix

5. Transformação e normalização
Tipo principal: vetor de observações e vetor de saída.

Aqui é importante diferenciar operações que retornam um escalar das que transformam um conjunto de dados.
Operação	Entrada	Retorno
Min-Max	Dataset	Vetor transformado
Standardize	Dataset	Vetor transformado
Center	Dataset	Vetor transformado
Scale	Dataset	Vetor transformado
Clip	Dataset + limites	Vetor transformado

Sugestão de estrutura:
typedef struct {
    double *data;
    size_t size;
} lstat_vector_t;


Uma observação de arquitetura: a entrada pode ser const, mas a saída deve ser gravada em um buffer fornecido pelo usuário. Assim, você evita alocações internas.
6. Estatísticas incrementais
Tipo principal: acumulador estatístico.

Aqui está uma das partes mais interessantes para o estudo de C.

Diferentemente das operações anteriores, não precisamos manter todos os dados na memória.

Sugestão de estrutura:
typedef struct {
    size_t count;
    double mean;
    double m2;
} lstat_online_t;


O m2 é o acumulador utilizado pelo algoritmo de Welford para calcular variância incremental.
Operação	Entrada	Retorno
Online mean	Accumulator + value	double
Online variance	Accumulator	double
Online stddev	Accumulator	double
Online covariance	Pair accumulator + x + y	double
Online correlation	Pair accumulator	double

Para covariância incremental, crie uma estrutura independente:
typedef struct {
    size_t count;
    double mean_x;
    double mean_y;
    double co_moment;
    double m2_x;
    double m2_y;
} lstat_online_pair_t;


7. Preparação para LPROB e LML
Aqui não criaria novos algoritmos estatísticos. Criaria modelos de dados que facilitem a evolução das próximas bibliotecas.
Conceito	Tipo sugerido	Uso futuro
Observação	double	LPROB / LML
Dataset	lstat_dataset_t	LPROB / LML
Vetor	lstat_vector_t	LML
Par de variáveis	lstat_pair_t	LSTAT / LML
Matriz	lstat_matrix_t	LML
Acumulador	lstat_online_t	LPROB / LML
Par acumulador	lstat_online_pair_t	LSTAT / LML


Arquitetura consolidada de dados
Minha sugestão é começar com apenas estes cinco tipos públicos:
LSTAT Data Types
1. lstat_dataset_t

Visualização não proprietária de um conjunto de dados.

const double *data · size_t size

2. lstat_vector_t

Vetor numérico mutável.

double *data · size_t size

3. lstat_pair_t

Duas séries de observações relacionadas.

const double *x · const double *y · size_t size

4. lstat_matrix_t

Matriz numérica em memória contígua (row-major).

const double *data · size_t rows · size_t cols

5. lstat_online_t e lstat_online_pair_t

Estado de cálculos incrementais.

Acumuladores estatísticos.
