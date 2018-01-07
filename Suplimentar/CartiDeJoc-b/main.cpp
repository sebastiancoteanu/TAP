/*Se consideră o secvenţă de cărţi de joc luate din mai multe pachete de cărţi, aşezate întrun
teanc pe masă (carţile sunt date în secvenţă de la bază la vârf). O carte dintr-un pachet de
joc va fi reprezentată ca o pereche (număr, litera), unde numele sunt de la 2 la 14 (11 pentru
as, 12 pentru juvete, etc..) iar litera corespunde unui simbol (D – diamonds, H – hearts, C –
clubs, S – spades). Jokerii sunt reprezentați doar prin litera „J”. Din această secvenţă de cărţi
dorim să extragem un număr maxim de cărţi, respectând următoarele reguli: fiecare carte
extrasă este situată deasupra cărţii extrase anterior (astfel, cărţile extrase formează un subşir
al secvenţei date), iar cartea nou extrasă şi cea extrasă la pasul anterior trebuie să aibă același
număr sau să aibă același simbol sau una dintre ele să fie un Joker.
b)  Se folosește un pachet ”special” de cărți, ce conține cărți numerotate de la 1 la n (nu
doar pana la 14), cu n citit la intrare. Secvența dată la intrare este formată folosind
elemente dintr-un singur astfel de pachet de cărți. Să se găsească un șir de lungime
maximă cu proprietatea anterior descrisă.*/

#include <iostream>
#include <fstream>

using namespace std;

struct Card {
    char symbol;
    int value;
};

void readData(int &numberOfCards, int &maxCard, Card *(&cards)) {
    ifstream f;
    int i = 1, value = 0;
    char symbol;
    f.open("date.in");
    f >> numberOfCards >> maxCard;
    cards = new Card[maxCard + 1];
    while(f >> symbol) {
        if(symbol >= '0' && symbol <= '9') {
            value = value * 10 + (symbol - 48);
        } else {
            cards[i].value = value;
            cards[i].symbol = symbol;
            value = 0;
            i++;
        }
    }
    f.close();
}

void displayData(Card *cards, int *parentArray, int currentIndex) {
    if(currentIndex == 0) {
        return;
    }
    displayData(cards, parentArray, parentArray[currentIndex]);
    if(cards[currentIndex].symbol == 'J') {
        cout << cards[currentIndex].symbol << " / ";
    } else {
        cout << cards[currentIndex].value << " " << cards[currentIndex].symbol << " / ";
    }
}

void dp(int numberOfCards, int maxCard, Card *cards) {
    int *parentArray = new int[numberOfCards + 1](), *dynamicArray = new int[numberOfCards + 1](),
        *values = new int[maxCard + 1](), *symbols = new int[5](), currentSymbol, currentValue, i, j, k, maxIdx = 0;

    for(i = 1; i <= numberOfCards; i++) {
        currentSymbol = cards[i].symbol;
        currentValue = cards[i].value;
        if(currentSymbol == 'J') {
            for(j = 1; j <= maxCard; j++) {
                k = values[j];
                values[j] = i;
                if(dynamicArray[i] < dynamicArray[k] + 1) {
                    dynamicArray[i] = dynamicArray[k] + 1;
                    parentArray[i] = k;
                }
            }
            for(j = 1; j <= 4; j++) {
                k = symbols[j];
                symbols[j] = i;
                if(dynamicArray[k] + 1 > dynamicArray[i]) {
                    dynamicArray[i] = dynamicArray[k] + 1;
                    parentArray[i] = k;
                }
            }
        } else {
            j = values[currentValue];
            values[currentValue] = i;
            switch(currentSymbol) {
                case 'D':
                    k = symbols[1];
                    symbols[1] = i;
                    break;
                case 'H':
                    k = symbols[2];
                    symbols[2] = i;
                    break;
                case 'C':
                    k = symbols[3];
                    symbols[3] = i;
                    break;
                default:
                    k = symbols[4];
                    symbols[4] = i;
            }
            dynamicArray[i] = dynamicArray[j] + 1;
            parentArray[i] = j;
            if(dynamicArray[i] < dynamicArray[k] + 1) {
                dynamicArray[i] = dynamicArray[k] + 1;
                parentArray[i] = k;
            }
        }
    }

    for(i = 1; i <= numberOfCards; i++) {
        if(dynamicArray[maxIdx] < dynamicArray[i]) {
            maxIdx = i;
        }
    }
    displayData(cards, parentArray, maxIdx);
}

using namespace std;

int main()
{
    int numberOfCards, maxCard, i;
    Card *cards;
    readData(numberOfCards, maxCard, cards);
    dp(numberOfCards, maxCard, cards);
    return 0;
}
