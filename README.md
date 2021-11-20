# Trabalho Prático - Processos e Threads

Algumas implementações em C++ de multiplicações de matrizes.

### Tabela de Conteúdos

1. [Compilando](#1-how-to-build)
3. [Executando](#2-how-to-run)

# 1. Compilando

Os arquivos de código fonte presentes na pasta `src` podem ser compilados através do compilador `g++` manualmente. Como alternativa, para criar os executaveis deste projeto de uma única vez, no diretório base execute o seguinte comando:

```shell
sh build.sh
```

Os arquivos serão compilados e os executaveis estarão na pasta `dist`.

# 2. Executando

Uma vez que os arquivos já foram compilados, você pode rodar o seguinte comando para gerar dois arquivos contendo os valores aleatoriamente gerados de uma matriz:

```shell
./dist/auxiliar <m1> <n1> <m2> <n2>
```

Onde `m1` e `n1` são as dimensões da matriz `A`, assim como `m2` e `n2` são as dimensões da matriz `B`.

Os arquivos `ma.txt` e `mb.txt`, contendo os valores da matriz `A` e `B` respectivamente, serão gerados na pasta onde o comando fora executado.

Estes arquivos podem ser utilizados na execução dos seguintes comandos:

```shell
./dist/sequencial ma.txt mb.txt
# ou
./dist/threads ma.txt mb.txt <p>
# ou
./dist/processos ma.txt mb.txt <p>
```

Onde `<p>` é um número inteiro o qual representa quantidade de elementos que cada thread ou processo irá calcular. (Recomenda-se `p = (m1 * n2) / 8`).

<hr />

Autores: Lucas do Nascimento Ribeiro & João Daniel Queiroz da Silva
