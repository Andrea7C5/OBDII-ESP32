#include "BluetoothSerial.h"
#include "ELMduino.h"

BluetoothSerial SerialBT;
#define ELM_PORT   SerialBT

// Dichiarazione delle funzioni
void temp();
void rpmm();
void kmh();
void dtc();

uint8_t address[6]  = {0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX};  //Sostituire XX con il proprio indirizzo MAC. io ho utilizzato l'indirizzo MAC dell'ELM327 perchè usando il nome del dispositivo "OBDII" a me non si collega

ELM327 myELM327;

//variabili per temperatura e giri motore
int coolantTemp = 0;
uint32_t rpm = 0;

byte inData;
char inChar;
String BuildINString="";
String DisplayString="";
String WorkingString="";
long DisplayValue;
long A;
int B;


void setup()
{
  Serial.begin(38400);
  ELM_PORT.begin(38400);
  ELM_PORT.begin("ArduHUD", true);
  SerialBT.setPin("1234");    //il pin per la connessione all'elm327 a volte può essere 1234 o 0000 o 6789
  
  if (!ELM_PORT.connect(address))   //address per connettersi usando il MAC address dichiarato sopra ma si può usare anche il nome dell'elm327 "OBDII"
  {
    Serial.println("Couldn't connect Phase 1");
    delay(1000);
   
    while (1);
  }

  if (!myELM327.begin(ELM_PORT))
  {
    Serial.println("Couldn't connect to OBD scanner - Phase 2");
    while (1);
  }

  Serial.println("Connected to ELM327");

//qui nasce uno dei miei problemi, non riesco a utilizzare le librerie elmduino per far partire la comunicazione con l'auto quindi ho inviato tramite seriale direttamente i comandi che volevo, ho inserito dei delay per essere sicuro che riceva i comandi, non so se realmente servano
delay(100);
ELM_PORT.println("ATZ");  //resetta l'interfaccia elm327
delay(100);
ELM_PORT.println("ATSP3"); //ho inserito ATSP3 in quanto sapevo che il protocollo di comunicazione della mia auto è questo
delay(100);
ELM_PORT.println("ATH1"); 
delay(100);
ELM_PORT.println("ATS0");
delay(100);
ELM_PORT.println("ATE0");
delay(100);
ELM_PORT.println("0100");
delay(3000);
ELM_PORT.println("0120");
delay(3000);
}
  
void loop() {
  // Controlliamo se ci sono dati disponibili sulla porta seriale
  if (Serial.available() > 0) {
    // Leggiamo la stringa inviata
    String input = Serial.readStringUntil('\n');

    // per passare da una lettura all'altra ho fatto si che riceva un comando dalla seriale
    if (input.equalsIgnoreCase("temp")) {
      temp(); // Chiamiamo la funzione per la temperatura
    } 
    else if (input.equalsIgnoreCase("rpm")) {
      rpmm(); // Chiamiamo la funzione per RPM
    } 
    else if (input.equalsIgnoreCase("kmh")) {
      kmh(); // Chiamiamo la funzione per KM/H
    }
    else if (input.equalsIgnoreCase("dtc")) {
      dtc(); // Chiamiamo la funzione per DTC
    }
  }
}

void temp() {
  while (true) {
    // Invia una richiesta per leggere la temperatura del liquido refrigerante  (PID 0x05)
    ELM_PORT.println("0105");
    delay(100);
    
    // Legge la risposta dall'ELM327
    String response = "";
    while (ELM_PORT.available()) {
        char c = ELM_PORT.read();
        response += c; 
    }

        // Estrai il valore grezzo della temperatura 
        int coolantTempRaw = strtol(response.substring(14, 17).c_str(), NULL, 16); // Estrai il byte della temperatura
        int coolantTemp = coolantTempRaw - 40;  // Calcola la temperatura in gradi Celsius

        // Stampa il valore della temperatura
        Serial.print("Temp: ");
        Serial.print(coolantTemp);
        Serial.println(" °C");
        Serial.print("\n");
        Serial.print("\n");
    

    delay(1000);  // Legge ogni secondo

    if (Serial.available() > 0) {
      String exitInput = Serial.readStringUntil('\n');
      if (exitInput.equalsIgnoreCase("exit")) {
        Serial.println("Uscita da temp.");
        break; // Esci dalla funzione temp
      }
    }
    delay(1000);
}
}
void rpmm() {


    while (true) {
    // Invia una richiesta per leggere i giri motore (PID 0x0C)
    ELM_PORT.println("010C");
    delay(200);
    
    // Leggi la risposta dall'ELM327
    String response = "";
    while (ELM_PORT.available()) {
        char c = ELM_PORT.read();
        response += c; 
    }

       // Estrai i byte per i giri del motore
        int value1 = strtol(response.substring(14, 17).c_str(), NULL, 16); // Primo byte (valore1)
        int value2 = strtol(response.substring(17, 20).c_str(), NULL, 16); // Secondo byte (valore2)

        // Calcola i giri del motore
        int RpmValue = ((value1 * 256) + value2) / 4;

        // Stampa il valore RPM
        Serial.println("Rpm: ");
        Serial.println(RpmValue);
        Serial.println("\n");

    if (Serial.available() > 0) { //se riceve dalla seriale il comando exit esce
      String exitInput = Serial.readStringUntil('\n');
      if (exitInput.equalsIgnoreCase("exit")) {
        Serial.println("Uscita da rpm.");
        break; // Esci dalla funzione rpm
      }
    }
    delay(1000);
}

}
  void kmh() {
}

        void dtc() {
}
