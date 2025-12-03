#include "calc/core/fat.h"
#include "calc/handlers/handle_operation.h"
#include "types/big_integer.h"
#include "types/operators.h"
#include "view/menu.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX_INPUT_SIZE 10000

void cleanNewLine(char *str) {
  size_t len = strlen(str);
  if (len > 0 && str[len - 1] == '\n') {
    str[len - 1] = '\0';
  }
}

int main(int argc, char *argv[]) {
  int is_interactive = 1;

  if (argc > 1) {
    if (!freopen(argv[1], "r", stdin)) {
      perror("Erro ao abrir arquivo de entrada\n");
      return 1;
    }

    if (!freopen("resultados.txt", "w", stdout)) {
      perror("Erro ao criar arquivo de resultados\n");
      return 1;
    }

    is_interactive = 0;
  }

  char op;
  char line[MAX_INPUT_SIZE];

  while (1) {
    if (is_interactive)
      show_menu();

    if (fgets(line, sizeof(line), stdin) == NULL)
      break;

    cleanNewLine(line);

    if (strlen(line) == 0)
      continue;

    op = line[0];
    if (isspace(op))
      continue;

    if (op == 'q' || op == 'Q')
      break;

    bigInt result = NULL;

    if (op == fat_operator) {
      if(is_interactive)
          printf("Digite o valor do fatorial que desejar calcular\n"
             "|------->");
      
      if (fgets(line, sizeof(line), stdin)) {
        cleanNewLine(line);

        int n = strtoul(line, NULL, 10);
        if (n < 0) {
          printf("Fatorial para números reais negativos não é definido\n");
          continue;
        }

        result = factorialBigInt(n);
        if (result) {
          char *decimalRep = result->to_decimal_representation(result);
          printf("!%u = %s\n", n, decimalRep);
          free(decimalRep);
          result->destroy(result);
          result = NULL;
        }
      }
    } else if (isValidOperation(op) && op != fat_operator) {
      char bufNum1[MAX_INPUT_SIZE];
      char bufNum2[MAX_INPUT_SIZE];
      if(is_interactive)
        printf("Insira o valor do primeiro número\n"
             "|------->");
      
      if (!fgets(bufNum1, sizeof(bufNum1), stdin))
        break;
      cleanNewLine(bufNum1);

      if(is_interactive)
        printf("Insira o valor do segundo número\n"
             "|------->");
      
      if (!fgets(bufNum2, sizeof(bufNum2), stdin))
        break;
      cleanNewLine(bufNum2);

      bigInt num1 = initNumber(bufNum1);
      bigInt num2 = initNumber(bufNum2);

      if (num1 && num2) {
        result = getResult(op, num1, num2);
        if (result) {
          char *decimalRep = result->to_decimal_representation(result);
          printf("%s %c %s = %s\n", bufNum1, op, bufNum2, decimalRep);
          free(decimalRep);
          result->destroy(result);
          result = NULL;
        }

        num1->destroy(num1);
        num1 = NULL;
        num2->destroy(num2);
        num2 = NULL;
      }
    } else {
      printf("Operacao desconhecida: %c\n", op);
    }
  }

  return 0;
}
