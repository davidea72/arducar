# arducar
arduino based car with mpu 6050 gyro

l' intento è quello di realizzare una macchinina comandata da un app sul telefono android 

 la macchinina deve andare avanti e indietro , destra e sinistra , deve fermarsi in automatico dopo un po che non riceve comandi 
 
 siccome non si trovano due motori che girino alla stessa velocità la macchinina tende sempre a sterzare da un lato, per correggere questo comportamento si è inserito il giroscopio GY-521 basato sull' mpu 6050
 
 il giroscopio puo' esser utilizzato in modalità normale , o con l' ausilio della DMP interna , in tal caso  va utilizzato il pin dell' interrupt per segnalare ad arduino quando la dmp ha finito i calcoli e i dati sono pronti da leggere 
 
 Anche in tale configurazione ho riscontrato che i primi 20 secondi circa la lettura non è stabile , quindi bisogna aspettare circa 20 secondi affinchè la lettura si stabilizzi (con un errore inferiore a 0.05 gradi) 
 
 ogni volta che la macchinina si ferma viene calcolato un nuovo offset in modo da considerare sempre come rotta 0 gradi la direzione che ha qualche istante prima della partenza 
 
 Per far andare dritta la macchinina quindi , viene passato al PID la rotta attuale , quella voluta (come setpoint) e se ne ottiene il valore da passare ai motori come correzione (output), questo valore è calcolato in base ai 3 parametri Kp , Ki e Kd 
 
 infine viene effettuata una lettura della batteria , tale tensione è ricavata tramite un partitore resistivo da quella di alimentazione dai supercondensatori , la lettura è riparametrizzata tra due valori che corrispondono a 7V - 0% e 11,7V 100% 
 l' app sul telefonino è stata creata tramite appinventor , del quale ho apprezzato la facilità d' uso ma ho anche trovato uno dei suoi limiti , non è possibile processare un grosso flusso dati dalla macchinina verso il telefonino , se mando tutti i dati di debug  sull' app vanno accumulando ritardo, arrivando ad una decina di secondi di ritardo fino a bloccare a volte l' app 
 
 Per debuggare sono stato costretto ad utilizzare il portatile collegato in bluetooth alla macchinina con un emulatore terminale quale minicom. 
 per facilitare il debug , le varie parti di debug sono attivabili e disattivabili a runtime , cosi' come anche i parametri K del pid sono modificabili a runtime con step di 0.5 
 
