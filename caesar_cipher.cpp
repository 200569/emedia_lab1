/* Szyfr Cezara */
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <cctype>
#include <cstring>

using namespace std;

string encode(string, int);
string decode(string, int);

int main()
{
    char ccase=0;
    string phrase, line, filename, crypted, decrypted;
    int key, length;
    int Tab[2][95];
    do{
        cout << " Menu:\n";
        cout << " a - pokaz obslugiwane znaki\n";
        cout << " 1. Szyfrowanie wiadomosci\n";
        cout << " 2. Deszyfrowanie wiadomosci\n";
        cout << " 3. Szyfrowanie pliku\n";
        cout << " 4. Deszyfrowanie pliku\n";
        cout << " --- \n";
        cin >> ccase;
        switch (ccase){
            case 'a': {
                filename = "parykluczy.txt";
                ofstream plikkluczy (filename);
                if (plikkluczy.is_open()){
                    for(int bajt = 32; bajt < 127; ++bajt)//tylko printable chars
                        if(isprint(bajt)){
                            cout << char(bajt) << " ";
                            char * buffer = new char [6];
                            buffer[0] = char(bajt);
                            buffer[1] = ' ';
                            buffer[2] = '-';
                            buffer[3] = ' ';
                            buffer[4] = char(bajt+1);
                            buffer[5] = '\r';
                            plikkluczy.write(buffer,5);
                            
                            delete[] buffer;
                        }
                    plikkluczy.close();
                    }
                cout << endl;
                
                break;}
            case '1':{
                cout << "Podaj ciag znakow do zaszyfrowania: ";
                cin >> phrase;
                cout << endl << "Podaj przesuniecie: ";
                cin >> key;
                cout << endl;
                crypted = encode(phrase,key);
                cout << "Zaszyfrowana fraza: " << crypted << endl << endl;
                break;}
            case '2':{
                cout << "Podaj ciag znakow do zdeszyfrowania: ";
                cin >> phrase;
                cout << endl << "Podaj przesuniecie: ";
                cin >> key;
                cout << endl;
                decrypted = decode(phrase,key);
                cout << "Zdeszyfrowana fraza: " << decrypted << endl << endl;
                break;}
            case '3':{
                filename = "in.txt";
                ifstream phrasefile (filename);
                if (phrasefile.is_open()){
                    phrasefile.seekg(0,phrasefile.end);
                    length = phrasefile.tellg();
                    phrasefile.seekg (0,phrasefile.beg);

                    char * buffer = new char [length];
                    cout << "Zczytano " << length << " znakow.\n";
                    phrasefile.read(buffer,length);
                    phrase = buffer;
                    delete[] buffer;
                    phrasefile.close();
                }else {
                    cout << "Nie moge otworzyc pliku " << filename << endl; 
                    break;
                }
                filename = "key.txt";
                ifstream keyfile(filename);
                if (keyfile.is_open()){
                    while (getline (keyfile,line) ){
                        istringstream dane(line);
                        dane >> key;
                    }
                    keyfile.close();
                }else {
                    cout << "Nie moge otworzyc pliku " << filename << endl; 
                    break;
                }
                cout << "Odczytany ciag: " << phrase << " \nKlucz: " << key << endl;
                crypted = encode(phrase,key);
                cout << "Zakodowany ciag: " << crypted << endl;
//zapis
                filename = "in2.txt";
                ofstream encodefile (filename);
                if (encodefile.is_open()){
                    
                    char * buffer = new char [length];
                    strcpy(buffer,crypted.c_str());
                    encodefile.write(buffer,length);
                    delete[] buffer;
                    encodefile.close();
                }else {
                    cout << "Nie moge otworzyc pliku " << filename << endl; 
                    break;
                }
                break;}
            case '4':{
                filename = "in2.txt";
                ifstream phrasefile (filename);
                if (phrasefile.is_open()){
                    phrasefile.seekg(0,phrasefile.end);
                    length = phrasefile.tellg();
                    phrasefile.seekg (0,phrasefile.beg);

                    char * buffer = new char [length];
                    cout << "Zczytano " << length << " znakow.\n";
                    phrasefile.read(buffer,length);
                    phrase = buffer;
                    delete[] buffer;
                    phrasefile.close();
                }else {
                    cout << "Nie moge otworzyc pliku " << filename << endl; 
                    break;
                }
                filename = "key.txt";
                ifstream keyfile(filename);
                if (keyfile.is_open()){
                    while (getline (keyfile,line) ){
                        istringstream dane(line);
                        dane >> key;
                    }
                    keyfile.close();
                }else {
                    cout << "Nie moge otworzyc pliku " << filename << endl; 
                    break;
                }
                cout << "Zakodowany ciag: " << phrase << " \nKlucz: " << key << endl;
                crypted = decode(phrase,key);
                cout << "Odkodowany ciag: " << crypted << endl;
//zapis
                filename = "out2.txt";
                ofstream encodefile (filename);
                if (encodefile.is_open()){
                    
                    char * buffer = new char [length];
                    strcpy(buffer,crypted.c_str());
                    encodefile.write(buffer,length);
                    delete[] buffer;
                    encodefile.close();
                }else {
                    cout << "Nie moge otworzyc pliku " << filename << endl; 
                    break;
                }
                break;}
            case '5':{
                filename = "parykluczy.txt";
                ifstream plik(filename);
                if (plik.is_open()){
                    for (int i = 1; i < 95; i++){
                        plik >> Tab[0][i];
                        plik >> Tab[1][i];
                    }
                    plik.close();
                }else {
                    cout << "Nie moge otworzyc pliku " << filename << endl; 
                    break;
                }
            }
            default :
                cout << "Niewlasciwy znak" <<endl;
        }
    }while(ccase != 'x');
       

    return 0;
}



string encode(string Phrase, int key){
    string Crypted = Phrase;
    uint PhraseSize = Phrase.length();
    //cout << "Rozmiar slowa: " << PhraseSize <<endl;
    int Tab[PhraseSize], sum, modulo;

    for(uint i = 0; i < Phrase.length(); i++){
        Tab[i] = Crypted[i] - '\0';
        //cout << "Bajt: " << Tab[i] << " Litera: " << Crypted[i];
        sum = Tab[i] + key;
        modulo = sum%127;
        if (modulo < 33) {
            Tab[i] = modulo + 32;
        }else{
            Tab[i] = modulo;
        }
        //cout << " Bajt przesuniety: " << Tab[i] << " literka: "<< char(Tab[i]) <<endl;
        Crypted[i] = '\0'+ Tab[i];
    }
    Crypted[PhraseSize] = '\0';
    return Crypted;
}

string decode(string Phrase, int key){
    string Decrypted = Phrase;
    uint PhraseSize = Phrase.length();
    //cout << "Rozmiar slowa: " << PhraseSize <<endl;
    int Tab[PhraseSize], sum, modulo;

    for(uint i = 0; i < Phrase.length(); i++){
        Tab[i] = Decrypted[i] - '\0';
        //cout << "Bajt: " << Tab[i] << " Litera: " << Crypted[i];
        sum = Tab[i] - key;
        modulo = sum%127;
        if (modulo < 33) {
            Tab[i] = 127-(32-modulo);
        }else{
            Tab[i] = modulo;
        }
        //cout << " Bajt przesuniety: " << Tab[i] << " literka: "<< char(Tab[i]) <<endl;
        Decrypted[i] = '\0'+ Tab[i];
    }
    Decrypted[PhraseSize] = '\0';
    return Decrypted;
}