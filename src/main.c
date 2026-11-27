#include "calc/core/fat.h"
#include "calc/handlers/handle_operation.h"
#include "types/big_integer.h"
#include "types/operators.h"
#include "view/menu.h"
#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_SIZE 10000

static void trimWhitespace(char *str) {
  if (!str)
    return;

  size_t start = 0;
  while (str[start] != '\0' && isspace((unsigned char)str[start]))
    start++;

  size_t end = strlen(str);
  while (end > start && isspace((unsigned char)str[end - 1]))
    end--;

  size_t len = end - start;
  if (start > 0 && len > 0)
    memmove(str, str + start, len);

  str[len] = '\0';
}

int main(const int argc, const char *argv[]) {
  int is_interactive = 1;

  if (argc > 1) {
    if (!freopen(argv[1], "r", stdin)) {
      perror("Erro ao abrir arquivo de entrada");
      return 1;
    }

    if (!freopen("resultados.txt", "w", stdout)) {
      perror("Erro ao criar arquivo de resultados");
      return 1;
    }

    is_interactive = 0;
  }

  char line[MAX_INPUT_SIZE];

  while (1) {
    if (is_interactive)
      show_menu();

    if (fgets(line, sizeof(line), stdin) == NULL)
      break;

    trimWhitespace(line);

    if (strlen(line) == 0)
      continue;

    const char op = line[0];
    if (isspace((unsigned char)op))
      continue;

    if (op == 'q' || op == 'Q')
      break;

    bigInt result = NULL;

    if (op == fat_operator) {
      if (is_interactive)
        printf("Digite o valor do fatorial que desejar calcular\n"
               "|------->");

      if (fgets(line, sizeof(line), stdin)) {
        trimWhitespace(line);

        char *endptr = NULL;
        errno = 0;
        long n = strtol(line, &endptr, 10);
        if (errno != 0 || endptr == line || *endptr != '\0') {
          fprintf(stderr, "Entrada inválida para fatorial: %s\n", line);
          continue;
        }

        if (n < 0) {
          printf("Fatorial para números reais negativos não é definido\n");
          continue;
        }

        result = factorialBigInt((unsigned int)n);
        if (result) {
          char *decimalRep = result->to_decimal_representation(result);
          printf("!%ld = %s\n", n, decimalRep);
          free(decimalRep);
          result->destroy(result);
          result = NULL;
        }
      }
    } else if (isValidOperation(op)) {
      char bufNum1[MAX_INPUT_SIZE];
      char bufNum2[MAX_INPUT_SIZE];
      if (is_interactive)
        printf("Insira o valor do primeiro número\n"
               "|------->");

      if (!fgets(bufNum1, sizeof(bufNum1), stdin))
        break;
      trimWhitespace(bufNum1);

      if (is_interactive)
        printf("Insira o valor do segundo número\n"
               "|------->");

      if (!fgets(bufNum2, sizeof(bufNum2), stdin))
        break;
      trimWhitespace(bufNum2);

      bigInt num1 = initNumber(bufNum1);
      bigInt num2 = initNumber(bufNum2);

      if (num1 && num2) {
        bool is_neg_mod =
            (op == mod_operator) && (num1->signal == -1 || num2->signal == -1);

        result = getResult(op, num1, num2);
        if (result) {
          char *decimalRep = result->to_decimal_representation(result);
          printf("%s %c %s = %s\n", bufNum1, op, bufNum2, decimalRep);

          free(decimalRep);
          decimalRep = NULL;

          result->destroy(result);
          result = NULL;
        } else if (!is_neg_mod) {
          printf("%s %c %s = undefined\n", bufNum1, op, bufNum2);
        }
      }

      if (num1) {
        num1->destroy(num1);
        num1 = NULL;
      }
      if (num2) {
        num2->destroy(num2);
        num2 = NULL;
      }
    } else {
      printf("Operacao desconhecida: %c\n", op);
    }
  }

  return 0;
}
