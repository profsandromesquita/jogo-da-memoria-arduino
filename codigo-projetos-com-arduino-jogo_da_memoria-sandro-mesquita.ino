/*==========================================================
   JOGO DA MEMÓRIA  –  Versão final (LCD I²C + pinos revistos)
   ----------------------------------------------------------
   Mapping físico (ver esquema de fios coloridos):
       LEDs ……  VERM = 10 | AMAR =  8 | VERD =  6 | AZUL = 4
       Botões … INIC = 12 | VERM = 11 | AMAR =  9 | VERD = 7 | AZUL = 5
       Buzzer ………………………………………… 3
       Pot.     ………………………………………… A0
       LCD I²C  ………………………………………… SDA = A4  SCL = A5   (addr 0x27)
==========================================================*/

/*==========================================================
  PROJETO: Jogo da Memória com Arduino
  SÉRIE: Robótica e Programação Maker
  MATERIAL DE APOIO: eBook "Projetos com Arduino – Jogo da Memória"
  AUTOR: Prof. Sandro Mesquita
  INSTITUIÇÃO: Instituto de Tecnologia e Inteligência Artificial (ITIA)
  VERSÃO: Final – com LCD I²C e pinagem revisada
  DATA: Julho de 2025

  DESCRIÇÃO:
  Este código implementa um jogo da memória utilizando Arduino Uno, 
  LEDs, botões, buzzer, potenciômetro e um display LCD 16x2 com interface I²C.
  O nível de dificuldade é ajustado via potenciômetro, e o jogo consiste em 
  memorizar e reproduzir uma sequência de LEDs acesos aleatoriamente.

  LICENÇA: Uso educacional livre, com créditos mantidos ao autor.

  REPOSITÓRIO OFICIAL:
  https://github.com/profsandromesquita/jogo-da-memoria-arduino
==========================================================*/

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// ---------- PINOS DE SAÍDA ----------
const int LED_VERM   = 10;
const int LED_AMAR   =  8;
const int LED_VERD   =  6;
const int LED_AZUL   =  4;
const int LEDs[4] = {LED_VERM, LED_AMAR, LED_VERD, LED_AZUL};

const int BUZZER = 3;

// ---------- PINOS DE ENTRADA ----------
const int BTN_START   = 12;   // Botão branco (Start/Reset)
const int BTN_VERM    = 11;
const int BTN_AMAR    =  9;
const int BTN_VERD    =  7;
const int BTN_AZUL    =  5;
const int BOTOES[4] = {BTN_VERM, BTN_AMAR, BTN_VERD, BTN_AZUL};

const int POT_NIVEL = A0;     // Potenciômetro (cursor fio ciano)

// ---------- LCD ----------
LiquidCrystal_I2C lcd(0x27, 16, 2);

// ---------- CONSTANTES ----------
const byte TAM_SEQ = 5;
byte sequencia[TAM_SEQ];             // Guarda sequência sorteada
const uint16_t intervalo[5] = {2000, 1600, 1200, 1000, 800};

// ------------------------------------------------------------
void setup() {
  // Configura pinos digitais
  for (byte i = 0; i < 4; i++) {
    pinMode(LEDs[i], OUTPUT);
    pinMode(BOTOES[i], INPUT_PULLUP);
  }
  pinMode(BTN_START, INPUT_PULLUP);
  pinMode(BUZZER, OUTPUT);

  // Inicia LCD
  lcd.init();
  lcd.backlight();

  // Mensagem de teste
  lcd.setCursor(0,0); lcd.print("JOGO DA MEMORIA");
  lcd.setCursor(0,1); lcd.print("TESTANDO PROJETO");
  piscaLeds(1, 200);
  beep(3, 100, 100);

  // Semente aleatória
  randomSeed(analogRead(A1));
}

void loop() {
  byte nivel = escolherNivel();   // 1) Potenciômetro + botão Start
  gerarSequencia();               // 2) Array aleatório
  exibirSequencia(nivel);         // 3) Mostra LEDs
  bool venceu = lerResposta();    // 4) Jogador responde
  mostrarResultado(venceu);       // 5) Feedback
}

// ==================== FUNÇÕES DE SUPORTE ===================

void piscaLeds(byte vezes, uint16_t tOn) {
  for (byte v = 0; v < vezes; v++) {
    for (byte i = 0; i < 4; i++) {
      digitalWrite(LEDs[i], HIGH);
      delay(tOn);
      digitalWrite(LEDs[i], LOW);
    }
  }
}

void beep(byte v, uint16_t tOn, uint16_t pausa) {
  for (byte i = 0; i < v; i++) {
    tone(BUZZER, 1000);        // 1 kHz
    delay(tOn);
    noTone(BUZZER);
    delay(pausa);
  }
}

byte escolherNivel() {
  byte niv = 1;
  lcd.clear();
  lcd.setCursor(0,0); lcd.print("PRESS BOTAO INIC");
  while (digitalRead(BTN_START) == HIGH) {
    byte novo = map(analogRead(POT_NIVEL),0,1023,1,5);
    if (novo != niv) {
      niv = novo;
      lcd.setCursor(0,1);
      lcd.print("NIVEL DO JOGO: ");
      lcd.print(niv);
      lcd.print(" ");           // apaga dígito antigo
    }
    delay(100);
  }
  beep(3, 80, 80);
  while (digitalRead(BTN_START) == LOW); // espera soltar
  delay(200);
  return niv;
}

void gerarSequencia() {
  for (byte i = 0; i < TAM_SEQ; i++)
    sequencia[i] = random(0,4);
}

void exibirSequencia(byte niv) {
  lcd.clear();
  lcd.setCursor(0,0); lcd.print("JOGO DA MEMORIA");
  lcd.setCursor(0,1); lcd.print("DECORE A SEQUENC");
  uint16_t passo = intervalo[niv-1];
  uint16_t tOn = passo/2, tOff = passo - tOn;
  delay(600);
  for (byte i = 0; i < TAM_SEQ; i++) {
    digitalWrite(LEDs[sequencia[i]], HIGH);
    delay(tOn);
    digitalWrite(LEDs[sequencia[i]], LOW);
    delay(tOff);
  }
  beep(3, 80, 80);
}

bool lerResposta() {
  lcd.clear();
  lcd.setCursor(0,0); lcd.print("JOGO DA MEMORIA");
  lcd.setCursor(0,1); lcd.print("INFORME A SEQUEN");
  for (byte p = 0; p < TAM_SEQ; p++) {
    int idx = aguardaBotao();
    beep(1, 60, 20);
    if (idx != sequencia[p]) return false;
  }
  return true;
}

int aguardaBotao() {
  while (true) {
    for (byte i = 0; i < 4; i++) {
      if (digitalRead(BOTOES[i]) == LOW) {
        while (digitalRead(BOTOES[i]) == LOW); // espera soltar
        delay(40); // debounce
        return i;
      }
    }
  }
}

void mostrarResultado(bool ok) {
  lcd.clear();
  if (ok) {
    lcd.setCursor(0,0); lcd.print("PARABENS JOGADOR");
    lcd.setCursor(0,1); lcd.print("VOCE ACERTOU   ");
  } else {
    lcd.setCursor(0,0); lcd.print("QUE PENA        ");
    lcd.setCursor(0,1); lcd.print("VOCE SE ENGANOU");
  }
  beep(3, 120, 120);
  delay(2500);
}