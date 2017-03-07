/* Szyfr Cezara */
#include <cctype>
#include <iostream>
#include <string>

using namespace std;

string encode(string, int);

int main()
{
    for(int bajt = 0; bajt < 256; ++bajt)
        if(isprint(bajt))
            cout << char(bajt) << " ";
    cout << endl << "szyfr: ";
    string test="tata", crypted;
    crypted = encode("tata~",3);
    cout<<crypted;
    cout<<endl;
    return 0;
}



string encode(string Phrase, int key){
    string Crypted = Phrase;
    uint PhraseSize = Phrase.length();
    cout << "rozmiar slowa: " << PhraseSize <<endl;
    int Tab[PhraseSize], sum;

    for(uint i = 0; i < Phrase.length(); i++){
        Tab[i] = int(Crypted[i]);
        cout << "int: " <<Tab[i] << " litera: " << Crypted[i] <<endl;
        sum = Tab[i] + key;
        Tab[i] = sum%=255;
        Crypted[i] = char(Tab[i]);
    }
    return Crypted;
}