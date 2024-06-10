# Calculadora Simples

Este projeto é uma calculadora simples que analisa e avalia expressões aritméticas básicas. Ele converte uma expressão em uma lista de tokens, cria uma árvore de sintaxe abstrata (AST) a partir desses tokens e avalia a expressão para obter o resultado.

## Funcionalidades

- Suporta operações básicas: adição (`+`), subtração (`-`), multiplicação (`*`) e divisão (`/`).
- Analisa e avalia expressões aritméticas seguindo a precedência correta dos operadores.

## Estrutura do Projeto

- `TipoToken`: Enumeração para os tipos de tokens (números e operadores).
- `Token`: Estrutura para representar um token com tipo e valor.
- `NoAST`, `NoNumero`, `NoOpBinario`: Classes para representar nós da árvore de sintaxe abstrata (AST).
- `Analisador`: Classe que analisa a lista de tokens e constrói a AST.
- Funções `tokenizar` e `avaliar`: Funções para tokenizar a string de entrada e avaliar a AST, respectivamente.

## Como Funciona

1. **Tokenização**: A função `tokenizar` converte a string de entrada em uma lista de tokens.
2. **Parsing**: A classe `Analisador` analisa a lista de tokens e constrói a AST.
3. **Avaliação**: A função `avaliar` recebe a AST e calcula o resultado da expressão.

## Exemplo

Entrada: `"3 + 5 * 2 - 8 / 4"`

Saída: `Resultado: 9`

## Uso

### Compilação

Para compilar o código, use um compilador de C++ como o `g++`. No terminal, navegue até o diretório do projeto e execute:

```bash
g++ -o calculadora calculadora.cpp
