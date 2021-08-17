#include "hangman_function.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <time.h>
#include <string>


bool arraysComparaison(std::vector <char> array1, std::vector <char> array2){

    for(int i=0; i<array1.size(); i++){
        if(array1[i] != array2[i]){
            return false;
        }
    }
    return true;
}


void displayVector(std::vector <char> array1){
    for(int i=0; i<array1.size(); i++){
        std::cout << array1[i] << ' ';
    }
    std::cout << std::endl;
}

void displayArrayTwoDimensions(char array1[][6], int arraySize){

    for(int i=0; i<arraySize; i++){
        for(int j=0; j<arraySize; j++){
            std::cout << array1[i][j];
        }
            std::cout << std::endl;
    }
}

void displayHangMan(int errors){
    char errorsArrayXy[14][2] = {
        {5, 0},
        {5, 2},
        {4, 1},
        {3, 1},
        {2, 1},
        {1, 1},
        {0, 2},
        {0, 3},
        {0, 4},
        {1, 4},
        {2, 4},
        {3, 4},
        {4, 3},
        {4, 5}
    };
    char arrayTempToDisplay[6][6] = {
        {' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' '}
    };
    char hangmanDraw[6][6] = {
        {' ', ' ', '_', '_', '_', ' '},
        {' ', '|', ' ', ' ', '|', ' '},
        {' ', '|', ' ', ' ', 'o', ' '},
        {' ', '|', ' ', ' ', '|', ' '},
        {' ', '|', ' ', '/', ' ', '\\'},
        {'/', ' ', '\\', ' ', ' ', ' '}
    };


    for(int i=0; i<errors; i++){
        arrayTempToDisplay[errorsArrayXy[i][0]][errorsArrayXy[i][1]] = hangmanDraw[errorsArrayXy[i][0]][errorsArrayXy[i][1]];
    }
    displayArrayTwoDimensions(arrayTempToDisplay, 6);


}

std::vector <char> getWord(){
    std::ifstream myFlow("./words.txt");
    std::vector <std::vector <char>> words;
    std::string line;
    srand(time(NULL));
    char fileChar;

    if(myFlow){
        while(getline(myFlow, line)){
            std::vector <char> wordChar(line.begin(), line.end());
            words.push_back(wordChar);
        }
    }else
    {
      std::cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << std::endl;
    }
    int rngWordIndex =  rand() %words.size() +1;
    return words[rngWordIndex-1];

}

void hangman(){
    srand(time(NULL));
    char hideLetter = '_';
    char userLetter;
    int isThere = 0;
    std::vector <char> myWord = getWord();
    std::vector <char> badLetter;
    std::vector <char> letterEntered(myWord.size());


    for(int i=0; i<myWord.size(); i++){

        letterEntered[i] = hideLetter;
        if(myWord[i] == ' '){
            letterEntered[i] = ' ';
        }
        std::cout << letterEntered[i] << ' ';

    }

    std::cout << std::endl;

    while(!arraysComparaison(letterEntered, myWord)){
            isThere = 0;
        std::cin >> userLetter;
        for(int i=0; i<myWord.size(); i++){
            if(userLetter == myWord[i]){
                letterEntered[i] = userLetter;
                isThere = 1;
            }
        }
        if(isThere == 0){
            badLetter.push_back(userLetter);
        }

        displayVector(letterEntered);
        std::cout << "Wrong letters : ";
        displayVector(badLetter);
        displayHangMan(badLetter.size());

        if(badLetter.size() == 14){
            std::cout << "Looser... the word was " << std::endl;
            displayVector(myWord);
            return;
        }
    }
    std::cout << " Well played ! ";
    return ;

}
