#include "mult.h"
#include "../../types/big_integer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Remove zeros à esquerda de um bigInt
void remove_leading_zeros_bigint(bigInt n) {
    if (!n || !n->vector || !n->size) return;
    
    size_t new_size = *n->size;
    while (new_size > 1 && n->vector->vector[new_size - 1] == 0) {
        new_size--;
    }
    *n->size = new_size;
}

// Combina dois bigInts (adição)
bigInt combine_bigint(bigInt a, bigInt b) {
    if (!a || !b || !a->vector || !b->vector) return NULL;
    
    size_t max_size = (*a->size > *b->size) ? *a->size : *b->size;
    bigInt result = initEmpty(max_size + 1);
    if (!result) return NULL;
    
    int carry = 0;
    size_t i;
    for (i = 0; i < max_size; i++) {
        int sum = carry;
        if (i < *a->size) sum += a->vector->vector[i];
        if (i < *b->size) sum += b->vector->vector[i];
        
        result->vector->vector[i] = sum % 10;
        carry = sum / 10;
    }
    
    if (carry > 0) {
        result->vector->vector[i] = carry;
        *result->size = max_size + 1;
    } else {
        *result->size = max_size;
    }
    
    result->signal = 1;
    remove_leading_zeros_bigint(result);
    return result;
}

// Diferença entre dois bigInts (a - b, assume a >= b)
bigInt difference_bigint(bigInt a, bigInt b) {
    if (!a || !b || !a->vector || !b->vector) return NULL;
    
    bigInt result = initEmpty(*a->size);
    if (!result) return NULL;
    
    int borrow = 0;
    for (size_t i = 0; i < *a->size; i++) {
        int diff = a->vector->vector[i] - borrow;
        if (i < *b->size) {
            diff -= b->vector->vector[i];
        }
        
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        
        result->vector->vector[i] = diff;
    }
    
    result->signal = 1;
    remove_leading_zeros_bigint(result);
    return result;
}

// Shift left (multiplica por 10^n)
bigInt shift_left_bigint(bigInt num, int positions) {
    if (!num || !num->vector) return NULL;
    
    if (positions == 0) {
        return initNumber(num->to_decimal_representation(num));
    }
    
    bigInt result = initEmpty(*num->size + positions);
    if (!result) return NULL;
    
    // Preenche com zeros nas primeiras posições
    for (int i = 0; i < positions; i++) {
        result->vector->vector[i] = 0;
    }
    
    // Copia os dígitos originais
    for (size_t i = 0; i < *num->size; i++) {
        result->vector->vector[i + positions] = num->vector->vector[i];
    }
    
    result->signal = num->signal;
    remove_leading_zeros_bigint(result);
    return result;
}

// Multiplicação escolar simples - CORRIGIDA
bigInt school_multiply_bigint(bigInt a, bigInt b) {
    if (!a || !b || !a->vector || !b->vector) return NULL;
    
    size_t result_size = *a->size + *b->size;
    bigInt result = initEmpty(result_size);
    if (!result) return NULL;
    
    // Inicializa com zeros
    for (size_t i = 0; i < result_size; i++) {
        result->vector->vector[i] = 0;
    }
    
    // Multiplicação correta
    for (size_t i = 0; i < *a->size; i++) {
        int carry = 0;
        for (size_t j = 0; j < *b->size; j++) {
            size_t pos = i + j;
            int product = a->vector->vector[i] * b->vector->vector[j] + 
                         result->vector->vector[pos] + carry;
            result->vector->vector[pos] = product % 10;
            carry = product / 10;
        }
        
        // Propaga o carry para as posições seguintes
        size_t carry_pos = i + *b->size;
        while (carry > 0) {
            int total = result->vector->vector[carry_pos] + carry;
            result->vector->vector[carry_pos] = total % 10;
            carry = total / 10;
            carry_pos++;
        }
    }
    
    result->signal = (a->signal == b->signal) ? 1 : -1;
    remove_leading_zeros_bigint(result);
    return result;
}


// Obtém parte alta do número (dígitos mais significativos)
bigInt get_high_part(bigInt num, size_t split) {
    if (!num || !num->vector || split >= *num->size) return initNumber("0");
    
    size_t high_size = *num->size - split;
    bigInt result = initEmpty(high_size);
    if (!result) return NULL;
    
    for (size_t i = 0; i < high_size; i++) {
        result->vector->vector[i] = num->vector->vector[i + split];
    }
    
    result->signal = 1;
    remove_leading_zeros_bigint(result);
    return result;
}

// Obtém parte baixa do número (dígitos menos significativos)
bigInt get_low_part(bigInt num, size_t split) {
    if (!num || !num->vector) return initNumber("0");
    
    size_t low_size = (*num->size < split) ? *num->size : split;
    bigInt result = initEmpty(low_size);
    if (!result) return NULL;
    
    for (size_t i = 0; i < low_size; i++) {
        result->vector->vector[i] = num->vector->vector[i];
    }
    
    result->signal = 1;
    remove_leading_zeros_bigint(result);
    return result;
}

// Algoritmo de Karatsuba - VERSÃO SIMPLIFICADA E CORRIGIDA
bigInt karatsuba_bigint(bigInt a, bigInt b) {
    if (!a || !b || !a->vector || !b->vector) return NULL;

    // Caso base: usa multiplicação escolar para números pequenos
    if (*a->size <= 4 || *b->size <= 4) {
        return school_multiply_bigint(a, b);
    }

    // Encontra o ponto de divisão (metade do menor número)
    size_t m = (*a->size < *b->size ? *a->size : *b->size) / 2;
    if (m == 0) m = 1;

    // Divide os números em partes alta e baixa
    bigInt a_high = get_high_part(a, m);
    bigInt a_low = get_low_part(a, m);
    bigInt b_high = get_high_part(b, m);
    bigInt b_low = get_low_part(b, m);

    // Verifica se as divisões foram bem sucedidas
    if (!a_high || !a_low || !b_high || !b_low) {
        if (a_high) a_high->destroy(a_high);
        if (a_low) a_low->destroy(a_low);
        if (b_high) b_high->destroy(b_high);
        if (b_low) b_low->destroy(b_low);
        return school_multiply_bigint(a, b);
    }
    // Calcula os três produtos do Karatsuba:
    // z0 = a_low * b_low
    // z1 = a_high * b_high  
    // z2 = (a_low + a_high) * (b_low + b_high)
    bigInt z0 = karatsuba_bigint(a_low, b_low);
    bigInt z1 = karatsuba_bigint(a_high, b_high);
    
    bigInt a_sum = combine_bigint(a_low, a_high);
    bigInt b_sum = combine_bigint(b_low, b_high);
    bigInt z2 = karatsuba_bigint(a_sum, b_sum);

    // Verifica se todos os produtos foram calculados
    if (!z0 || !z1 || !z2) {
        if (z0) z0->destroy(z0);
        if (z1) z1->destroy(z1);
        if (z2) z2->destroy(z2);
        a_high->destroy(a_high);
        a_low->destroy(a_low);
        b_high->destroy(b_high);
        b_low->destroy(b_low);
        a_sum->destroy(a_sum);
        b_sum->destroy(b_sum);
        return school_multiply_bigint(a, b);
    }
// Calcula o resultado final:
    // resultado = z1 * 10^(2m) + (z2 - z1 - z0) * 10^m + z0
    bigInt temp = difference_bigint(z2, z1);
    bigInt middle_term = difference_bigint(temp, z0);
    
    bigInt part1 = shift_left_bigint(z1, 2 * m);      // z1 * 10^(2m)
    bigInt part2 = shift_left_bigint(middle_term, m); // middle * 10^m
    
    bigInt sum1 = combine_bigint(part1, part2);
    bigInt result = combine_bigint(sum1, z0);

    // Define o sinal do resultado
    if (result) {
        result->signal = (a->signal == b->signal) ? 1 : -1;
    }

    // Limpeza de memória
    a_high->destroy(a_high);
    a_low->destroy(a_low);
    b_high->destroy(b_high);
    b_low->destroy(b_low);
    a_sum->destroy(a_sum);
    b_sum->destroy(b_sum);
    z0->destroy(z0);
    z1->destroy(z1);
    z2->destroy(z2);
    temp->destroy(temp);
    middle_term->destroy(middle_term);
    part1->destroy(part1);
    part2->destroy(part2);
    sum1->destroy(sum1);

    return result;
}

// Função principal de multiplicação
bigInt multBigInt(bigInt a, bigInt b) {
    if (!a || !b) return NULL;

    // Verifica multiplicação por zero
    if ((*a->size == 1 && a->vector->vector[0] == 0) || 
        (*b->size == 1 && b->vector->vector[0] == 0)) {
        return initNumber("0");
    }

    // Para números pequenos, usa multiplicação escolar
    if (*a->size <= 10 || *b->size <= 10) {
        return school_multiply_bigint(a, b);
    }

    // Para números grandes, usa Karatsuba
    return karatsuba_bigint(a, b);
}

