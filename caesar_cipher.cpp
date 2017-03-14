/* Szyfr Cezara */
#include <cctype>
#include <iostream>
#include <string>

using namespace std;

string encode(string, int);
string decode(string, int);

int main()
{
    for(int bajt = 32; bajt < 127; ++bajt)//tylko printable chars
        if(isprint(bajt))
            cout << bajt << char(bajt) << "; ";
            
    cout << endl << "szyfr: ";
    string test="tata}~", crypted, decrypted;
    cout << test << endl;
    crypted = encode(test,1);
    cout << crypted << endl;
    decrypted = decode(crypted,1);
    cout << decrypted << endl;
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