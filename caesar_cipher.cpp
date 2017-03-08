/* Szyfr Cezara */
#include <cctype>
#include <iostream>
#include <string>

using namespace std;

string encode(string, int);

int main()
{
    for(int bajt = 32; bajt < 127; ++bajt)
        cout << " bajt : " << bajt << char(bajt) << " ";//if(isprint(bajt))
            
    cout << endl << "szyfr: ";
    string test="tata", crypted;
    crypted = encode("tata}~",2);
    cout<<crypted;
    cout<<endl;
    return 0;
}



string encode(string Phrase, int key){
    string Crypted = Phrase;
    uint PhraseSize = Phrase.length();
    cout << "Rozmiar slowa: " << PhraseSize <<endl;
    int Tab[PhraseSize], sum, modulo;

    for(uint i = 0; i < Phrase.length(); i++){
        Tab[i] = Crypted[i] - '0';
        cout << "Bajt: " << Tab[i] << " Litera: " << Crypted[i];
        sum = Tab[i] + key;
        modulo = sum%127;
        if (modulo < 32) {
            Tab[i] = modulo + 33;
        }else{
            Tab[i] = modulo;
        }
        
        cout << " Bajt przesuniety: " << Tab[i] <<endl;
        Crypted[i] = Tab[i] + '0';
    }
    return Crypted;
}