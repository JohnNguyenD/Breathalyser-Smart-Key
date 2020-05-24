int AlcoPin = A1;
float period = 12*3600

void setup() {
    pinMode(AlcoPin, OUTPUT);
    digitalWrite(AlcoPin, LOW);
    
    
}

void loop() {
    
    float sensor_volt;
    float RS_gas;
    float ratio;
    int sensorValue = analogRead(A1);
    
    sensor_volt = (float)sensorValue/1024*5.0;
    RS_gas = sensor_volt/(5 - sensor_volt);
    
    if (RS_gas < 0.09){
        Particle.publish("Alcohol_Stage", "Blowing needed");
        delay(5000);
    }
        
        
    if(RS_gas >= 1.0){
        Particle.publish("Alcohol_Stage", "drunk");
        delay(period);
    }
        
    else if (RS_gas > 0.10 and RS_gas < 1.0){
        Particle.publish("Alcohol_Stage", "normal");
        delay(5000);
    }
}
