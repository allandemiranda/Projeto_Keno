# Projeto_Keno
==============
### Desenvolvedores

  **Allan de Miranda Silva**

  **Josué Claudio de Pontes**

### Introdução

O [Keno](https://pt.wikipedia.org/wiki/Keno) é um jogo de loteria muito popular nos casinos modernos, e utilizado igualmente nas loterias estatais.

Num casino tradicional, o jogo do Keno é composto por uma tômbola com 80 bolas numeradas. Os jogadores marcam nos seus cartões (numerados de 1 a 80) alguns dos números. O montante de números marcados varia de casino para casino, mas geralmente varia entre um e quinze.

Da tômbola extrai-se um total de 20 bolas. Os jogadores são pagos de acordo com a coincidência dos seus números marcados no cartão e dos números extraídos. Quantos mais números coincidirem, maior é o prémio atribuído.

Nos casinos online, o jogo de Keno é geralmente apresentado num ecrã que contém a tômbola, e o cartão, que é marcado aleatoriamente ou através do clique no mouse do computador. Os números sorteados na tômbola são marcados diretamente no cartão, o que torna o jogo mais rápido. 

### Instalação

Utilizando o terminal:
1. Faça o clone deste projeto com `git clone https://github.com/allandemiranda/Projeto_Keno.git`
2. Entre na pasta do projeto e digite o comando `g++ -std=c++17 src/KenoBet.cpp src/main.cpp -I include/ -o /bin/Keno.out`
3. Rode a aplicação com `.\bin\Keno.out <nome do arquivo de jogadas>`

### Criando jogadas para a aplicação

Utilizando o terminal:
1. Entre na pasta do projeto digite o comando `cd data`
2. Utilize o Vim ou um editor de texto de sua preferência para criar o arquivo texto dentro da pasta aberta

Modelo de criação do arquivo:
```
1500.0                        <------ Valor que irá apostar 
10                            <------ Quantidade de rodadas que irá apostar
21 12 64 12 11 10 9 5 7 3     <------ Números que irá apostar [1-80]
```
