const int numParams = 5;
char recebido[numParams];
bool ready = false;
const int pinosXY[4][4] = {2,3,4,5,6,7,8,9,10,11,12,13,A0,A1,A2,A3};
const int pinosZ[4] = {A4,A5,A6,A7};
void setup() {
    Serial.begin(9600);
}

void loop() {
    receber();
    acendeLeds();
}

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

void acendeLeds() {
    if (ready == true) {
        Serial.println(recebido[0]);
        Serial.println(recebido[1]);
        Serial.println(recebido[2]);
        Serial.println(recebido[3]);
        Serial.print("----------\n");
        int x = recebido[1] - '0';
        int y = recebido[2] - '0';
        int z = recebido[3] - '0';
        
        switch(recebido[0]) {
          case 'a':
            Serial.print("----------\n");
            Serial.println(x);
            Serial.println(y);
            Serial.println(z);
            Serial.print("----------\n");
            Serial.println(pinosXY[--x][--y]);
            Serial.println(pinosZ[--z]);
            
            // digitalWrite(pinosXY[x][y], LOW);
            // digitalWrite(pinosZ[z], HIGH);
            break;          
        }
        ready = false;
    }
}


















