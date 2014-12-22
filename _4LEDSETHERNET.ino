#include <SPI.h>  
#include <Ethernet.h>  
#include <Wire.h>
#include "rgb_lcd.h"
#include <math.h>
rgb_lcd lcd;
 
byte mac[] = { 0x98, 0x4F, 0xEE, 0x01, 0x86, 0x6D };
IPAddress ip(169,254,1,189); 
EthernetServer server(80);
float  temperature;
float resistance;
int B=3975; 
int led1=6; 
int led2=7;
int led3=8; 
int led4=9; 
String estado1="OFF";
String estado2="OFF"; 
String estado3="OFF"; 
String estado4="OFF"; 
 EthernetClient client;

void setup()
{
  Serial.begin(9600);
 lcd.begin(16, 2);

  Ethernet.begin(mac, ip);
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
 
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(led3,OUTPUT);
  pinMode(led4,OUTPUT);
}
 
void loop()
{
  int temp=analogRead(A1);
  resistance=(float)(1023-temp)*10000/temp;
  temperature=1/(log(resistance/10000)/B+1/298.15)-273.15;
  client  = server.available(); 
  if (client) {
    Serial.println("new client");
    boolean currentLineIsBlank = true; 
    String cadena=""; 
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        cadena.concat(c);
         int posicion=cadena.indexOf("LED="); 
 
          if(cadena.substring(posicion)=="LED=ON1")
          {
            encenderLed(1);           
          }
          if(cadena.substring(posicion)=="LED=OFF1")
          {
            apagarLed(1);
          }
           if(cadena.substring(posicion)=="LED=ON2")
          {
             encenderLed(2);  
          }
          if(cadena.substring(posicion)=="LED=OFF2")
          {
            apagarLed(2);
          }
           if(cadena.substring(posicion)=="LED=ON3")
          {
             encenderLed(3);  
          }
          if(cadena.substring(posicion)=="LED=OFF3")
          {
            apagarLed(3);
          }
           if(cadena.substring(posicion)=="LED=ON4")
          {
            encenderLed(4);  
          }
          if(cadena.substring(posicion)=="LED=OFF4")
          {
            apagarLed(4);
          }
           if(cadena.substring(posicion)=="LED=ENCENDER")
          {
           
           encenderLed(4); 
              encenderLed(3); 
             encenderLed(2); 
           encenderLed(1); 
            }
            
            if(cadena.substring(posicion)=="LED=APAGAR")
          {
              apagarLed(4);
             apagarLed(3);
            apagarLed(2);
             apagarLed(1);
            
          }
 
       
        if (c == '\n' && currentLineIsBlank) {
 
            
            
           
           mostrarpagina();
            break;
        }
        if (c == '\n') {
          currentLineIsBlank = true;
        }
        else if (c != '\r') {
          currentLineIsBlank = false;
        }
      }
    }
   
    delay(1);
    client.stop();
  }
}



void encenderLed(int x){
  if(x==4){
   digitalWrite(led4,HIGH);
   estado4="ON";
  }
  if(x==3){
   digitalWrite(led3,HIGH);
   estado3="ON";
  }
   if(x==2){
   digitalWrite(led2,HIGH);
   estado2="ON";
  }
  if (x==1){
   digitalWrite(led1,HIGH);
   estado1="ON";
  }
}

void apagarLed(int x){
  if(x==4){
   digitalWrite(led4,LOW);
   estado4="OFF";
  }
  if(x==3){
   digitalWrite(led3,LOW);
   estado3="OFF";
  }
   if(x==2){
   digitalWrite(led2,LOW);
   estado2="OFF";
  }
  if (x==1){
   digitalWrite(led1,LOW);
   estado1="OFF";
  }
}



void mostrarpagina(){
  client.println("HTTP/1.1 200 OK");
            client.println("Content-Type: text/html");
            client.println();
 
   client.println("<html>");
            
 client.println("<body bgcolor= '#ffdfef'>; background:"/");
  client.println("<meta http-equiv='refresh' content='5'>");
 client.println("<h1 align='center'>JOSE MANUEL CALAHORRO GOMEZ</h1><h3 align='center'>LED controlado por Intel Galileo</h3>");
 client.println("<div style='position:absolute;left: 810px;top: 150px;'>");
 client.println("<h3>Led 1</h3>");
 client.println("<button onClick=location.href='./?LED=ON1\' style='margin:auto;background-color: #84B1FF;color: snow;padding: 10px;border: 1px solid #3F7CFF;width:65px;'>ON");
 client.println("</button>");
 client.println("<button onClick=location.href='./?LED=OFF1\' style='margin:auto;background-color: #84B1FF;color: snow;padding: 10px;border: 1px solid #3F7CFF;width:65px;'>OFF");
 client.println("</button>");
 client.println("<br /><br />");
 client.println("<b>LED = ");
 client.print(estado1);
 client.println("</div>");
 client.println("<div style='position:absolute;left: 1010px;top: 150px;'>");
 client.println("<h3>Led 2</h3>");
 client.println("<button onClick=location.href='./?LED=ON2\' style='margin:auto;background-color: #84B1FF;color: snow;padding: 10px;border: 1px solid #3F7CFF;width:65px;'>ON");
 client.println("</button>");
 client.println("<button onClick=location.href='./?LED=OFF2\' style='margin:auto;background-color: #84B1FF;color: snow;padding: 10px;border: 1px solid #3F7CFF;width:65px;'>OFF");
 client.println("</button>");
 client.println("<br /><br />");
 client.println("<b>LED =" );
 client.print(estado2);
 client.println("</div>");
 client.println("<div style='position:absolute;left: 810px;top: 350px;'>");
 client.println("<h3>Led 3</h3>");
 client.println("<button onClick=location.href='./?LED=ON3\' style='margin:auto;background-color: #84B1FF;color: snow;padding: 10px;border: 1px solid #3F7CFF;width:65px;'>ON");
 client.println("</button>");
 client.println("<button onClick=location.href='./?LED=OFF3\' style='margin:auto;background-color: #84B1FF;color: snow;padding: 10px;border: 1px solid #3F7CFF;width:65px;'>OFF");
 client.println("</button>");
 client.println("<br /><br />");
 client.println("<b>LED = ");
 client.print(estado3);
 client.println("</div>");
 client.println("<div style='position:absolute;	left: 1010px;top: 350px;'>");
 client.println("<h3>Led 4</h3>");
 client.println("<button onClick=location.href='./?LED=ON4\' style='margin:auto;background-color: #84B1FF;color: snow;padding: 10px;border: 1px solid #3F7CFF;width:65px;'>ON");
 client.println("</button>");
 client.println("<button onClick=location.href='./?LED=OFF4\' style='margin:auto;background-color: #84B1FF;color: snow;padding: 10px;border: 1px solid #3F7CFF;width:65px;'>OFF");
 client.println("</button>");
 client.println("<br /><br />");
 client.println("<b>LED = ");
 client.print(estado4);
 client.println("</div>");
 client.println(" <div style='position:absolute;left: 1010px;top: 550px;'>");
 client.println("<h3>Encender todos</h3>");
 client.println("<button onClick=location.href='./?LED=ENCENDER\' style='margin:auto;background-color: #84B1FF;color: snow;padding: 10px;border: 1px solid #3F7CFF;width:180px;'>ENCENCER TODOS");
 client.println("<br /><br />");	
 client.println("</div>");
  client.println(" <div style='position:absolute;left: 810px;top: 550px;'>");
 client.println("<h3>Apagar todos</h3>");
 client.println("<button onClick=location.href='./?LED=APAGAR\' style='margin:auto;background-color: #84B1FF;color: snow;padding: 10px;border: 1px solid #3F7CFF;width:180px;'>APAGAR TODOS");
 client.println("<br /><br />");	
 client.println("</div>");
 client.println("<div style='position:absolute;left: 510px;top: 150px;'>");
 client.println("<h3>Temperatura</h3>");
 client.println("<br /><br />");
 client.print(temperature);
 client.println(" grados");
 client.println("</div>");
 client.println("</b><br />");
 client.println("</b></body>");
 client.println("</html>");
 }
