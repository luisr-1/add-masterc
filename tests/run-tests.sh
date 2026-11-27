#!/bin/bash

BIN=./build/add-masterc               # caminho do binário
SCENARIOS=tests/scenarios.txt         # arquivo com entradas
EXPECTED=tests/expected.txt           # arquivo de saídas esperadas
OUT=resultados.txt                    # arquivo gerado pelo programa
GEN=tests/generate_expected.py        # gerador em Python

echo "[ RUNNER ] Verificando arquivos..."

# 1. verificar se existe o arquivo de entrada
if [ ! -f "$SCENARIOS" ]; then
    echo "✗ ERRO: $SCENARIOS não encontrado!"
    exit 1
fi

# 2. verificar se o gerador existe
if [ ! -f "$GEN" ]; then
    echo "✗ ERRO: gerador $GEN não encontrado!"
    exit 1
fi

# 3. verificar se o binário existe
if [ ! -x "$BIN" ]; then
    echo "✗ ERRO: binário $BIN não encontrado! Execute 'make' antes."
    exit 1
fi

# 4. gerar expected.txt se não existir ou se scenarios.txt / gerador forem mais recentes
if [ ! -f "$EXPECTED" ] || [ "$SCENARIOS" -nt "$EXPECTED" ] || [ "$GEN" -nt "$EXPECTED" ]; then
    echo "[ RUNNER ] Gerando $EXPECTED atualizado..."
    python3 "$GEN"

    if [ $? -ne 0 ]; then
        echo "✗ ERRO ao gerar expected.txt"
        exit 1
    fi

    echo "[ RUNNER ] expected.txt criado com sucesso!"
fi

echo "[ RUNNER ] Executando programa..."
"$BIN" "$SCENARIOS"

if [ $? -ne 0 ]; then
    echo "✗ ERRO: problema ao executar o binário."
    exit 1
fi

echo "[ RUNNER ] Comparando resultado..."
diff -u "$EXPECTED" "$OUT"

if [ $? -eq 0 ]; then
    echo "✓ TODOS OS TESTES PASSARAM!"
else
    echo "✗ SAÍDAS DIFEREM!"
    exit 1
fi
