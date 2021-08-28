# Mini Shell - FSO
Trabalho 1 de Fundamentos de Sistemas Operacionais: Mini Shell

[Apresentação do trabalho em vídeo](https://www.youtube.com/watch?v=cHcr1EZdFao)
(começa em 14:27).

Uma versão experimental do mini-shell está [aqui](experiment/README.md).

## Algumas direções
### Funções que podem ser úteis:
[Docs](https://pubs.opengroup.org/onlinepubs/9699919799/functions/exec.html) da família de funções `exec`.

- `execl`
- `execve`
- `execv`: parece muito mais conveniente que `execl` por que a chamada 
da funcção continua a igual independentemente do número de argumentos
do comando.
- `strerror`


### Medir tempo
[8 maneiras de medir tempo](https://levelup.gitconnected.com/8-ways-to-measure-execution-time-in-c-c-48634458d0f9).

[clock_t no stackoverflow](https://stackoverflow.com/questions/3557221/how-do-i-measure-time-in-c)
