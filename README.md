# Jogo da Memória com Arduino

Este projeto implementa um jogo da memória eletrônico utilizando a plataforma Arduino UNO. O objetivo é desafiar os jogadores a memorizarem uma sequência aleatória de LEDs coloridos e reproduzi-la corretamente por meio de botões.

## Objetivo do Projeto

Criar uma ferramenta educacional para o ensino de lógica de programação, eletrônica básica e interação com hardware físico. O projeto foi desenvolvido para ser utilizado em atividades pedagógicas com estudantes entre 8 e 15 anos, em ambientes de robótica educacional.

## Componentes Utilizados

- 1 Arduino UNO
- 1 Display LCD 16x2 com módulo I²C
- 4 LEDs (vermelho, amarelo, verde, azul)
- 4 botões correspondentes aos LEDs
- 1 botão branco (start/reset)
- 1 buzzer ativo
- 1 potenciômetro (ajuste de nível)
- 1 protoboard
- Resistores de 220Ω e 10kΩ
- Jumpers coloridos
- Fonte 9V ou conexão USB

## Funcionalidades

- Exibição de mensagens em LCD via I²C
- Níveis de dificuldade ajustáveis com potenciômetro
- Geração randômica de sequência de LEDs
- Resposta do jogador por botões
- Feedback visual (LEDs) e sonoro (buzzer)
- Reinício automático do jogo após término

## Pinagem Utilizada

| Componente         | Pino Arduino |
|--------------------|--------------|
| LED Vermelho       | 10           |
| LED Amarelo        | 8            |
| LED Verde          | 6            |
| LED Azul           | 4            |
| Botão Vermelho     | 11           |
| Botão Amarelo      | 9            |
| Botão Verde        | 7            |
| Botão Azul         | 5            |
| Botão Start (branco)| 12          |
| Buzzer             | 3            |
| Potenciômetro      | A0           |
| LCD I²C SDA        | A4           |
| LCD I²C SCL        | A5           |

## Como Utilizar

1. Monte o circuito conforme o esquemático disponível.
   ![circuito-do-jogo-da-memoria](https://github.com/user-attachments/assets/365a7d45-a3e7-4f06-9d13-0770f2ff823e)
   
3. Faça o upload do código para a placa Arduino usando a IDE Arduino.
4. Conecte a fonte de alimentação ou cabo USB.
5. Ajuste o nível com o potenciômetro.
6. Pressione o botão de início.
7. Memorize a sequência apresentada.
8. Reproduza a sequência usando os botões correspondentes.
9. Download do Livro
- Você pode baixar gratuitamente o capítulo completo contendo a explicação detalhada do projeto neste link:
  ![EbooK Projetos com Arduino - Jogo da Memória](https://drive.google.com/file/d/1Z8rtr-rhby-Xf5437nJ2UBeoKgn5cq_g/view?usp=drive_link)
- Ou diretamente em nosso repositório do GitHub:
[eBook-Projetos-Com-Arduino-Jogo-Da-Memoria.pdf](https://github.com/user-attachments/files/21204418/eBook-Projetos-Com-Arduino-Jogo-Da-Memoria.pdf)

## Licença

Este projeto está licenciado sob a Licença MIT.

## Créditos

Desenvolvido como parte do conteúdo do livro “Robótica Educacional com Arduino – Jogos Interativos na Prática”. Projeto idealizado para facilitar a aprendizagem por meio da integração entre software e hardware.

