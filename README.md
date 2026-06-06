# 🐴 THE HORSE RIDE THREAD 🐴

> *Una simulazione di corsa ippica scritta in C++ con thread, mutex, ASCII art, e un easter egg degno di un essere umano profondamente disturbato.*

---

## 🎯 Cos'è?

Questo programma simula una **corsa di cavalli** direttamente nel tuo terminale. Puoi schierare da 2 a 4 cavalli, scommettere su uno di loro, guardarli galoppare in tempo reale disegnati in ASCII art, e piangere quando perdi.

Funziona con **thread paralleli** (uno per cavallo), **mutex** per non fare esplodere la console, e una logica di avanzamento basata sull'attesa... casuale. È praticamente la borsa valori.

---

## 🗺️ Come funziona

```
main()
  │
  ├─► titleScreen()       
  │
  └─► printMenu()
        │
        ├─► [1] Inserisci numero cavalli (2-4)
        │         │
        │         ├─► Inserisci nomi cavalli
        │         ├─► Scegli su chi scommettere
        │         └─► Lancia N thread → race(id) per ogni cavallo
        │                   │
        │                   ├─► Loop: avanza, disegna, stampa
        │                   └─► Se arriva al traguardo → winnerScreen() + salvaRis()
        │
        ├─► [2] stampaRis()  ← legge il file dei risultati
        └─► [0] Esci (con stile)
```

---

## ⚙️ Le funzioni

### `titleScreen()`
Stampa una schermata di titolo completamente inutile che occupa metà del tuo terminale. Usa `\033[...m` per i colori ANSI.

### `printMenu()`
Il cuore del main loop. Mostra il menu, legge la scelta dell'utente, e poi fa accadere le cose. Gestisce anche la logica della scommessa: se hai indovinato il vincitore, ti compare un messaggio trionfale in ASCII verde. Altrimenti, rosso della vergogna.

### `clearScreen()`
Su Windows usa `system("cls")` come un barbaro. Su sistemi seri (Linux/macOS) manda una sequenza di escape ANSI. Semplice, efficace, controverso.

### `puliziaMatrice()`
Riempie tutta la matrice `screen[ROWS][COL]` di spazi. È il reset del canvas prima di ridisegnare tutto. 

### `drawHorse(int posX, int posY)`
Scrive il cavallo ASCII nella matrice `screen`. Il cavallo è definito così:

```
            .''
  ._.-.___.' (`\
 //(        ( `'
'/ )\ ).__. )
' <' `\ ._/'\
   `   \     \
```

`posX` è la posizione orizzontale (quanto ha avanzato), `posY` è la corsia verticale (quale cavallo è). Controlla che il cavallo non esca dalla matrice.

### `printScreen()`
Legge la matrice `screen` e la stampa riga per riga nel terminale. Colora ogni cavallo con il suo colore ANSI dedicato (giallo, rosso, verde, blu — come i Power Rangers). Chiama anche `track()` dopo ogni cavallo per disegnare la pista.

### `track()`
Stampa due righe di `~` marroni. Questa è la pista.

### `race(int id)`
**LA FUNZIONE PRINCIPALE.** Gira in un thread per ogni cavallo. Ogni iterazione:
1. Aspetta un tempo **casuale** tra 1 e 5 secondi (o 100ms se sei `minnesota`)
2. Prende il **mutex** `m`
3. Avanza di 1 posizione
4. Ridisegna tutti i cavalli
5. Controlla se ha vinto
6. Rilascia il mutex

Usa il mutex per evitare che due thread stampino contemporaneamente e producano qualcosa che sembra arte moderna involontaria.

### `winnerScreen(int id)`
Stampa "WINNER!!" in ASCII art gialla e annuncia il vincitore.

### `salvaRis(int id)`
Salva il risultato della gara su `risultati.txt` in modalità append (`ios::app`). Scrive: numero cavalli, nome vincitore, data e ora. Se il file non si apre, urla in rosso e se ne va.

### `stampaRis()`
Legge `risultati.txt` e stampa tutte le gare salvate. Usa `getline` per leggere la data+ora come resto della riga dopo nome e numero. Fondamentale: se il file non esiste ancora, crasha elegantemente.

### `get_data_ora()`
Restituisce data e ora nel formato `DD/MM/YYYY HH:MM:SS` usando `localtime` e `strftime`.

---

## 🥚 MINNESOTA

Se dai ad un cavallo il nome `minnesota`, questo non aspetta 1-5 secondi per ogni mossa. Aspetta `100 millisecondi`.

È la modalità dio. Ed è anche una citazione a `Massimiliano Allegri`, che in un'intervista raccontò di aver scommesso su un cavallo di nome Minnesota alle corse. Qualcuno gli disse che era più facile che diventasse allenatore di Serie A che vedere quel cavallo vincere. Bene: il cavallo vinse, e lui era sulla panchina della Juventus.

L'easter egg è nascosto nel codice come `nomi[id] == "minnesota"` senza nemmeno un commento — perché certe cose o le sai o non le meriti. Pura follia. 
`Rispetta.`

---

## 🏗️ Struttura del codice

```
theHorseRideThread.cpp
│
├── Costanti ANSI (colori)
├── Costanti di gioco (ROWS, COL, fine, ecc.)
├── ASCII art del cavallo (array di stringhe)
│
├── Variabili globali
│   ├── screen[32][80]     ← il canvas
│   ├── posizioni[4]       ← dove sono i cavalli
│   ├── winner / winnerId  ← stato della gara
│   └── nomi[4]            ← nomi dei partecipanti
│
├── mutex m                ← il mutex
│
└── Funzioni (vedi sopra)
```

---


## 💻 Compilazione ed esecuzione

```bash
# Compila con supporto thread
g++ horse theHorseRideThread.cpp -o ./es

# Avvia
./es
```

> ⚠️ Su Windows potresti dover usare MinGW o WSL. In alternativa, riconsideri le tue scelte di vita.

---

*Fatto con amore dal suo alunno preferito, tanti problemi, thread, e Max (ora pure Dusan mi ha abbandonato, maledetti)*
