# OBDII-ESP32
Ho utilizzato l'ESP32 Wrover per fare queste prove in quanto non è possibile utilizzare gli ESP32-s2 (ad esempio) perchè avendo il BLE non è possibile utilizzare le librerie BluetoothSerial. Il mio intento è quello di leggere i dati trasmessi all'esp32 tramite bluetooth dal flipper zero o comunque qualsiasi altro dispositivo. E' possibile utilizzare anche le interfacce ELM327 che hanno la connessione usb invece del bluetooth collegandosi direttamente all'rx e tx prima del convertirore Seriale->USB, le mie prime prove erano infatti su quello, ma il fatto di avere i fili collegato lo rendeva scomodo, comunque pubblicherò anche quello appena lo ritrovo. 

![IMG_4677](https://github.com/user-attachments/assets/95fdf65f-c011-41e6-bad6-16fda673e8c2)

# ELM327
Come interfaccia ELM327 ho utilizzato quelle che si trovano anche su amazon.

![7187RPpHBhL _AC_UF1000,1000_QL80_](https://github.com/user-attachments/assets/78265b1c-b756-4a81-adf8-937183c239ce)






# Codice e problemi riscontrati
Utilizzando il nome del dispositivo "OBDII" come negli esempi di codice di ELMduino non riesco a connettermi e ho preferito utilizzare l'indirizzo MAC dell'adattatore bluetooth ELM327 e specificato il pin. Un'altra difficoltà che ho riscontrato penso per una questione di posizione dei byte ricevuti dall'interfaccia è che utilizzando le librerie Elmduino per inzializzare la comunicazione con l'auto a me non funziona, ho usato direttamente i comandi Elm327 da seriale.
Per quanto riguarda il protocollo si potrebbe anche utilizzare ATSP0 per far si che lo scelga automaticamente, io sapendo che la mia auto utilizza il protocollo 3 (ISO 9141-2) ho utilizzato direttamente quello. 
Ovviamente i comandi e parametri utilizzati da me non per forza corrisponderanno con altri, ad esempio per i valori esadecimali ricevuti per la temperatura o altro devono corrispondere la posizione dei byte. Un'altra cosa importante il baud rate dell'interfaccia ELM327 almeno per quanto riguarda la mia è 38400, voi potreste avere un baud rate differente.
Dopo la connessione stabilita per poter avviare la lettura ad esempio della temperatura si dovrà inviare dal terminale "temp". 

Per adesso ho inserito solo lettura della temperatura e giri motore, anche per questi non ho utilizzato la libreria ELMduino, ma calcolato i valori esadecimali ricevuti dal seriale, probabilmente è possibile utilizzare anche le librerie ELMduino per questo. in futuro sicuramente inserirò la lettura degli errori della centralina e la possibilità di cancellarli perchè è ciò che mi interessa.






# Le librerie ed esempi utilizzati: 
https://github.com/PowerBroker2/ELMduino
