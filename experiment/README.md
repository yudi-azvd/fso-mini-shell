# Brincando com o mini-shell
Abra o terminal e execute:

```sh
cd experiment
chmod +x print-process-tree.sh
watch -n 0.5 ./print-process-tree.sh
```

Assim podemos visualizar quase em tempo real a àrvore
de processos do programa. Em outro terminal, execute:

    gcc mini-shell.c
    ./a.out

Experimente com alguns comandos:

    /usr/bin/ls .
    /usr/bin/ls /
    /usr/bin/ls --color

    /bin/apt-get moo
    /bin/false 111


## Um bug?
No vídeo do professor:

    apt-get moo
    > Erro: No such file or directory
    > Demorou 0 segundos, retornou 2

Minha saída:

    apt-get moo
    > Erro: No such file or directory
    > Demorou 0 segundos, retornou 1

Os status de retorno são diferentes.