#include <Servo.h>
#include <Adafruit_LiquidCrystal.h>



int TRIG = 11;
int ECHO = 12;
int DURATION;
int DISTANCE;

Adafruit_LiquidCrystal lcd_1(0);
Servo myservo;


byte customChar[8] = {
  B00110,
  B01001,
  B01001,
  B00110,
  B00000,
  B00000,
  B00000,
  B00000
};

void setup() {
  myservo.attach(9);
  
  pinMode(A0, INPUT);
  pinMode (TRIG, OUTPUT);
  pinMode (ECHO, INPUT);
  Serial.begin(9600);
  lcd_1.begin(16, 2);
  lcd_1.createChar(0, customChar);
  lcd_1.home();
}

void loop() {
  lcd_1.setCursor(7,0);
  lcd_1.print("ALTURA: ");
  
  LECTURA_DISTANCIA();

  int val = analogRead(A0);
  float angulo = map(val, 0, 1023, 0, 89.9);
  
  myservo.write(angulo);
  
  float radianes = ((angulo * 3.1416) / 180);
  float TAN = tan(radianes) ;

  lcd_1.setCursor(0, 0);
  lcd_1.print(angulo);
  lcd_1.write(0);
  lcd_1.print(" ");

  lcd_1.setCursor(0,1);
  lcd_1.print(DISTANCE);
  lcd_1.print("cm");
  lcd_1.print(" ");
  
  float ALTURA = TAN * DISTANCE;    
  lcd_1.setCursor(7,1);
  lcd_1.print(ALTURA);
  lcd_1.print("cm");
  lcd_1.print(" ");
}

void LECTURA_DISTANCIA() {
  digitalWrite(TRIG, LOW);
  delay(25);
  digitalWrite(TRIG, HIGH);
  delay(25);
  digitalWrite(TRIG, LOW);

  DURATION = pulseIn(ECHO, HIGH);

  DISTANCE = DURATION * 0.034 / 2;
  delay(400);
}
 
