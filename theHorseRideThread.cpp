#include<iostream>
#include<cstdlib>
#include<ctime>
#include<cstdio>
#include<string>
#include<thread>
#include<fstream>
#include<chrono>
#include<mutex>

using namespace std;

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

const int HORSE_ROWS = 6;
const int ROWS = 32;
const int COL = 80; //larghezza schermo
const int fine = 40; //traguardo
const string coloriCavalli[4] = {GIALLO_BRILLANTE, ROSSO_BRILLANTE, VERDE_BRILLANTE, BLU_BRILLANTE};

const char* horse[] = { //array di stringhe per disegnare il cavallo
    "            .''",
    "  ._.-.___.' (`\\",
    " //(        ( `'",
    "'/ )\\ ).__. ) ",
    "' <' `\\ ._/'\\",
    "   `   \\     \\",

};

//VARIABILI GLOBALI

char screen[ROWS][COL];
int posizioni[4] = {0, 0, 0, 0};
bool winner = false;
int numCavalli = 0;
int winnerId = -1;
string nomi[4];

//MUTEX

mutex m;

void clearScreen();
void titleScreen();
void printMenu();
void track();
void puliziaMatrice();
void drawHorse(int posX, int posY);
void printScreen();
void race(int id);
void winnerScreen(int id);
void minnesotaScreen(int id);
void salvaRis(int id);
void stampaRis();

string get_data_ora();

int main() {
    srand(time(NULL));

    titleScreen();

    cout << endl;
    cout << "Premi invio per iniziare...\n";
    cout.flush();
    getchar();

    printMenu();
}

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        cout << "\033[2J\033[1;1H";
        cout.flush();
    #endif
}

void titleScreen() {
    clearScreen();

    cout << BLU_BRILLANTE;
    cout << "/======================================================================\\\n";
    cout << "|| _____ _            _   _                       ____  _     _       ||\n";
    cout << "|||_   _| |__   ___  | | | | ___  _ __ ___  ___  |  _ \\(_) __| | ___  ||\n";
    cout << "||  | | | '_ \\ / _ \\ | |_| |/ _ \\| '__/ __|/ _ \\ | |_) | |/ _` |/ _ \\ ||\n";
    cout << "||  | | | | | |  __/ |  _  | (_) | |  \\__ \\  __/ |  _ <| | (_| |  __/ ||\n";
    cout << "||  |_| |_| |_|\\___| |_| |_|\\___/|_|  |___/\\___| |_| \\_\\_|\\__,_|\\___| ||\n";
    cout << "\\======================================================================/\n";
    cout << RESET;

    cout << ROSSO_BRILLANTE;
    cout << " _____ _                        _   _____    _ _ _   _             \n";
    cout << "|_   _| |                      | | |  ___|  | (_) | (_)            \n";
    cout << "  | | | |__  _ __ ___  __ _  __| | | |__  __| |_| |_ _  ___  _ __  \n";
    cout << "  | | | '_ \\| '__/ _ \\/ _` |/ _` | |  __|/ _` | | __| |/ _ \\| '_ \\ \n";
    cout << "  | | | | | | | |  __/ (_| | (_| | | |__| (_| | | |_| | (_) | | | |\n";
    cout << "  \\_/ |_| |_|_|  \\___|\\__,_|\\__,_| \\____/\\__,_|_|\\__|_|\\___/|_| |_|\n";
    cout << RESET;

}

void printMenu() {
    clearScreen();

    int scelta;

    cout << BLU_BRILLANTE;
    cout << " __  __ _____ _   _ _   _ \n";
    cout << "|  \\/  | ____| \\ | | | | |\n";
    cout << "| |\\/| |  _| |  \\| | | | |\n";
    cout << "| |  | | |___| |\\  | |_| |\n";
    cout << "|_|  |_|_____|_| \\_|\\___/ \n";
    cout << RESET;
    
    cout << endl;

    cout << "1. Inizia la corsa dei cavalli" << endl;
    cout << "2. Visualizza le statistiche" << endl;
    cout << "0. Esci dal gioco" << endl;

    cout << "Scegli un'opzione: ";
    cin >> scelta;

    switch(scelta) {
        case 1: {
            clearScreen();

            cout << "Quanti cavalli vuoi fare gareggiare? (2 - 4): ";
            cin >> numCavalli;

            if (numCavalli < 2 || numCavalli > 4) {
                cout << "Numero di cavalli non valido. Verranno usati 2 cavalli.\n";
                numCavalli = 2;
            }

            for (int i = 0; i < numCavalli; i++) {
                cout << "Inserisci il nome del " << i + 1 << " cavallo: ";
                cin >> nomi[i];
            }

            int scommessa = -1;
            cout << "Su quale cavallo vuoi scommettere? (1-" << numCavalli << ", 0 per nessun cavallo): ";
            cin >> scommessa;

            cout << "\nVia! La gara sta per iniziare...\n";
            this_thread::sleep_for(chrono::seconds(2));
 
                
            thread threads[4];
            for (int i = 0; i < numCavalli; i++) {
                threads[i] = thread(race, i);
            }
                    
            for (int i = 0; i < numCavalli; i++) {
                threads[i].join();
            }   

            if (scommessa >= 1 && scommessa <= numCavalli) {
                if (winnerId == scommessa - 1) {
                    clearScreen();

                    cout << VERDE_BRILLANTE;
                    cout << " _____                                                     _   _ _       _        _ _ " << endl;
                    cout << "/  ___|                                                   | | | (_)     | |      | | |" << endl;
                    cout << "\\ `--.  ___ ___  _ __ ___  _ __ ___   ___  ___ ___  __ _  | | | |_ _ __ | |_ __ _| | |"  << endl;
                    cout << " `--. \\/ __/ _ \\| '_ ` _ \\| '_ ` _ \\ / _ \\/ __/ __|/ _` | | | | | | '_ \\| __/ _` | | |" << endl;
                    cout << "/\\__/ / (_| (_) | | | | | | | | | | |  __/\\__ \\__ \\ (_| | \\ \\_/ / | | | | || (_| |_|_|" << endl;
                    cout << "\\____/ \\___\\___/|_| |_| |_|_| |_| |_|\\___||___/___/\\__,_|  \\___/|_|_| |_|\\__\\__,_(_|_)" << endl;
                    cout << RESET;
                }
                else {
                    clearScreen();

                    cout << ROSSO_BRILLANTE;
                    cout << " _____                                                    ______                          __" << endl;
                    cout << "/  ___|                                                   | ___ \\                    _   / /" << endl;
                    cout << "\\ `--.  ___ ___  _ __ ___  _ __ ___   ___  ___ ___  __ _  | |_/ /__ _ __ ___  __ _  (_) | | " << endl;
                    cout << " `--. \\/ __/ _ \\| '_ ` _ \\| '_ ` _ \\ / _ \\/ __/ __|/ _` | |  __/ _ \\ '__/ __|/ _` |     | | " << endl;
                    cout << "/\\__/ / (_| (_) | | | | | | | | | | |  __/\\__ \\__ \\ (_| | | | |  __/ |  \\__ \\ (_| |  _  | | " << endl;
                    cout << "\\____/ \\___\\___/|_| |_| |_|_| |_| |_|\\___||___/___/\\__,_| \\_|  \\___|_|  |___/\\__,_| (_) | | " << endl;
                    cout << "                                                                                         \\_\\"<< endl;
                    cout << RESET;
                }
            }

            break;
        }
        case 2: {
            stampaRis();
            break;
        }
        case 0: {
            cout << ROSSO_BRILLANTE << "Uscita in corso..." << RESET;
            break;
        }
        default: {
            cout << ROSSO_BRILLANTE << "Scelta non valida. Riprova" << RESET;
            break;
        }
    }

}

void track() {
    cout << MARRONE;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    cout << RESET;
}

void puliziaMatrice() {
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COL; c++) {
            screen[r][c] = ' ';
        }
    }
}

void drawHorse(int posX, int posY) {
    for (int row = 0; row < HORSE_ROWS; row++) {
        for (int col = 0; horse[row][col] != '\0'; col++) {
            //controlla che il cavallo non esca dalla matrice
            if (posX + col < COL && posY + row < ROWS) {
                screen[posY + row][posX + col] = horse[row][col];
            }
        }
    }
}

void printScreen() {
    clearScreen();

    for (int i = 0; i < numCavalli; i++) {
        cout << coloriCavalli[i];
        cout << "Cavallo " << i + 1 << " - " << nomi[i] << endl;

        for (int r = i * 8; r < i * 8 + HORSE_ROWS; r++) {
            for (int c = 0; c < COL; c++) {
                cout << screen[r][c];
            }
            cout << endl;
        }

        cout << RESET;
        track();
    }
}

void race(int id) {
    bool godMode = (nomi[id] == "minnesota");

    while (posizioni[id] < fine && !winner) {

        if (godMode) {
            this_thread::sleep_for(chrono::milliseconds(100));
        } else {
            int attesa = rand() % 5 + 1;
            this_thread::sleep_for(chrono::seconds(attesa));
        }
    
        //SEZIONE CRITICA
        m.lock();
        posizioni[id]++;

        puliziaMatrice();
        for (int i = 0; i < numCavalli; i++)
            drawHorse(posizioni[i], i * 8);

        if (posizioni[id] >= fine && !winner) {
            winner = true;
            winnerId = id;
            printScreen();
            winnerScreen(id);
            salvaRis(id);
            m.unlock();
            getchar();
            return;
        }

        printScreen(); // stampa solo se nessuno ha vinto
        m.unlock();
    }
    
}

void winnerScreen(int id) {
    clearScreen();
    cout << GIALLO_BRILLANTE;
    cout << " _    _ _____ _   _  _   _  ___________ _ _ \n";
    cout << "| |  | |_   _| \\ | || \\ | ||  ___| ___ \\ | |\n";
    cout << "| |  | | | | |  \\| ||  \\| || |__ | |_/ / | |\n";
    cout << "| |/\\| | | | | . ` || . ` ||  __||    /| | |\n";
    cout << "\\  /\\  /_| |_| |\\  || |\\  || |___| |\\ \\|_|_|\n";
    cout << " \\/  \\/ \\___/\\_| \\_/\\_| \\_/\\____/\\_| \\_(_|_)\n";
    cout << RESET;
    cout << BIANCO_BRILLANTE;
    cout << "Il cavallo " << id + 1 << " - " << nomi[id] << " ha vinto la gara!!\n";
}

string get_data_ora() // Funzione per far restituire data e ora 
{ 
    time_t ora = time(0); 
    struct tm *data_ora = localtime(&ora); 
    char buffer[80]; 
    strftime(buffer, sizeof(buffer), "%d/%m/%Y %H:%M:%S", data_ora); 
    return string(buffer); 
}

void salvaRis(int id) {
    ofstream file ("risultati.txt", ios::app);

    if (!file) {
        cout << ROSSO_BRILLANTE << "Errore nell'apertura del file!!" << RESET;
        return;
    }

    string dataOra = get_data_ora();

    file << numCavalli << " " << nomi[id] << " " << dataOra << "\n";
    file.close();

    cout << GIALLO_BRILLANTE << "Risultati salvati in risultati.txt" << RESET;
}

void stampaRis() {
    ifstream file ("risultati.txt");

    if (!file) {
        cout << ROSSO_BRILLANTE << "Errore nell'apertura del file!!" << RESET;
    }
    clearScreen();

    cout << "=== Corse Totali ===" << endl;

    string dataOra = get_data_ora();

    int nCav;
    string nome, data;

    while (file >> nCav >> nome) {
        getline(file, dataOra); // legge il resto della riga (data + ora)
        dataOra = dataOra.substr(1); // rimuove lo spazio iniziale

        cout << "N. Cavalli: " << nCav << endl;
        cout << "Nome Vincitore: " << nome << endl;
        cout << "Data e ora: " << dataOra << endl;
        cout << "================" << endl;
    }

    file.close();
}
