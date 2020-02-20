//per Definire il senso di marcia del motore
/*    direzione_motoreA |   direzione_motoreB  | Evento
    --------------------|----------------------|----------------------
           LOW          |        LOW           | fermo
           LOW          |        HIGH          | Movimento in un senso
           HIGH         |        LOW           | Movimento senso opposto
           HIGH         |        HIGH          | Fermo                     */


void driver_motore(int * pot, double * Out) {
int  potenza=*pot;
int correzione=*Out;
int pwmSX = 0;         //  power rimappato in scala da 0 a 255 per l' output
int pwmDX = 0;         //  power rimappato in scala da 0 a 255 per l' output
int powerSX = 0;        // potenza generale pwmSX
int powerDX = 0;        // potenza generale pwmDX

/*
 * 
 * gira piu' veloce il motore destro
 * 
 * 
 */
  if (potenza == 0) {
    
    
    digitalWrite(direzione_motoreSXA, LOW);
    digitalWrite(direzione_motoreSXB, LOW);
    digitalWrite(direzione_motoreDXA, LOW);
    digitalWrite(direzione_motoreDXB, LOW);
    pwmSX=0;
    pwmDX=0;
    powerSX=0;
    powerDX=0;
    
  }
  else if (potenza > 0) {
    
    if (debug_pwm) {
      Serial.print("D:");
    Serial.print("avanti ");
    Serial.println(correzione);
    }
    
    digitalWrite(direzione_motoreSXA, LOW);
    digitalWrite(direzione_motoreSXB, HIGH);
    digitalWrite(direzione_motoreDXA, LOW);
    digitalWrite(direzione_motoreDXB, HIGH);

    powerSX=potenza+correzione;
    
    powerDX=potenza;
    
    
    powerSX=constrain(powerSX,0,255);
    powerDX=constrain(powerDX,0,255);
    //map(value, fromLow, fromHigh, toLow, toHigh)
    pwmSX = map(powerSX, 0, 255, 80, 255);
    pwmDX = map(powerDX, 0, 255, 80, 255);
    
  }
  else {
    analogWrite(pwm_motor_SX, pwmSX);
    analogWrite(pwm_motor_DX, pwmDX);

    if (debug_pwm) {
      Serial.print("D:");
    Serial.print("indietro ");
    }
    
    digitalWrite(direzione_motoreSXA, HIGH);
    digitalWrite(direzione_motoreSXB, LOW);
    digitalWrite(direzione_motoreDXA, HIGH);
    digitalWrite(direzione_motoreDXB, LOW);

     powerSX=potenza+correzione;
     
    powerDX=potenza;
    
    powerSX=constrain(powerSX,-255,0);
    powerDX=constrain(powerDX,-255,0);
    
    //map(value, fromLow, fromHigh, toLow, toHigh)
    pwmSX = map(powerSX, -255, 0, 255, 80);
    pwmDX = map(powerDX, -255, 0, 255, 80);
    

  }
  
  if (debug_pwm and potenza !=0) {
    Serial.print("potenza ");
    Serial.print(potenza);
    Serial.print(" correzione ");
    Serial.print(correzione);
    Serial.print(" powerSX ");
    Serial.print(powerSX);
    Serial.print(" powerDX ");
    Serial.print(powerDX);
    Serial.print(" pwm value sx ");
    Serial.print(pwmSX);
    Serial.print(" dx ");
    Serial.println(pwmDX);
  }
  
  analogWrite(pwm_motor_SX, pwmSX);
  analogWrite(pwm_motor_DX, pwmDX);

} 
