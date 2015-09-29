#include<stdio.h>
#include<iostream>
#include<fstream>
#include<stdlib.h>

using namespace std;

char* filename;
char* input;
char* output;
int size;
int count[26];
int countD[26 * 26];

void getSize() {
	char c;
	FILE *fd;
	fd = fopen(filename, "r");
	int i = 0;
	while((c = fgetc(fd)) != EOF) {
			i++;
	}
	fclose(fd);
    size = i;
    input = (char *) calloc(size, sizeof(char));
    output = (char *) calloc(size, sizeof(char));
}


void readfile() {
    getSize();
    ifstream infile;
    infile.open(filename);
    if (infile.is_open()) {
        while (!infile.eof()) {
	        infile >> input;
	    }
    }
    infile.close();
}

void printOrder() {
    int index = 0;
    int most = -1;
    int total = 0;
    for(int i = 0; i < 26; i++) {
        for(int j = 0; j < 26; j++) {
            if(count[j] > most) {
                most = count[j];
                index = j;
            }
        }
        char c = 'A' + index;
        cout << c << ": " << most << '\n';
        total += most;
        most = -1;
        count[index] = -2;
    }
}

void printDoubles() {
    int index = 0;
    int most = -1;
    for(int i = 0; i < 26*26; i++) {
        for(int j = 0; j < 26*26; j++) {
            if(countD[j] > most) {
                most = countD[j];
                index = j;
            }
        }
        char c1 = 'A' + (index / 26);
        char c2 = 'A' + (index % 26);
        if(most > 9)
            cout << c1 << c2 << ": " << most << '\n';
        most = -1;
        countD[index] = -2;
    }
}

void countLetters() {
    for(int i = 0; i < size; i++) {
        if(input[i] != '\n')
            count[input[i]-'A']++;
    }
}

void countDoubles() {
    for(int i = 0; i < size - 1; i += 2) {
        if(input[i] != '\n' || input[i+1] != '\n') {
            countD[(input[i]-'A')*26 + (input[i+1] - 'A')]++;
        }
        else {
            break;
        }
    }
}

void printCypher() {
    for(int i = 0; i < size; i++) {
            cout << input[i];
    }
    cout << "\n\n";
}

//SOLVED
void subDecryption() {
    for(int i = 0; i < size; i++) {
        switch(input[i]) {
            case 'C': cout << 'A'; break;//lock
            case 'G': cout << 'O'; break;//lock
            case 'A': cout << 'T'; break;//lock
            case 'R': cout << 'E'; break;//lock
            case 'Q': cout << 'H'; break;//lock
            case 'E': cout << 'N'; break;//lock
            case 'W': cout << 'D'; break;//lock
            case 'P': cout << 'I'; break;//lock
            case 'S': cout << 'S'; break;//lock
            case 'L': cout << 'M'; break;//lock
            case 'I': cout << 'C'; break;//lock
            case 'M': cout << 'R'; break;//lock
            case 'B': cout << 'W'; break;//lock
            case 'O': cout << 'L'; break;//lock
            case 'V': cout << 'G'; break;//lock
            case 'X': cout << 'U'; break;//lock
            case 'Y': cout << 'P'; break;//lock
            case 'J': cout << 'B'; break;//lock
            case 'Z': cout << 'Y'; break;//lock
            case 'F': cout << 'F'; break;//lock
            case 'N': cout << 'K'; break;//lock
            case 'U': cout << 'V'; break;//lock
            case 'D': cout << 'X'; break;//lock
            case 'H': cout << 'J'; break;//lock
            case 'K': cout << 'Q'; break;//lock
            case 'T': cout << 'Z'; break;//lock
            default: break;
        }
    }
    cout << '\n';
}

void decryptPoints(char playfair[25], int c1c, int c1r, int c2c, int c2r, int i) {
    if(c1c == c2c) {
        if(c1r == 0) {
            c1r = 4;
        }
        else {
            c1r = (c1r - 1) % 5;
        }
        if(c2r == 0) {
            c2r = 4;
        }
        else {
            c2r = (c2r - 1) % 5;
        }
    }
    else if(c1r == c2r) {
        if(c1c == 0) {
            c1c = 4;
        }
        else {
            c1c = (c1c - 1) % 5;
        }
        if(c2c == 0) {
            c2c = 4;
        }
        else {
            c2c = (c2c - 1) % 5;
        }
    }
    else {
        swap(c1c, c2c);
    }
    int coord1 = c1r*5 + c1c;
    int coord2 = c2r*5 + c2c;
    output[i] = playfair[coord1];
    output[i+1] = playfair[coord2];
    //cout << playfair[coord1] << playfair[coord2];
}

int findCoord(char playfair[25], char letter) {
    for(int i = 0; i < 25; i++) {
        if(playfair[i] == letter)
            return i;
    }
    return 26;
}
//I == J UNSOLVED
//row = coord/5; column = coord % 5;
/*    char playfair[25] = {
        'A', 'B', 'C', 'D', 'E',
        'F', 'G', 'H', 'I', 'K',
        'L', 'M', 'N', 'O', 'P',
        'Q', 'R', 'S', 'T', 'U',
        'V', 'W', 'X', 'Y', 'Z'
    };*/
void setPast(char past[25], char present[25]) {
    for(int i = 0; i < 25; i++)
        past[i] = present[i];
}

void resetPresent(char past[25], char present[25]) {
    for(int i = 0; i < 25; i++)
        present[i] = past[i];
}

void randomize(char present[25]) {
    swap(present[rand() % 25],present[rand() % 25]);
}

void resetCount() {
    for(int i = 0; i < 26*26; i++) {
        countD[i] = 0;
    }
}

int fitness() {
    int fit = 0;
    resetCount();
    for(int i = 0; i < size - 1; i += 1) {
        if(output[i] != '\n' || output[i+1] != '\n' || output[i+2] != '\n' || output[i+3] != '\n') {
            if(output[i] == 'Q' || output[i] == 'Z' || output[i] == 'K') fit -= 5;
            if(output[i] == 'E' || output[i] == 'T' || output[i] == 'A' || output[i] == 'O' || output[i] == 'I') fit += 1;
            if(output[i] == output[i+1]) fit -= 20;
            if(output[i] == 'T' && output[i+1] == 'H') fit+= 3;
            if(output[i] == 'H' && output[i+1] == 'E') fit+= 3;
            if(output[i] == 'A' && output[i+1] == 'N') fit+= 3;
            if(output[i] == 'I' && output[i+1] == 'N') fit+= 3;
            if(output[i] == 'E' && output[i+1] == 'R') fit+= 3;
            if(output[i] == 'O' && output[i+1] == 'N') fit+= 3;
            if(output[i] == 'R' && output[i+1] == 'E') fit+= 2;
            if(output[i] == 'E' && output[i+1] == 'D') fit+= 2;
            if(output[i] == 'N' && output[i+1] == 'D') fit+= 2;
            if(output[i] == 'H' && output[i+1] == 'A') fit+= 2;
            if(output[i] == 'A' && output[i+1] == 'T') fit+= 2;
            if(output[i] == 'E' && output[i+1] == 'N') fit+= 2;
            if(output[i] == 'E' && output[i+1] == 'S') fit+= 2;
            if(output[i] == 'O' && output[i+1] == 'F') fit+= 2;
            if(output[i] == 'N' && output[i+1] == 'T') fit+= 2;
            if(output[i] == 'E' && output[i+1] == 'A') fit+= 2;
            if(output[i] == 'T' && output[i+1] == 'I') fit+= 2;
            if(output[i] == 'T' && output[i+1] == 'O') fit+= 2;
            if(output[i] == 'E' && output[i+1] == 'N') fit+= 2;
            if(output[i] == 'D' && output[i+1] == 'O' && output[i+2] == 'T') fit+= 15;
            if(output[i] == 'T' && output[i+1] == 'H' && output[i+2] == 'E') fit+= 8;
            if(output[i] == 'A' && output[i+1] == 'N' && output[i+2] == 'D') fit+= 8;
            if(output[i] == 'T' && output[i+1] == 'H' && output[i+2] == 'A') fit+= 8;
            if(output[i] == 'E' && output[i+1] == 'N' && output[i+2] == 'T') fit+= 7;
            if(output[i] == 'I' && output[i+1] == 'O' && output[i+2] == 'N') fit+= 6;
            if(output[i] == 'T' && output[i+1] == 'I' && output[i+2] == 'O') fit+= 6;
            if(output[i] == 'F' && output[i+1] == 'O' && output[i+2] == 'R') fit+= 6;
            if(output[i] == 'G' && output[i+1] == 'H' && output[i+2] == 'T') fit+= 6;
            if((output[i] == output[i+1]) == output[i+2]) fit-= 15;
            if(output[i] == 'T' && output[i+1] == 'H' && output[i+2] == 'A' && output[i+3] == 'T') fit+= 10;
            if(output[i] == 'T' && output[i+1] == 'H' && output[i+2] == 'E' && output[i+3] == 'N') fit+= 10;
            if(output[i] == 'T' && output[i+1] == 'H' && output[i+2] == 'E' && output[i+3] == 'M') fit+= 10;
            if(output[i] == 'W' && output[i+1] == 'I' && output[i+2] == 'T' && output[i+3] == 'H') fit+= 10;
            if(output[i] == 'H' && output[i+1] == 'A' && output[i+2] == 'V' && output[i+3] == 'E') fit+= 10;
            if(output[i] == 'H' && output[i+1] == 'A' && output[i+2] == 'R' && output[i+3] == 'X' && output[i+4] == 'R' && output[i+5] == 'Y') fit+= 100;
            if(output[i] == 'C' && output[i+1] == 'O' && output[i+2] == 'M' && output[i+3] == 'X' && output[i+4] == 'M' && output[i+5] == 'A') fit+= 100;
            if(((output[i] == output[i+1]) == output[i+2]) == output[i+3]) fit-= 20;
            if(i > 0 && output[i] == 'X' && output[i-1] == output[i+1]) fit += 5;
            else if(output[i] == 'X') fit -= 20;
        }
        else {
            break;
        }
    }
    return fit;
}

void printTable(char key[25]) {
    for(int i = 0; i < 25; i++) {
        if(i % 5 == 0)
            cout << '\n';
        cout << "'" <<key[i] <<"'"<<",";
    }
}

/*

*/
//efadas == comxma
void memetic() {
    srand(time(NULL));
    int pastfit = 1753;
    int presentfit = 100;
    char past[25] = {
        'Q','N','V','P','Y',
        'K','O','H','F','W',
        'I','L','M','A','S',
        'G','E','U','C','R',
        'Z','T','D','X','B'
    };
    char present[25];
    resetPresent(past, present);
    int count = 0;
    
    for(int j = 0; j < 1000000; j++) {
        randomize(present);
        for(int i = 0; i < size - 1; i+=2) {
            int coord1 = findCoord(present, input[i]);
            int coord2 = findCoord(present, input[i+1]);
            if(coord1 != 26 && coord2 != 26)
                decryptPoints(present, coord1 % 5, coord1 / 5, coord2 % 5, coord2 / 5, i);
        }
        presentfit = fitness();
        if(presentfit < pastfit) {
            count++;
            presentfit = pastfit;
            resetPresent(past, present);
        }
        else {
            count = 0;
            pastfit = presentfit;
            setPast(past, present);
        }
        if(count == 5 && pastfit <= 1753 && j < 1000000-1) {
            for(int k = 0; k < count; k++)
                randomize(present);
            count = 0;
        }
    }
    
    for(int i = 0; i < size - 1; i+=2) {
        int coord1 = findCoord(present, input[i]);
        int coord2 = findCoord(present, input[i+1]);
        if(coord1 != 26 && coord2 != 26)
            decryptPoints(present, coord1 % 5, coord1 / 5, coord2 % 5, coord2 / 5, i);
        else cout << "__";
    }
    presentfit = fitness();
    printTable(present);
    cout << presentfit << '\n';
    for(int i = 0; i < size; i++) {
        cout << output[i];
    }
    cout << "\n\n";
}

void playDecryption() {
    char playfair[25] = {
        'L','X','T','D','Y',
        'E','R','S','A','G',
        'W','I','U','O','Z',
        'N','V','M','F','Q',
        'H','K','P','C','B'
    };
    for(int i = 0; i < size - 1; i+=2) {
        int coord1 = findCoord(playfair, input[i]);
        int coord2 = findCoord(playfair, input[i+1]);
        if(coord1 != 26 && coord2 != 26)
            decryptPoints(playfair, coord1 % 5, coord1 / 5, coord2 % 5, coord2 / 5, i);
        else cout << "__";
    }
    for(int i = 0; i < size; i++) {
        cout << output[i];
    }
    cout << "\n\n";
}

void printWithoutX() {
    for(int i = 0; i < size; i++) {
        if(output[i] != 'X') {
            cout << output[i];
        }
    }
    cout << "\n\n";
}

int main(int argc, char** argv) {
    filename = argv[1];
    readfile();
    if(argc == 2) {
        printCypher();
        subDecryption();
    }
    if(argc == 3) {
        memetic();
        //playDecryption();
        //countLetters();
        //printOrder();
        //countDoubles();
        //printDoubles();
        //printCypher();
        //playDecryption();
        //printWithoutX();
    }
    free(input);
    free(output);
    return 0;
}
