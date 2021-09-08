# Mini Shell - FSO
Um programa que simula um shell com funcionalidades muito básicas. Aceita
o caminho de um programa com um argumento obrigatório e imprime
a saída do programa entrado pelo usuário no terminal. Exemplo:

    /bin/apt-get moo

A saída será:

                    (__) 
                    (oo) 
              /------\/ 
             / |    ||   
            *  /\---/\ 
               ~~   ~~   
    ..."Have you mooed today?"...
    > Demorou 0.0 segundos, retornou 0

Para mais informações sobre o enunciado do problema consulte o 
[PDF](https://moj.naquadah.com.br/contests/bcr-FSO-2021_1-trabalho-001/fso-timedshell.pdf), a 
[página](https://moj.naquadah.com.br/contests/bcr-FSO-2021_1-trabalho-001/fso-timedshell.html)
ou o [vídeo](https://www.youtube.com/watch?v=cHcr1EZdFao) com uma breve demonstração (começa em 14:27).


## Brincando com o mini-shell
Abra o terminal e execute:

    cd src
    chmod +x print-process-tree.sh
    watch -n 0.5 ./print-process-tree.sh

Assim podemos visualizar quase em tempo real a àrvore
de processos do programa. Em outro terminal, execute:

    gcc mini-shell.c -O2 -static -lm

Igonore o warning e comece o programa:

    ./a.out

Experimente com alguns comandos:

    /usr/bin/ls .
    /usr/bin/ls /
    /usr/bin/ls --color

    /bin/apt-get moo
    /bin/false 111

Faça <kbd>Ctrl</kbd>+<kbd>D</kbd> para sair do programa.


## Funções aprendidas para o programa:
[Docs](https://pubs.opengroup.org/onlinepubs/9699919799/functions/exec.html) da
família de funções `exec`.

- `execl`
- `execve`
- `gettimeofday`
- `execv`: parece muito mais conveniente que `execl` por que a chamada 
da função continua a igual independentemente do número de argumentos
do comando.
- `strerror`


## Medir tempo
[8 maneiras de medir tempo](https://levelup.gitconnected.com/8-ways-to-measure-execution-time-in-c-c-48634458d0f9).

[clock_t no stackoverflow](https://stackoverflow.com/questions/3557221/how-do-i-measure-time-in-c)


## Continuação/evolução do mini shell
[Mais funcionalidades](https://web2.clarkson.edu/class/cs444/assignments/shell/)
de outras universidades.

[Mais inspiração](https://brennan.io/2015/01/16/write-a-shell-in-c/)
se precisar de ajuda.