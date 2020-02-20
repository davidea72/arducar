/*
 * l' intento è quello di realizzare una macchinina comandata da un app sul telefono android
 * la macchinina deve andare avanti e indietro , destra e sinistra , deve fermarsi in automatico dopo un po che non riceve comandi
 * siccome non si trovano due motori che girino alla stessa velocità la macchinina tende sempre a sterzare da un lato
 * per correggere questo comportamento si è inserito il giroscopio GY-521 basato sull' mpu 6050
 * il giroscopio puo' esser utilizzato in modalità normale , o con l' ausilio della DMP interna , in tal caso
 * va utilizzato il pin dell' interrupt per segnalare ad arduino quando la dmp ha finito i calcoli e i dati sono pronti da leggere
 * anche in tale configurazione ho riscontrato che i primi 20 secondi circa la lettura non è stabile , quindi bisogna aspettare
 * circa 20 secondi affinchè la lettura si stabilizzi (con un errore inferiore a 0.05 gradi)
 * quindi ogni volta che la macchinina si ferma viene calcolato un nuovo offset in modo da calcolare sempre come rotta 0 gradi la direzione  
 * qualche istante prima della partenza
 * per far andare dritta la macchinina quindi , viene passato al PID la rotta attuale , quella voluta (come setpoit) e se ne ottiene il valore 
 * da passare ai motori come correzione (output)  , questo valore è calcolato in base ai 3 parametri Kp , Ki e Kd
 * infine viene effettuata una lettura della batteria , tale tensione è ricavata tramite un partitore resistivo da quella di alimentazione dai
 * supercondensatori , la lettura è riparametrizzata tra due valori che corrispondono a 7V - 0% e 11,7V 100%
 * 
 * l' app sul telefonino è stata creata tramite appinventor , del quale ho apprezzato la facilità d' uso ma ho anche trovato uno dei suoi 
 * limiti , non è possibile processare un grosso flusso dati dalla macchinina verso il telefonino , se mando tutti i dati di debug
 * sull' app vanno accumulando ritardo, arrivando ad una decina di secondi di ritardo fino a bloccare a volte l' app
 * 
 * quindi per debuggare sono stato costretto ad utilizzare il portatile collegato in bluetoot alla macchinina con un emulatore terminale
 * quale minicom.
 * per facilitare il debug , le varie parti di debug sono attivabili e disattivabili a runtime , cosi' come anche i parametri K del pid sono
 * modificabili a runtime con step di 0.5
 * 
 * 
 */

bool debug_cmd = false;
bool debug_imbardata = false;
bool debug_batt = false;
bool debug_pwm = false;
bool debug_pid = false;
bool report_batteria = true;
#define direzione_motoreSXA  11 // D11
#define direzione_motoreSXB  12 // D12
#define direzione_motoreDXA  9 //D9
#define direzione_motoreDXB  10 //D10
#define pwm_motor_SX  6 //PWM D6// A4 SDA
#define pwm_motor_DX  3 //PWM D3
#define battery 0 // A0
#define UP  'U'         //comando per andare avanti o aumentare la velocita in avanti/ridurre quella in indietro
#define DOWN  'D'       //comando per andare indietro o aumentare la velocita indietro/ridurre quella in avanti
#define LEFT 'L'
#define RIGHT 'R'
#define debug_cmd_on 'a'
#define debug_cmd_off 'b'
#define debug_imbardata_on 'c'
#define debug_imbardata_off 'd'
#define debug_batt_on 'e'
#define debug_batt_off 'f'
#define debug_pwm_on 'g'
#define debug_pwm_off 'h'
#define debug_pid_on 'i'
#define debug_pid_off 'l'
#define report_batteria_on 'm'
#define report_batteria_off 'n'
#define Kp_add 'o'
#define Kp_sub 'p'
#define Ki_add 'q'
#define Ki_sub 'r'
#define Kd_add 's'
#define Kd_sub 't'

#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
#include <PID_v1.h>
#include "motore.h"

#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
#include "Wire.h"
#endif


MPU6050 mpu;

//variabili necessarie alla lettura del giroscopio

bool dmpReady = false;  // set true if DMP init was successful
uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
uint16_t fifoCount;     // count of all bytes currently in FIFO
uint8_t fifoBuffer[64]; // FIFO storage buffer
Quaternion q;           // [w, x, y, z]         quaternion container
VectorFloat gravity;    // [x, y, z]            gravity vector
float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector
float offsetX, offsetY, offsetZ;


//variabili necessarie al controllo PID
double Setpoint = 0, Output, imbardata = 0, imbardata_gradi, imbardata_netta, rotta;
double Kp = 3;
double Ki = 1.1;
double Kd = 20;


PID myPID(&rotta, &Output, &Setpoint, Kp, Ki, Kd, P_ON_E, DIRECT); 
/*
 * 
 *  P_ON_M specifies that Proportional on Measurement be used
 *  P_ON_E (Proportional on Error) is the default behavior 
 *  
 *  rotta: The variable we're trying to control (double)
 *  Output: The variable that will be adjusted by the pid (double) 
 *  Setpoint: The value we want to Input to maintain (double)
 *  
 *  Kp, Ki, Kd: Tuning Parameters. these affect how the pid will change the output. (double>=0)
 *  Direction: Either DIRECT or REVERSE. determines which direction the output will move when faced with a given error. DIRECT is most common.
 *  Kp: Determines how aggressively the PID reacts to the current amount of error (Proportional) (double >=0)
 *  Ki: Determines how aggressively the PID reacts to error over time (Integral) (double>=0)
 *  Kd: Determines how aggressively the PID reacts to the change in error (Derivative) (double>=0)
 *  
 */




// ================================================================
// ===               INTERRUPT DETECTION ROUTINE                ===
// ================================================================

volatile bool mpuInterrupt = false;     // indicates whether MPU interrupt pin has gone high
void dmpDataReady() {
  mpuInterrupt = true;
  //Serial.println("interrupt");

}

/*
 * 
 * lo schetch definisce i pin in testa direttamente come define
 * vengono utilizzati i seguenti pin 
 * direzione_motoreSXA  11 // D11
 * direzione_motoreSXB  12 // D12
 * direzione_motoreDXA  9 //D9
 * direzione_motoreDXB  10 //D10
 * pwm_motor_SX  6 //PWM D6// A4 SDA
 * pwm_motor_DX  3 //PWM D3
 * battery 0 // A0
 * 
 * tale sequenza è stata scelta cosi' anche in funzione del circuito stampato che ho realizzato
 * inoltre vengono utilizzati i pin
 * A5 SCL 
 * A4 SDL
 * per il dialoco I2C con giroscopio
 * 
 */


//definizione variabili

int sterzata = 0;
char received = "";     // variabile per ricezione da bluetooth
int potenza = 0;
int tensione;
char tensione_percentuale[2];
int every = 0;        //variabile usata per contare ogni quanti cicli mandare fuori dei dati , viene calcolato il modulo % in base a quanto volgiamo sia veloce
bool calibrated = false;  //utilizzata per bloccare il funzionamento della macchinina finche il giroscopio non si stabilizza
int cal_count = 500;      //quanti cicli dobbiamo aspettare prima di considerare stabilizzato il giroscopio
int cicle_from_start= 0;  //cicli (loop) dall' avvio
int ritardo = 30;         //tempo di attesa a fine loop
int flash_every = 30;     //ogni quanti cicli deve flashare il led
double milli, old_milli, tot_milli;   //variabili utilizzate per il debug



// ================================================================
// ===                      INITIAL SETUP                       ===
// ================================================================

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(direzione_motoreSXA, OUTPUT);
  pinMode(direzione_motoreSXB, OUTPUT);
  pinMode(pwm_motor_SX, OUTPUT);
  pinMode(direzione_motoreDXA, OUTPUT);
  pinMode(direzione_motoreDXB, OUTPUT);
  pinMode(pwm_motor_DX, OUTPUT);
  Serial.begin(115200);
  // join I2C bus (I2Cdev library doesn't do this automatically)
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
  Wire.begin();
  TWBR = 24; // 400kHz I2C clock (200kHz if CPU is 8MHz)
#elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
  Fastwire::setup(400, true);
#endif

  // initialize device
  mpu.initialize();


  // load and configure the DMP
  devStatus = mpu.dmpInitialize();

  // supply your own gyro offsets here, scaled for min sensitivity
  mpu.setXGyroOffset(0);
  mpu.setYGyroOffset(0);
  mpu.setZGyroOffset(0);
  mpu.setZAccelOffset(0); // 1688 factory default for my test chip


  // make sure it worked (returns 0 if so)
  if (devStatus == 0) {
    // turn on the DMP, now that it's ready
    mpu.setDMPEnabled(true);

    // enable Arduino interrupt detection
    attachInterrupt(0, dmpDataReady, RISING);
    mpuIntStatus = mpu.getIntStatus();

    // set our DMP Ready flag so the main loop() function knows it's okay to use it
    dmpReady = true;

    // get expected DMP packet size for later comparison
    packetSize = mpu.dmpGetFIFOPacketSize();
  }
  myPID.SetOutputLimits(-90, 90);
  myPID.SetSampleTime(20);
  myPID.SetMode(AUTOMATIC);

}



// ================================================================
// ===                    MAIN PROGRAM LOOP                     ===
// ================================================================

void loop() {

  // if programming failed, don't try to do anything
  if (!dmpReady) return;

  // wait for MPU interrupt or extra packet(s) available
  while (!mpuInterrupt && fifoCount < packetSize) {



  }


  if (Serial.available() > 0 )
  {
    received = Serial.read();
    //Serial.println(received);

  }



  //il comando di potenza non puo' eccedere il valore di 120 per lasciare spazio alla correzione

  switch (received) {
    case  UP:
      if ( potenza < 120) {
        potenza += 10;
        Serial.flush();
        if (debug_cmd) {

        }

      }
      break;

    case DOWN:
      if ( potenza > -120) {
        potenza -= 10;
        Serial.flush();
        if (debug_cmd) {
        }
        Serial.flush();
      }
      break;

    case LEFT:
      sterzata += 10;
      Serial.flush();
      break;
      
    case RIGHT:
      sterzata -= 5;
      Serial.flush();
      break;

    case debug_cmd_on:
      debug_cmd = true;
      Serial.println("debug comandi avviato");
      break;

    case debug_cmd_off:
      debug_cmd = false;
      Serial.println("debug comandi fermato");
      break;


    case debug_imbardata_on:
      debug_imbardata = true;
      Serial.println("debug imbardata avviato");
      break;

    case debug_imbardata_off:
      debug_imbardata = false;
      Serial.println("debug imbardata fermato");
      break;


    case debug_batt_on:
      debug_batt = true;
      Serial.println("debug batteria avviato");
      break;

    case debug_batt_off:
      debug_batt = false;
      Serial.println("debug batteria fermato");
      break;


    case debug_pwm_on:
      debug_pwm = true;
      Serial.println("debug pwm avviato");
      break;

    case debug_pwm_off:
      debug_pwm = false;
      Serial.println("debug pwm fermato");
      break;


    case debug_pid_on:
      debug_pid = true;
      Serial.println("debug pid avviato");
      break;

    case debug_pid_off:
      debug_pid = false;
      Serial.println("debug pid fermato");
      break;

    case report_batteria_on:
      report_batteria = true;
      Serial.println("report batteria avviato");
      break;

    case report_batteria_off:
      report_batteria = false;
      Serial.println("report batteria fermato");
      break;

    case Kp_add:
      Kp += 0.5;
      myPID.SetTunings(Kp, Ki, Kd);
      break;

    case Kp_sub:
      Kp -= 0.5;
      myPID.SetTunings(Kp, Ki, Kd);
      break;

    case Ki_add:
      Ki += 0.5;
      myPID.SetTunings(Kp, Ki, Kd);
      break;

    case Ki_sub:
      Ki -= 0.5;
      myPID.SetTunings(Kp, Ki, Kd);
      break;

    case Kd_add:
      Kd += 0.5;
      myPID.SetTunings(Kp, Ki, Kd);
      break;

    case Kd_sub:
      Kd -= 0.5;
      myPID.SetTunings(Kp, Ki, Kd);
      break;

    default:
      Serial.flush();

  }


  every += 1;
  if (potenza > 0 and every % 10 == 0) {
    potenza -= 1;
    every = 0;
  }

  if (potenza < 0 and every % 10 == 0) {
    potenza += 1;
    every = 0;
  }

  if (calibrated == true and potenza != 0) {
    myPID.Compute();
    if (debug_pid) {
      milli = millis();
      Serial.print("D:");
      Serial.print(milli - old_milli);

      old_milli = milli;
      tot_milli += old_milli;
      Serial.print(" ");
      Serial.print(old_milli);
      Serial.print("\tKp,Ki,Kd = ");
      Serial.print(Kp);
      Serial.print(",");
      Serial.print(Ki);
      Serial.print(",");
      Serial.print(Kd);
      Serial.print("\timbardata= ");
      Serial.print(imbardata);
      Serial.print("\tsterzata = ");
      Serial.print(sterzata);
      Serial.print("\t rotta= ");
      Serial.print(rotta);
      Serial.print(" valore output= ");
      Serial.println(Output);

    } else {
      tot_milli = 0;
    }

  }

  if (debug_imbardata and potenza != 0) {
    Serial.print("D:");
    Serial.print("imbardata_gradi = ");
    Serial.print(imbardata_gradi);
    Serial.print(" imbardata_netta = ");
    Serial.print(imbardata_netta);

    Serial.print("imbardata = ");
    Serial.print(imbardata);
    Serial.print(" output = ");
    Serial.println(Output);
  }

    if (calibrated == true) {
    driver_motore(&potenza, &Output);
  }

  if (every % 5 == 0) {


    lettura_batteria();
  }


  delay(ritardo);





  // reset interrupt flag and get INT_STATUS byte
  mpuInterrupt = false;
  mpuIntStatus = mpu.getIntStatus();

  // get current FIFO count
  fifoCount = mpu.getFIFOCount();

  // check for overflow (this should never happen unless our code is too inefficient)
  if ((mpuIntStatus & 0x10) || fifoCount == 1024) {
    // reset so we can continue cleanly
    mpu.resetFIFO();

    // otherwise, check for DMP data ready interrupt (this should happen frequently)
  } else if (mpuIntStatus & 0x02) {
    // wait for correct available data length, should be a VERY short wait

    while (fifoCount < packetSize) fifoCount = mpu.getFIFOCount();

    // read a packet from FIFO
    mpu.getFIFOBytes(fifoBuffer, packetSize);

    // track FIFO count here in case there is > 1 packet available
    // (this lets us immediately read more without waiting for an interrupt)
    fifoCount -= packetSize;


    // display Euler angles in degrees
    mpu.dmpGetQuaternion(&q, fifoBuffer);
    mpu.dmpGetGravity(&gravity, &q);
    mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);

    if (cicle_from_start < cal_count) {
      cicle_from_start++;
      if (cicle_from_start % flash_every == 0) {
        digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
      }
    }

    if (calibrated == true && potenza == 0) {
      offsetX = (ypr[0] * 180 / M_PI);
      sterzata = 0;

    }


    if (calibrated == true) {
      imbardata_gradi = ypr[0];
      imbardata_netta = (imbardata_gradi * 180 / M_PI);
      imbardata = ( (int)(imbardata_netta - offsetX)  % 360);
      rotta = imbardata + sterzata;
    }

    if (cicle_from_start == cal_count) {
      offsetX = (ypr[0] * 180 / M_PI);
      offsetY = (ypr[1] * 180 / M_PI);
      offsetZ = (ypr[2] * 180 / M_PI);
      cicle_from_start++;
      digitalWrite(LED_BUILTIN, HIGH);
      calibrated = true;
    }

  }
}







void lettura_batteria () {
  tensione = analogRead(battery);

  if (debug_batt) {
    Serial.print("D:");
    Serial.print("tensione letta ");
    Serial.println(tensione);
  }
  tensione = map(tensione, 480, 750, 0, 100);
  tensione = constrain(tensione, 0, 100);
  itoa(tensione, tensione_percentuale, 10);


  if (report_batteria) {
    Serial.print("B:");
    Serial.println(tensione_percentuale);
  }
}
