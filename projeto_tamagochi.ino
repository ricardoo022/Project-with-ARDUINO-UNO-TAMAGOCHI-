int buttonPin_dormir=4;
int buttonPin_brincar=3;
int buttonPin_comer=2;
int ledPin_vermelho=13;
int ledPin_amarelo=12;
int ledPin_verde=11;
int PinLDR=A0;
unsigned long tempo_verde=0;
unsigned long tempo_amarelo=0;
unsigned long tempo_vermelho=0;
long randNumber;
unsigned long tempo_dormir;

float media=0;
int valorADC=0;
int pontuacao;
int vetor[6];
unsigned long contador;
int count;
unsigned long tempo_anterior;

int buttonState1= LOW;
int lastButtonState1 = LOW;

int buttonState2=LOW;
int lastButtonState2=LOW; 

int buttonState3=LOW;
int lastButtonState3=LOW;

long lastDebounceTime = 0;  
long debounceDelay = 50;    

void pin_mode(int intervalo,int intervalo2, String funcao){
  for(int i=intervalo ;i<=intervalo2;i++){                    // pin mode vai variar com a string que escrever quando chamo a funcao
    if (funcao=="INPUT_PULLUP"){
  		pinMode(i,INPUT_PULLUP);
    }  
    else if(funcao=="OUTPUT"){
      	pinMode(i,OUTPUT);
    }
  }
}  
 

float media_f() {
  float soma = 0;                      //se a variavel count  for 6 percorro o array e vou incrementando os respeitvos numeros na variavel soma e depois divido por 6 para fazer media
  if (count == 6) {  
    for (int i = 0; i < 6; i++) {
      soma += vetor[i];
    }
    float media = soma / 6;
   
    return(media);
  }
}

  
  
  

void desligar_leds(){
  for(int pin=11;pin<=13;pin++){     //percorro os pins dos leds desligando os
  	digitalWrite(pin,LOW);  
  }

}

int penalizacao(unsigned long tempo){
  	
  if((millis()-tempo)>=60000UL && millis()-tempo!=0){    //se a diferenca entre o tempo em que carrego nos respetivos botoes(tempo atual) e o tempo que guardei quando os leds acenderam for maior que 1min, vai somar 5 à pontuacao a cada minuto completo que passe adiciono mais 5, se a diferenca tiver entre 0 e os 15s retiro 5 pontos
    contador=int((millis()-tempo)/60000UL);
    pontuacao+=5*contador;

  }
  else if((millis()-tempo)<=15000 && pontuacao>0){
    pontuacao-=5;

  }
  if(pontuacao>25){
    Serial.println("Tamagochi morreu");

  }

  return pontuacao; 
}







void setup() {
  Serial.begin(9600);
  pin_mode(11,13,"OUTPUT");   //pinMode 
  pin_mode(2,4,"INPUT_PULLUP");
  pinMode(PinLDR,INPUT);
  
  tempo_dormir=0;
  pontuacao=0;
  randomSeed(analogRead(0)); 
  randNumber=random(-60000,60000); // dá um numero aleatorio no intervalo de +-60s

}

  


void loop() {
	if (pontuacao <= 25) {     // se a pontuacao for <=25 executa o codigo se nao vai estar a executar sempre a funcar desligar_leds
    if (tempo_dormir==0) {   

      if (millis() % 60000UL == 0 && millis() >1 && millis()!=tempo_anterior) {
        tempo_anterior=millis();
        Serial.print("Pontuação:");
        Serial.println(pontuacao);
        valorADC = analogRead(A0);
        vetor[count] = valorADC;
        count++;
      }

      if (count >= sizeof(vetor) / sizeof(int)) {
        media_f();
        count = 0;

      }


      if (millis() % (78000UL + randNumber) == 0 && millis() != 0 && digitalRead(ledPin_verde)==LOW) {   //led comer   // quando os leds acenderem guardo o tempo numa variavel
        digitalWrite(ledPin_verde, HIGH);
        tempo_verde = millis();
      }

      if (millis() % (60000UL + randNumber) == 0 && millis() != 0 &&  digitalRead(ledPin_amarelo)==LOW) {  // LED atencao
        digitalWrite(ledPin_amarelo, HIGH);
        tempo_amarelo = millis();
      }

      if ((millis() % (198000UL + randNumber) == 0 && millis() != 0 &&  digitalRead(ledPin_vermelho)==LOW) || media > (1024 * 2 / 3)) { //led dormir
        digitalWrite(ledPin_vermelho, HIGH);
        tempo_vermelho = millis();
      }


      int reading1 = !digitalRead(buttonPin_dormir);  //debounce botao1 dormir

      if (reading1 != lastButtonState1) {
        lastDebounceTime = millis();
      }

      if ((millis() - lastDebounceTime) > debounceDelay) {
        if (reading1 != buttonState1) {
          buttonState1 = reading1;
          if (digitalRead(ledPin_vermelho) == HIGH) {
            if (reading1 == HIGH) {                    //funcao penalizacao é executada quando carrego nos respetivos botoes
              penalizacao(tempo_vermelho);    

              tempo_dormir = millis();                 
              if ((millis() - tempo_dormir) == 0) {  
                if(pontuacao<=25){                          
                  Serial.println("Tamagochi a dormir");
                  desligar_leds();
                }
              }

            }
          }
        }
      }

      lastButtonState1 = reading1;


      int reading2 = !digitalRead(buttonPin_brincar);  //debounce botao brincar

      if (reading2 != lastButtonState2) {
        lastDebounceTime = millis();
      }

      if ((millis() - lastDebounceTime) > debounceDelay) {
        if (reading2 != buttonState2) {
          buttonState2 = reading2;
          if (digitalRead(ledPin_amarelo) == HIGH) {
            if (reading2 == HIGH) {
              penalizacao(tempo_amarelo);

              digitalWrite(ledPin_amarelo, LOW);
            }
          }
        }
      }
      lastButtonState2 = reading2;

      int reading3 = !digitalRead(buttonPin_comer);  //debounce botao comer

      if (reading3 != lastButtonState3) {
        lastDebounceTime = millis();
      }

      if ((millis() - lastDebounceTime) > debounceDelay) {
        if (reading3 != buttonState3) {
          buttonState3 = reading3;
          if (digitalRead(ledPin_verde) == HIGH) {
            if (reading3 == HIGH) {
              penalizacao(tempo_verde);  

              digitalWrite(ledPin_verde, LOW);
            }
          }
        }
      }
      lastButtonState3 = reading3;

    }


    else {                     
      desligar_leds();                           //o tempo_dormir !=0 então o programa vai ler apenas a funcar desligar_leds até passar o tempo para acordar, quando acordar volto a igualar a variavel tempo_dormir a 0 para o programa voltar a executar o código todo
      if (millis() - tempo_dormir == 96000UL) {
        Serial.println("Tamagochi a acordar");
        tempo_dormir = 0;
      }
    }


  }

  else {               //a pontuacao é >25 então o programa só vai executar a funcar desligar_leds
    desligar_leds();
  }
}


