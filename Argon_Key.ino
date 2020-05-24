// This #include statement was automatically added by the Particle IDE.
#include <MQTT.h>

#include "MQTT/MQTT.h"
#include "MQTT/MQTT.h"

int led = D6;
//int button = D4;
int erButton = D3;
bool pressed = false;

byte server[] = { 192,168,0,15 };//the IP of broker
void callback(char* topic, byte* payload, unsigned int length);
void alcoholReact(const char *event, const char *data);
MQTT client(server, 1883, callback);


void callback(char* topic, byte* payload, unsigned int length) {
    char p[length + 1];
    memcpy(p, payload, length);
    p[length] = NULL;

    if (!strcmp(p, "1"))
        digitalWrite(led, HIGH);
    else if (!strcmp(p, "0"))
        digitalWrite(led, LOW);
    delay(1000);
}



void alcoholReact(const char *event, const char *data){
    if(strcmp(data, "drunk") == 0){
        digitalWrite(led, LOW);
        delay(1000);
        
    }
    
    else if(strcmp(data, "normal") == 0){
        digitalWrite(led, HIGH);
        delay(1000);
        digitalWrite(led, LOW);
        
    }
    
    else if(strcmp(data, "Blowing needed")==0){
        digitalWrite(led, LOW);
        delay(1000);
    }
}   



void setup() {
    
    pinMode(led, OUTPUT);
    //pinMode(button, INPUT);
    pinMode(erButton, INPUT_PULLUP);
    
    bool pressed = false;
    
    //Particle.publish("Buzzer_state","off");
    Particle.subscribe("Alcohol_Stage", alcoholReact);
    Particle.function("led", ledToggle);
    
    client.connect("192.168.0.15");
    if (client.isConnected()){
        client.subscribe("Testing");
    }
    
}

void loop() {
    
    
    if(client.isConnected()){
        client.loop();
        
    }
    
    if(digitalRead(erButton) == 1)
    {
        if(pressed == true)
            return;
            
        pressed = true;
        
        Particle.publish("Buzzer_state","on");
        Particle.publish("Er_Button", "Open the door");
        delay(30);
    }
    
    else if(digitalRead(erButton) == 0){
        
        if(pressed == false)
            return;
            
        pressed = false;
        
        Particle.publish("Buzzer_state", "off");
        delay(30);
    }
    
}    

int ledToggle(String command){
    if (command == "on"){
        digitalWrite(led,HIGH);
        delay(1000);
        digitalWrite(led,LOW);
        delay(1000);
        
    }
    else if(command == "off"){
        digitalWrite(led,LOW);
        delay(1000);
    }
}
