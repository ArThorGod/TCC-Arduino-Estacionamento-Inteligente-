// Programa : Controle de vagas de estacionamento com o HC-SR04  
// Autor : Arduino e Cia  
   
//Inicializa as bibliotecas do sensor Ultrasonico e do Display  
#include <NewPing.h>  
#include <LiquidCrystal.h>
#include <Servo.h>  
   
#define SONAR_NUM   1 // Define o numero de sensores  
#define MAX_DISTANCE 10 // Distancia maxima  

#define echoPin A1 //Pino ECHO do sensor no pino analógica A1
#define trigPin A0 //Pino TRIG do sensor no pino analógica A0

#define TRIGGER_PIN  10 // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     13 // Arduino pin tied to echo pin on the ultrasonic sensor.

// Milisegundos de intervalo entre medicoes (29ms e o tempo mínimo para
// evitar conflito entre os sensores)  
#define PING_INTERVAL 33
   
// Armazena a quantidade de vezes que a medicao deve ocorrer,para cada sensor  
unsigned long pingTimer[SONAR_NUM];

unsigned int cm[SONAR_NUM];     // Armazena o numero de medicoes  
uint8_t currentSensor = 0;     // Armazena o sensor que esta ativo  
   
int Pinoled1Verm = 20;  //Pino led1 - Vermelho  
int Pinoled1Verde = 19; //Pino led1 - Verde  
int Pinoled2Verm = 18;  //Pino led2 - Vermelho  
int Pinoled2Verde = 17; //Pino led2 - Verde  
int vagaslivres = 2;   //Contador de vagas livres  
int vagasocupadas = 0;  //Contador de vagas ocupadas  
int sensor1 = 0;    //Contador de vagas no sensor1  
int sensor2 = 0;     //Contador de vagas no sensor2  

long duracao;
long HR_dist=0;
int minimumRange=5;
int maximumRange=200;
   
//Define os pinos que serao ligados ao LCD  
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
   
NewPing sonar[SONAR_NUM] =  
{  
  // Armazena informacoes sobre a pinagem dos sensores  
  // Pino trigger, echo e distancia máxima, para cada sensor  
  NewPing(7, 6, MAX_DISTANCE),  
};  

NewPing sensor(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

//Define os motores
Servo myservo1;
Servo myservo2;

   
void setup()  
{  
  Serial.begin(9600);  
  lcd.begin(16,2); //Inicializa LCD  
  lcd.clear();   //Limpa o LCD  
  pingTimer[0] = millis() + 75;      //Primeira medicao começa com 75ms  
  //Define o tempo de inicializacao de cada sensor
  for (uint8_t i = 1; i < SONAR_NUM; i++)  
   pingTimer[i] = pingTimer[i - 1] + PING_INTERVAL;  
  pinMode(Pinoled1Verm, OUTPUT);  //Define o Pino vermelho do led1 como saida  
  pinMode(Pinoled1Verde, OUTPUT); //Define o Pino verde do led1 como saida  
  pinMode(Pinoled2Verm, OUTPUT);  //Define o Pino vermelho do led2 como saida  
  pinMode(Pinoled2Verde, OUTPUT); //Define o Pino verde do led2 como saida  
  myservo1.attach(8);
  myservo2.attach(9);
  pinMode(trigPin, OUTPUT); //define o pino TRIG como saída
  pinMode(echoPin, INPUT); //define o pino ECHO como entrada
 }  
   
void loop()
{  
  // Loop entre todos os sensores
  for (uint8_t i = 0; i < SONAR_NUM; i++) {  
   if (millis() >= pingTimer[i]) {
    //Define o tempo que o proximo sensor sera acionado
    pingTimer[i] += PING_INTERVAL * SONAR_NUM;  
    // Ciclo do sensor completo  
    if (i == 0 && currentSensor == SONAR_NUM - 1) oneSensorCycle();
    // Reseta o timer antes de ler o proximo sensor  
    sonar[currentSensor].timer_stop();    
    // Número do sensor sendo acionado
    currentSensor = i;              
    // Se nao houver eco do sensor, seta a distância como zero  
    cm[currentSensor] = 0;          
    sonar[currentSensor].ping_timer(echoCheck);  
   }  
 }  
     
 //Calcula a quantidade de vagas disponiveis e ocupadas, e imprime no display  
 vagasocupadas = sensor1 + sensor2;  
 vagaslivres = 1 - vagasocupadas;  
 lcd.setCursor(0,0);  
 lcd.print("Vagas livres = ");  
 lcd.print(vagaslivres);  
 lcd.setCursor(0,1);  
 lcd.print("Vagas ocup. = ");  
 lcd.print(vagasocupadas);  

 Distancia(); //chama a função para medir a distância

  Serial.print("Ping: ");
  Serial.print(sensor.ping_cm()); // Send ping, get distance in cm and print result (0 = outside set distance range)
  Serial.println("cm");

  //SERVO-MOTOR 1
  if (sensor.ping_cm() >=5)
  {
    myservo1.write(0) ;
    delay(2000);
  }
  else if (sensor.ping_cm() < 5)
  {
    myservo1.write(90);
    delay(2000);
  }


}
 
   
void echoCheck() { //Se receber um sinal (eco), calcula a distancia  
  if (sonar[currentSensor].check_timer())  
   cm[currentSensor] = sonar[currentSensor].ping_result / US_ROUNDTRIP_CM;  
 }  
   
void oneSensorCycle() { // Ciclo de leitura do sensor  
  for (uint8_t i = 0; i < SONAR_NUM; i++) {  
   //Se for detectado objeto entre 0 e 50 cm do sensor1, acende o led1 vermelho
   if (cm[0] > 1 && cm[0] < 50)  
   {  
     digitalWrite(Pinoled1Verm, 1);  
     digitalWrite(Pinoled1Verde, 0);  
     sensor1 = 1; //Incrementa o número de vagas ocupadas na vaga1  
   }  
   else //Se não for detectado objeto no sensor 1, mantém o led1 verde aceso  
   {  
     digitalWrite(Pinoled1Verm, 0);  
     digitalWrite(Pinoled1Verde, 1);  
     sensor1 = 0; //Marca a vaga 1 como livre  
   }  
   
   //Se for detectado objeto entre 0 e 50 cm do sensor2, acende o led2 vermelho  
   if (cm[1] > 1 && cm[1] < 50)
   {  
     digitalWrite(Pinoled2Verm, 1);  
     digitalWrite(Pinoled2Verde, 0);  
     sensor2 = 1; //Incrementa o número de vagas ocupadas na vaga2  
   }  
   else //Se não for detectado objeto no sensor 2, mantém o led2 verde aceso  
   {  
     digitalWrite(Pinoled2Verm, 0);  
     digitalWrite(Pinoled2Verde, 1);  
     sensor2 = 0; //Marca a vaga 2 como livre  
   }  

   //Imprime os valores lidos no monitor serial, para fins de acompanhamento  
   Serial.print("Sensor : ");
   Serial.print(i);  
   Serial.print(" = ");  
   Serial.print(cm[i]);  
   Serial.print(" cm - ");  
  }  
  Serial.println();  
}  

void Distancia(){
  digitalWrite(trigPin, LOW); //não envia som
  delayMicroseconds(2);
  digitalWrite(trigPin,HIGH); //envia som
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW); //não envia o som e espera o retorno do som enviado
  duracao = pulseIn(echoPin,HIGH); //Captura a duração em tempo do retorno do som.
  HR_dist = duracao/56; //Calcula a distância
  Serial.println(HR_dist); //Exibe na Serial a distância

}
