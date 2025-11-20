## Sobre o projeto
___
O projeto é uma calculadora que opera números inteiros de precisão arbitrária, que são conhecidos muitas vezes como BigInt.
Muitos projetos como GMP (GNU Multiple Precision) e linguagens de programação implementam esse tipo para as suas próprias necessidades. A necessidade de se criar um tipo desses é basicamente por limitações de hardware, existe um limite de acordo com a arquitetura do computador em quantos bytes consegue armazenar em seus registradores. Fazendo assim necessário driblarmos essa limitação física com algoritmos e estruturas de dados o mais eficiente possíveis para amortizar a queda de desempenho que existe entre operações em registradores específicos para isso (soma, mutliplicação). O Big Integer, pode ser feito de diferentes maneiras, as principais sendo array de dígitos ou listas encadeadas de dígitos, com mais algumas propriedades em sua estrutura de dados, como sinal (se é um número positivo ou negativo), quantidade atual de dígitos, etc. A necessidade da implementação desse tipo pode ser visto na criptografia, onde se é usado para calcular números provavelmente primos para assinar chaves de criptografia, como também para aplicações de banco de dados e muitas outras aplicações tecno-científicas. Bem, o projeto é meramente acadêmico e com o efeito de manipular, estruturar e aprender mais sobre técnicas de algoritmos e estruturas de dados,
então não espere muito desse projeto. Para ser realizado uma obra prima, com certeza levaria anos e décadas de desenvolvimento. 

O nome do projeto é inspirado na calculadora [ADDMASTER "Baby" 6593](https://collections.whipplemuseum.cam.ac.uk/objects/15303/), uma calculadora mecânica de bolso alemã de 1950~1960.
___
### Dependências
 - GCC (GNU Compiler Collection)
 - GNU Make
 - Valgrind
___
### Como realizar o build
Para realizar o build do projeto, existe na raiz do projeto, um arquivo `Makefile` que automatiza a compilação e linking para montagem do binário

- add-master/
    - src/
    - Makefile
    - ...

é necessário estar na raiz e executar o comando:

```bash
make
```
No momento em que for executado, será criado uma pasta `/build` na raiz do projeto, contendo as dependências que compilaram o binário e o binário com nome `add-masterc`.
- add-master/
    - build/
        - src/
        - add-masterc
    - src/
    - Makefile
    - ...
    
Para executar o binário a partir da raiz do projeto:

```bash
./build/add-masterc
```
### Como apagar o binário
```bash
make clean
```

### Como testar se existe vazamento de memória
```bash
make memcheck
```
Esse comando irá executar o programa e irá logar em arquivos `valgrind.log` a origem do vazamento com a linha de código e com a stacktrace.
___
```
                .___  .___                                 __                        
    _____     __| _/__| _/          _____ _____    _______/  |_  ___________   ____  
    \__  \   / __ |/ __ |  ______  /     \\__  \  /  ___/\   __\/ __ \_  __ \_/ ___\ 
     / __ \_/ /_/ / /_/ | /_____/ |  Y Y  \/ __ \_\___ \  |  | \  ___/|  | \/\  \___ 
    (____  /\____ \____ |         |__|_|  (____  /____  > |__|  \___  >__|    \___  >
         \/      \/    \/               \/     \/     \/            \/            \/ 
         
```
___