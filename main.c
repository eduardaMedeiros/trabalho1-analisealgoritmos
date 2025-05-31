#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//-------------------RECURSIVA---------------------

// Função recursiva para resolver o problema de subset sum
int recursive_dfs(int* nums, int numsSize, int i, int current_sum, int target) {
    // Caso base: se a soma atual for igual ao alvo, encontramos uma solução
    if (current_sum == target) return 1;
    // Caso base: se excedemos o tamanho ou a soma atual passa do alvo, retorna falso
    if (i >= numsSize || current_sum > target) return 0;

    // Explora dois caminhos: incluir o elemento atual ou não incluir
    return recursive_dfs(nums, numsSize, i + 1, current_sum + nums[i], target) ||
           recursive_dfs(nums, numsSize, i + 1, current_sum, target);
}

// Função que inicializa o processo recursivo
int recursive_partition(int* nums, int numsSize) {
    int total = 0;
    // Calcula a soma total dos elementos
    for (int i = 0; i < numsSize; i++) total += nums[i];

    // Se a soma total for ímpar, não é possível dividir em dois subconjuntos iguais
    if (total % 2 != 0) return 0;

    int target = total / 2;

    // Inicia a busca recursiva
    return recursive_dfs(nums, numsSize, 0, 0, target);
}

//-------------------TOP-DOWN COM MEMOIZATION---------------------

// Função recursiva com memoization
int memoization_dfs(int* nums, int numsSize, int i, int current_sum, int target, int** memo) {
    // Caso base: encontramos uma soma válida
    if (current_sum == target) return 1;
    // Caso base: índices fora do limite ou soma que ultrapassa o alvo
    if (i >= numsSize || current_sum > target) return 0;

    // Se já foi calculado antes, retorna o valor armazenado
    if (memo[i][current_sum] != -1) return memo[i][current_sum];

    // Calcula e armazena o resultado (incluir ou não incluir o elemento atual)
    memo[i][current_sum] = memoization_dfs(nums, numsSize, i + 1, current_sum + nums[i], target, memo) ||
                           memoization_dfs(nums, numsSize, i + 1, current_sum, target, memo);
    return memo[i][current_sum];
}

// Função que prepara a matriz de memoização e chama a função recursiva
int memoization_partition(int* nums, int numsSize) {
    int total = 0;
    // Calcula a soma total dos elementos
    for (int i = 0; i < numsSize; i++) total += nums[i];

    // Se for ímpar, não é possível particionar
    if (total % 2 != 0) return 0;

    int target = total / 2;

    // Cria uma matriz de memoização com tamanho numsSize x (target + 1)
    int** memo = (int**)malloc(numsSize * sizeof(int*));
    for (int i = 0; i < numsSize; i++) {
        memo[i] = (int*)malloc((target + 1) * sizeof(int));
        for (int j = 0; j <= target; j++) memo[i][j] = -1;  // Inicializa com -1
    }

    // Executa a busca com memoization
    int result = memoization_dfs(nums, numsSize, 0, 0, target, memo);

    // Libera memória alocada
    for (int i = 0; i < numsSize; i++) free(memo[i]);
    free(memo);

    return result;
}

//-------------------BOTTOM-UP COM TABULATION---------------------

// Função que resolve o problema usando programação dinâmica (bottom-up)
int tabulation_partition(int* nums, int numsSize) {
    int total = 0;
    // Soma total dos elementos
    for (int i = 0; i < numsSize; i++) total += nums[i];

    // Se for ímpar, não dá para dividir em dois subconjuntos iguais
    if (total % 2 != 0) return 0;

    int target = total / 2;

    // Cria um vetor dp de tamanho (target + 1) inicializado com 0
    int* dp = (int*)calloc(target + 1, sizeof(int));
    dp[0] = 1;  // Soma zero sempre é possível (subconjunto vazio)

    // Percorre cada número no conjunto
    for (int i = 0; i < numsSize; i++) {
        // Atualiza dp de trás para frente para não sobrescrever valores necessários
        for (int j = target; j >= nums[i]; j--) {
            if (dp[j - nums[i]]) dp[j] = 1;
        }
    }

    int result = dp[target];  // Verifica se é possível alcançar a soma target
    free(dp);  // Libera memória

    return result;
}

//-------------------FUNÇÕES AUXILIARES---------------------

// Executa um caso de teste com as três abordagens
void test_case(int* nums, int size) {
    printf("Recursive: %s\n", recursive_partition(nums, size) ? "true" : "false");
    printf("Memoization: %s\n", memoization_partition(nums, size) ? "true" : "false");
    printf("Tabulation: %s\n\n", tabulation_partition(nums, size) ? "true" : "false");
}

// Imprime um vetor no formato {a, b, c, ...}
void print_array(int* arr, int n) {
    printf("{");
    for (int i = 0; i < n; i++) {
        printf("%d", arr[i]);
        if (i < n - 1) printf(", ");
    }
    printf("}");
}

//-------------------FUNÇÃO PRINCIPAL---------------------

int main() {
    // Define alguns casos de teste
    int test1[] = {1, 5, 11, 5};  // true
    int test2[] = {1, 2, 3, 5};   // false
    int test3[] = {2, 2, 3, 5};   // false
    int test4[] = {1, 1, 1, 1};   // true
    int test5[] = {100, 100, 100, 100, 100, 100, 100, 100};  // true

    // Executa e imprime os resultados de cada teste
    printf("Caso de teste 1: ");
    print_array(test1, 4);
    printf("\n");
    test_case(test1, 4);

    printf("Caso de teste 2: ");
    print_array(test2, 4);
    printf("\n");
    test_case(test2, 4);

    printf("Caso de teste 3: ");
    print_array(test3, 4);
    printf("\n");
    test_case(test3, 4);

    printf("Caso de teste 4: ");
    print_array(test4, 4);
    printf("\n");
    test_case(test4, 4);

    printf("Caso de teste 5: ");
    print_array(test5, 8);
    printf("\n");
    test_case(test5, 8);

    return 0;
}
