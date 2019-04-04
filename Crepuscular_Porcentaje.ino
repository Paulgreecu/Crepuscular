#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_Address 0x3C
Adafruit_SSD1306 oled(1);

int buttonState[]={0,0};

void setup() {
  pinMode(3,OUTPUT);
  pinMode(13,OUTPUT);
  pinMode(8,INPUT);
  pinMode(5,INPUT);
  Serial.begin(9600);
  oled.begin(SSD1306_SWITCHCAPVCC, OLED_Address);
}

void loop() {
  
  int porcentaje=map(analogRead(0), 0,1023,0,100);
  int pact=map(analogRead(1), 0,1023,0,100);
  
  oled.clearDisplay();
  oled.setTextColor(WHITE);
  oled.setTextSize(2);
  oled.setCursor(0,0);
  oled.drawFastHLine(0,15,128,WHITE);
  oled.drawFastHLine(0,16,128,WHITE);

  cambiarValorBoton(8,buttonState[0]);
 
  if(buttonState[0]==0){
    oled.println("Automatico");
    oled.setCursor(15,22);
    if(porcentaje<pact){
      Encender();
    }else{
      Apagar();
    }
  }else{
    oled.println("  Manual");
    oled.setCursor(15,22);
    cambiarValorBoton(5,buttonState[1]);
    if(buttonState[1]){
      Encender();
    }else{
      Apagar();
    }
  }
  oled.setCursor(0,45);
  oled.print(porcentaje);
  oled.print("% - ");
  oled.print(pact);
  oled.print("%");
  oled.display();
  delay(50);
}

void Encender(){
  digitalWrite(13, HIGH);
  digitalWrite(3, HIGH);
  oled.println("Encendido");
  oled.fillCircle(5,30,5,WHITE);
}

void Apagar(){
  digitalWrite(13, LOW);
  digitalWrite(3, LOW);
  oled.println("Apagado");
  oled.drawCircle(5,30,5,WHITE);
}

void cambiarValorBoton(int b, int &bState){
  if(digitalRead(b)){
    if(bState==1){bState=0;}
    else{bState=1;}
  }
}
