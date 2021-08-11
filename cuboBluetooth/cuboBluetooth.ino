// Definições iniciais
const int numParams = 5;
char recebido[numParams];
bool ready = false;
const int pinosXY[4][4] = {2,3,4,5,6,7,8,9,10,11,12,13,A0,A1,A2,A3};
const int pinosZ[2] = {A4,A5};
int x, y, z;

// Define os pinos, inicia o Serial e realiza um teste
void setup() {
    Serial.begin(9600);
    for (int i = 2; i<=18; i++) {
      pinMode(i, OUTPUT);
      digitalWrite(i, HIGH);
    }
    pinMode(pinosZ[0], OUTPUT);
    pinMode(pinosZ[1], OUTPUT);
    acendeZ(0);
    testa(50);
}

void loop() {
  receber();
  acendeLeds();
}

// Recebe e armazena informações atraves do Serial
void receber() {
    static bool recebendo = false;
    static int i = 0;
    char inic = '<';
    char fim = '>';
    char data;
    while (Serial.available() > 0 && ready == false) {
        data = Serial.read();
        if (recebendo == true) {
            if (data != fim) {
                recebido[i] = data;
                i++;
                if (i >= numParams) {
                    i = numParams - 1;
                }
            }
            else {
                recebido[i] = '\0';
                recebendo = false;
                i = 0;
                ready = true;
            }
        }
        else if (data == inic) {
            recebendo = true;
        }
    }
}

// Comanda o cubo dependendo do que foi obtido na função receber()
void acendeLeds() {
    if (ready == true) {
        Serial.println(recebido[0]);
        Serial.println(recebido[1]);
        Serial.println(recebido[2]);
        Serial.println(recebido[3]);
        Serial.print("----------\n");
        x = recebido[1] - '0';
        y = recebido[2] - '0';
        z = recebido[3] - '0';
        
        switch(recebido[0]) {
          case 'a':
            Serial.print("----------\n");
            Serial.println(x);
            Serial.println(y);
            Serial.println(z);
            Serial.print("----------\n");
            Serial.println(pinosXY[--x][--y]);
            Serial.println(pinosZ[--z]);
            
            digitalWrite(pinosXY[x][y], LOW);
            acendeZ(z);
            delay(5000);
            digitalWrite(pinosXY[x][y], HIGH);
            acendeZ(0);
            break;
          case 't':
            int tmp = (x*100) + (y*10) + (z);
            Serial.println(z+1);
            testa(tmp);
            break;
        }
        ready = false;
    }
}

// Acende todos os leds sequencialmente
void testa (int tmp) {
  for (int z = 0; z<=3; z++) {
    for (int x = 0; x<=3; x++) {
      for (int y = 0; y<=3; y++) {
        Serial.println("x - ");
        Serial.println(x);
        Serial.println("y - ");
        Serial.println(y);
        Serial.println("z - ");
        Serial.println(z);
        Serial.println("PinosXY - ");
        Serial.println(pinosXY[x][y]);
        Serial.println("PinosZ - ");
        Serial.println(pinosZ[z]);
        Serial.print("----------\n");
        digitalWrite(pinosXY[x][y], LOW);
        acendeZ(z);
        delay(tmp);
        digitalWrite(pinosXY[x][y], HIGH);
        acendeZ(0);
      }
    }
  }
}

// Função para interagir com o demultiplexador
void acendeZ(int z) {
  switch (++z) {
    case 1:
      digitalWrite(pinosZ[0], LOW);
      digitalWrite(pinosZ[1], LOW);
      break;
    case 2:
      digitalWrite(pinosZ[0], HIGH);
      digitalWrite(pinosZ[1], LOW);
      break;
    case 3:
      digitalWrite(pinosZ[0], LOW);
      digitalWrite(pinosZ[1], HIGH);
      break;
    case 4:
      digitalWrite(pinosZ[0], HIGH);
      digitalWrite(pinosZ[1], HIGH);
      break;
  }
}
