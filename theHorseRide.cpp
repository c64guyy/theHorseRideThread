// Gioco della corsa dei cavalli: MARCO VINCI

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <string>
#include <fstream>

using namespace std;

//Costanti per i colori
const string RESET = "\033[0m";
const string NERO = "\033[30m";
const string ROSSO = "\033[31m";
const string VERDE = "\033[32m";
const string GIALLO = "\033[33m";
const string BLU = "\033[34m";
const string MAGENTA = "\033[35m";
const string CIANO = "\033[36m";
const string BIANCO = "\033[37m";
const string GRIGIO_SCURO = "\033[90m";
const string ROSSO_BRILLANTE = "\033[91m";
const string VERDE_BRILLANTE = "\033[92m";
const string GIALLO_BRILLANTE = "\033[93m";
const string BLU_BRILLANTE = "\033[94m";
const string MAGENTA_BRILLANTE = "\033[95m";
const string CIANO_BRILLANTE = "\033[96m";
const string BIANCO_BRILLANTE = "\033[97m";
const string MARRONE = "\033[38;5;94m";

// Prototipi funzioni
void titleScreen();
void clearScreen();
void track();
void game();
void stampaCavallo(int rigaBase, int colonna);
void pausa();
void salvaRisultato(int nCavalli, string vincitore, int mosseTotali);
string get_data_ora_stringa();
void allGames();
void totGames();
void horseStats();
void registraCavalli();

// Variabili globali
int posCavallo1 = 1, posCavallo2 = 1, posCavallo3 = 1, posCavallo4 = 1;
int puntiCavallo1 = 0, puntiCavallo2 = 0, puntiCavallo3 = 0, puntiCavallo4 = 0;
int mosseTotali = 0;
const int LUNGHEZZA_PISTA = 50;
string nomi[4];
string nomiCavalli[4] = {"", "", "", ""};  // nomi dei cavalli
int numCavalli = 0;

int main() {
    titleScreen();

    cout << GIALLO_BRILLANTE << "Premi invio per continuare...\n" << RESET;
    cout.flush();
    getchar();

    cout << VERDE_BRILLANTE << "=== MENU PRINCIPALE ===\n" << RESET;;

    //cout << "0. Inizia la corsa dei cavalli\n";
    //cout << "1. Visualizza le statistiche\n";
    //cout << "-1. Esci\n";

    int scelta;

    do {

        cout << "1. Inizia la corsa dei cavalli\n";
        cout << "2. Visualizza le statistiche\n";
        cout << "0. Esci\n";
        cout << GIALLO_BRILLANTE << "Scelta: " << RESET;
        cin >> scelta;

        switch(scelta) {

            case 1: { // Gioco principale

                clearScreen();
                game();
                getchar();
                break;

            }
            case 2: { //Case statistiche 

                clearScreen();
                cout << GIALLO_BRILLANTE << "=== MENU STATISTICHE ===\n" << RESET;

                cout << endl;

                cout << "1. Visualizza tutte le corse\n";
                cout << "2. Visaulizza il numero tot. di partite\n";
                cout << "3. Visualizza i nomi dei cavalli e quante corse hanno vinto\n";

                int scelta2; 

                do {
                    cout << GIALLO_BRILLANTE << "Scelta: " << RESET;
                    cin >> scelta2;

                    switch (scelta2) {
                        
                        case 1: {

                            allGames();
                            break;
                        }
                        case 2: {

                            totGames();
                            break;

                        }
                        case 3: {

                            horseStats();
                            break;

                        }
                        default: {

                            cout << ROSSO_BRILLANTE << "Scelta non valida. Riprova.\n" << RESET;
                            break;

                        }

                    }

                } while (scelta2 != 0);
                
                break;

            }
            case 0: {

                cout << ROSSO_BRILLANTE << "Uscita in corso...\n" << RESET;
                break;

            }
            default: {

                cout << ROSSO_BRILLANTE << "Scelta non valida. Riprova.\n" << RESET;
                break;
            }

        }

    } while (scelta != 0);

    return 0;
}

string get_data_ora_stringa() // Funzione per far restituire data e ora 
{ 
    time_t ora = time(0); 
    struct tm *data_ora = localtime(&ora); 
    char buffer[80]; 
    strftime(buffer, sizeof(buffer), "%d/%m/%Y %H:%M:%S", data_ora); 
    return string(buffer); 
}

void titleScreen() // FUnzione per stampare la schermata del titolo
{
    clearScreen();
    cout << endl;

    cout << BLU;
    cout << "/======================================================================\\\n";
    cout << "|| _____ _            _   _                       ____  _     _       ||\n";
    cout << "|||_   _| |__   ___  | | | | ___  _ __ ___  ___  |  _ \\(_) __| | ___  ||\n";
    cout << "||  | | | '_ \\ / _ \\ | |_| |/ _ \\| '__/ __|/ _ \\ | |_) | |/ _` |/ _ \\ ||\n";
    cout << "||  | | | | | |  __/ |  _  | (_) | |  \\__ \\  __/ |  _ <| | (_| |  __/ ||\n";
    cout << "||  |_| |_| |_|\\___| |_| |_|\\___/|_|  |___/\\___| |_| \\_\\_|\\__,_|\\___| ||\n";
    cout << "\\======================================================================/\n";
    cout << RESET;
}

void clearScreen() // Funzione per pulire lo schermo (universale per windows/linux/MACOS)
{ 
#ifdef _WIN32
    system("cls");
#else
    cout << "\033[2J\033[1;1H";
    cout.flush();
#endif
}

void track() // Funzione per stampare il tracciato
{ 
    cout << MARRONE;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    cout << RESET;
}

void pausa() // Funzione per pausa
{ 
    clock_t fine = clock() + 300 * CLOCKS_PER_SEC / 1000;
    while (clock() < fine);
}

void salvaRisultato(int nCavalli, string vincitore, int mosseTotali) // Funzione per salvare i risultati su file
{
    ofstream file("risultati_corsa.txt", ios::app);
    
    
    if (!file) {
        cout << ROSSO_BRILLANTE << "Errore nell'apertura del file per salvare i risultati.\n" << RESET;
        return;
    }

    string dataOra = get_data_ora_stringa();
        
        
    file << nCavalli << " " << vincitore << " " << mosseTotali << " " << dataOra << "\n";
    file.close();
        
    cout << GIALLO_BRILLANTE << "\n Risultati salvati in 'risultati_corsa.txt'\n" << RESET;

}

void game() // Gioco principale
{
    clearScreen();
    int nCavalli;

    cout << GIALLO_BRILLANTE;
    cout << "Inserisci il numero di cavalli da far gareggiare (2-4): ";
    cout << RESET;

    do {
        cin >> nCavalli;
    } while (nCavalli < 2 || nCavalli > 4);

    cout << endl;
    for (int i = 0; i < nCavalli; i++) {
        cout << "Inserisci il nome del " << i + 1 << " cavallo: ";
        cin >> nomi[i];
    }

    numCavalli = nCavalli;  // salva numero cavalli
    registraCavalli(); 

    posCavallo1 = posCavallo2 = posCavallo3 = posCavallo4 = 1;

    puntiCavallo1 = puntiCavallo2 = puntiCavallo3 = puntiCavallo4 = 0;

    mosseTotali = 0;

    srand(time(NULL));

    while (true) {
        clearScreen();
        track();

        // Stampa cavalli
        cout << ROSSO_BRILLANTE;
        stampaCavallo(4, posCavallo1);
        cout << RESET;
        track();

        cout << VERDE_BRILLANTE;
        stampaCavallo(14, posCavallo2);
        cout << RESET;
        track();

        if (nCavalli >= 3) {
            cout << GIALLO_BRILLANTE;
            stampaCavallo(24, posCavallo3);
            cout << RESET;
            track();
        }
        if (nCavalli == 4) {
            cout << BLU_BRILLANTE;
            stampaCavallo(34, posCavallo4);
            cout << RESET;
            track();
        }

        // Movimento

        int passo1 = rand() % 4; // Genera un numero casuale di passi da 0 a 3
        posCavallo1 = (posCavallo1 + passo1 > LUNGHEZZA_PISTA) ? LUNGHEZZA_PISTA : posCavallo1 + passo1; // Se il cavallo supera la pista, rimane fermo
        if (posCavallo1 >= LUNGHEZZA_PISTA) puntiCavallo1 = 10; // Assegna 10 punti se raggiunge o supera la lunghezza della pista

        // Stesso per il secondo cavallo
        int passo2 = rand() % 4;
        posCavallo2 = (posCavallo2 + passo2 > LUNGHEZZA_PISTA) ? LUNGHEZZA_PISTA : posCavallo2 + passo2;
        if (posCavallo2 >= LUNGHEZZA_PISTA) puntiCavallo2 = 10;

        // Stesso per il terzo e il quarto cavallo
        if (nCavalli >= 3) {
            int passo3 = rand() % 4;
            posCavallo3 = (posCavallo3 + passo3 > LUNGHEZZA_PISTA) ? LUNGHEZZA_PISTA : posCavallo3 + passo3;
            if (posCavallo3 >= LUNGHEZZA_PISTA) puntiCavallo3 = 10;
        }
        if (nCavalli == 4) {
            int passo4 = rand() % 4;
            posCavallo4 = (posCavallo4 + passo4 > LUNGHEZZA_PISTA) ? LUNGHEZZA_PISTA : posCavallo4 + passo4;
            if (posCavallo4 >= LUNGHEZZA_PISTA) puntiCavallo4 = 10;
        }

        mosseTotali++;

        // Controllo vincitore
        if (puntiCavallo1 == 10) {

            clearScreen();

            cout << "\n\n" << ROSSO_BRILLANTE << nomi[0] << " HA RAGGIUNTO 50 E HA VINTO!\n\n" << RESET;
            
            // Scrittura dei risultati sul file
            salvaRisultato(nCavalli, nomi[0], mosseTotali);
            
            // Schermata finale
            cout << GIALLO_BRILLANTE << "\n🏆 " << nomi[0] << " HA VINTO LA CORSA! 🏆\n\n" << RESET;

            cout << "Risultati gara (su 50):\n\n";
            cout << ROSSO_BRILLANTE << " 1° " << nomi[0] << ": " << posCavallo1 << "/50" << RESET << endl;
            cout << VERDE_BRILLANTE << " 2° " << nomi[1] << ": " << posCavallo2 << "/50" << RESET << endl;
            if (nCavalli >= 3) cout << GIALLO_BRILLANTE << " 3° " << nomi[2] << ": " << posCavallo3 << "/50" << RESET << endl;
            if (nCavalli == 4) cout << BLU_BRILLANTE << " 4° " << nomi[3] << ": " << posCavallo4 << "/50" << RESET << endl;

            cout << "\nMosse totali: " << mosseTotali << "\n";
            cout << "\nSalvato in risultati_corsa.txt\n\n";

            cout << GIALLO_BRILLANTE << "Premi un tasto per uscire..." << RESET;
            getchar();
            break;
        }

        if (puntiCavallo2 == 10) {

            clearScreen();

            cout << "\n\n" << VERDE_BRILLANTE << nomi[1] << " HA RAGGIUNTO 50 E HA VINTO!\n\n" << RESET;

            salvaRisultato(nCavalli, nomi[1], mosseTotali);
            
            // Schermata finale
            cout << GIALLO_BRILLANTE << "\n🏆 " << nomi[1] << " HA VINTO LA CORSA! 🏆\n\n" << RESET;

            cout << "Risultati gara (su 50):\n\n";
            cout << ROSSO_BRILLANTE << " 1° " << nomi[0] << ": " << posCavallo1 << "/50" << RESET << endl;
            cout << VERDE_BRILLANTE << " 1° " << nomi[1] << ": " << posCavallo2 << "/50" << RESET << endl;
            if (nCavalli >= 3) cout << GIALLO_BRILLANTE << " 3° " << nomi[2] << ": " << posCavallo3 << "/50" << RESET << endl;
            if (nCavalli == 4) cout << BLU_BRILLANTE << " 4° " << nomi[3] << ": " << posCavallo4 << "/50" << RESET << endl;

            cout << "\nMosse totali: " << mosseTotali << "\n";
            cout << "\nSalvato in risultati_corsa.txt\n\n";

            cout << GIALLO_BRILLANTE << "Premi un tasto per uscire..." << RESET;
            getchar();
            break;
        }

        if (nCavalli >= 3 && puntiCavallo3 == 10) {
            clearScreen();

            cout << "\n\n" << GIALLO_BRILLANTE << nomi[2] << " HA RAGGIUNTO 50 E HA VINTO!\n\n" << RESET;
            salvaRisultato(nCavalli, nomi[2], mosseTotali);
            
            break;
        }

        if (nCavalli == 4 && puntiCavallo4 == 10) {
            clearScreen();
            cout << "\n\n" << BLU_BRILLANTE << nomi[3] << " HA RAGGIUNTO 50 E HA VINTO!\n\n" << RESET;
            salvaRisultato(nCavalli, nomi[3], mosseTotali);
            
            break;
        }

        pausa();
    }
}


void stampaCavallo(int rigaBase, int colonna) 
//Funzione per stampare il cavallo
{
    cout << "\033[" << rigaBase << ";" << colonna << "H";
    cout << "            .''\n";

    cout << "\033[" << (rigaBase + 1) << ";" << colonna << "H";
    cout << "  ._.-.___.' (`\\\n";

    cout << "\033[" << (rigaBase + 2) << ";" << colonna << "H";
    cout << "//(        ( `'\n";

    cout << "\033[" << (rigaBase + 3) << ";" << colonna << "H";
    cout << "'/ )\\ ).__. ) \n";

    cout << "\033[" << (rigaBase + 4) << ";" << colonna << "H";
    cout << "' <' `\\ ._/'\\\n";

    cout << "\033[" << (rigaBase + 5) << ";" << colonna << "H";
    cout << "   `   \\     \\\n";
    cout.flush();
}

void allGames() { // Funzione per visualizzare tutte le corse registrate

    clearScreen();

    ifstream file("risultati_corsa.txt");

    if (!file) {
        cout << ROSSO_BRILLANTE << "Errore nell'apertura del file delle statistiche.\n" << RESET;
        return;
    }

    cout << GIALLO_BRILLANTE << "=== TUTTE LE CORSE REGISTRATE ===\n\n" << RESET;

    int nCavalli;
    string vincitore;
    int mosseTotali;
    string dataOra; 

    while (file >> nCavalli >> vincitore >> mosseTotali) {

        getline(file, dataOra); 
        cout << "Cavalli: " << nCavalli << ", Vincitore: " << vincitore << ", Mosse Totali: " << mosseTotali << ", Data e Ora:" << dataOra << "\n";
    }

    file.close();
}

void totGames() { //Funzione per stampare il numero di partite

    clearScreen();

    ifstream file("risultati_corsa.txt");

    if (!file) {
        cout << ROSSO_BRILLANTE << "Errore nell'apertura del file delle statistiche.\n" << RESET;
        return;
    }

    int nCavalli;
    string vincitore;
    int mosseTotali;
    string dataOra;
    
    int count = 0;

    while (file >> nCavalli >> vincitore >> mosseTotali >> dataOra){

        count++; 
    }

    cout << "TOTALE PARTITE GIOCATE: " << count << endl;

    file.close();
}

void horseStats() { //statistiche per ogni cavallo
    clearScreen();
    
    if (numCavalli == 0) {
        cout << ROSSO_BRILLANTE << "Nessun cavallo registrato.\n" << RESET;
        return;
    }

    ifstream file("risultati_corsa.txt");
    if (!file) {
        cout << ROSSO_BRILLANTE << "Errore nell'apertura del file.\n" << RESET;
        return;
    }

    cout << GIALLO_BRILLANTE << "=== VITTORIE PER CAVALLO ===\n\n" << RESET;

    int vittorie[4] = {0, 0, 0, 0};

    int nCavalliFile;
    string vincitore;
    int mosseTotali;
    string resto;

    while (file >> nCavalliFile >> vincitore >> mosseTotali) {
        getline(file, resto);  // scarta data/ora
        
        // Cerca tra i cavalli registrati
        for (int i = 0; i < numCavalli; i++) {
            if (nomiCavalli[i] == vincitore) {
                vittorie[i]++;
                break;
            }
        }
    }

    file.close();

    // Stampa
    cout << "NOME\t\tVITTORIE\n";
    cout << "--------------------\n";
    for (int i = 0; i < numCavalli; i++) {
        cout << nomiCavalli[i] << "\t\t" << vittorie[i] << "\n";
    }
}


void registraCavalli() { //funzione per registrare i cavalli
    for (int i = 0; i < 4; i++) {
        nomiCavalli[i] = "";
    }
    
    for (int i = 0; i < numCavalli; i++) {  
        nomiCavalli[i] = nomi[i];
    }
}

