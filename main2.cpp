#include <iostream>
#include <bits/stdc++.h>

void setup(char (*arr)[3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            arr[i][j] = '-';
        }
    }
};

void printErr(int scene) {
    switch (scene) {
        case 0:
            printf("Invalid input!\n");
            break;
        case 1:
            printf("Cannot assign O on an already assigned tile!\n");
            break;
    }
}

void printArr(char (*arr)[3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            std::cout << arr[i][j] << (j == 2 ? "\n" : " ");
        }
    }
}

int setO(char (*arr)[3], int pos) {
    int row = pos/3;
    int col = pos%3 - 1;
    if (arr[row][col] == '-') {
        arr[row][col] = 'O';
        return 1;
    } else {
        printErr(1);
        return 0;
    }
}
int setX(char (*arr)[3], int pos) {
    int row = pos/3;
    int col = pos%3 - 1;
    if (arr[row][col] == '-') {
        arr[row][col] = 'X';
        return 1;
    } else {
        return 0;
    }
}


int yourTurn(char (*arr)[3]) {
    bool check1 = false;
    std::string choice{};
    while (!check1) {
        printf("\nSelect a position (type 'quit' or 'exit' to quit the game): ");
        std::cin >> choice;
        if (choice == "quit" || choice == "exit") {
            printf("Goodbye!\n");
            return -1;
        }
        try {
            double pos = std::stod(choice);
            if (pos < 1 || pos > 9 || pos != floor(pos)) {
                printErr(0);
                return 0;
            } else {
                check1 = true;
                int check2 = setO(arr, int (pos));
                if (check2 == 0) {
                    return 0;
                }
            }
        }
        catch (std::invalid_argument& e) {
            printErr(0);
            return 0;
        }
    }
    return 1;
}

void botTurn(char (*arr)[3]) {
    int check = 0;
    int realpos = 0;
    while (check != 1) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<double> dis(1, 9);
        int pos = dis(gen);
        check = setX(arr, pos);
        realpos = pos;
    }
    printf("X is assigned on tile %i!\n\n", realpos);
}

int checkWinner (char (*arr)[3]) {
    std::string Opos{};
    std::string Xpos{};
    int cse = -1;
    int missing{};
    for (int i = 1; i <= 9; i++) {
        int row = i/3;
        int col = i%3 - 1;
        if (arr[row][col] == '-') {
            missing++;
        } else if (arr[row][col] == 'X') {
            Xpos += std::to_string(i);
        } else if (arr[row][col] == 'O') {
            Opos += std::to_string(i);
        }
    }
    for (char i : Opos) {
        if (i == '1') {
            cse = 1;
        }
        if (i == '2') {
            cse = 2;
        }
        if (i == '3') {
            cse = 3;
        }
        if (i == '4') {
            cse = 4;
        }
        if (i == '7') {
            cse = 5;
        }
        switch (cse) {
            case 1:
                for (int j = 1; j < Opos.size(); j++) {
                    if (Opos[j] == '2' && Opos[j+1] == '3') {
                        return 1;
                    }
                    if (Opos[j] == '4'){
                        for (int k = Opos.find('4')+1; k < Opos.size(); k++) {
                            if (Opos[k] == '7') {
                                return 1;
                            }
                        }
                    }
                    if (Opos[j] == '5'){
                        for (int k = Opos.find('5')+1; k < Opos.size(); k++) {
                            if (Opos[k] == '9') {
                                return 1;
                            }
                        }
                    }
                }
            case 2:
                for (int j = Opos.find('2')+1; j < Opos.size(); j++) {
                    if (Opos[j] == '5') {
                        for (int k = Opos.find('5')+1; k < Opos.size(); k++) {
                            if (Opos[k] == '8') {
                                return 1;
                            }
                        }
                    }
                }
            case 3:
                for (int j = Opos.find('3')+1; j < Opos.size(); j++) {
                    if (Opos[j] == '5') {
                        for (int k = Opos.find('5')+1; k < Opos.size(); k++) {
                            if (Opos[k] == '7') {
                                return 1;
                            }
                        }
                    }
                    if (Opos[j] == '6') {
                        for (int k = Opos.find('6')+1; k < Opos.size(); k++) {
                            if (Opos[k] == '9') {
                                return 1;
                            }
                        }
                    }
                }
            case 4:
                for (int j = Opos.find('4')+1; j < Opos.size(); j++) {
                    if (Opos[j] == '5') {
                        for (int k = Opos.find('5')+1; k < Opos.size(); k++) {
                            if (Opos[k] == '6') {
                                return 1;
                            }
                        }
                    }
                }
            case 5:
                for (int j = Opos.find('7')+1; j < Opos.size(); j++) {
                    if (Opos[j] == '8' && Opos[j+1] == '9') {
                        return 1;
                    }
                }
        }
    }
    cse = -1;
    for (char i : Xpos) {
        if (i == '1') {
            cse = 1;
        }
        if (i == '2') {
            cse = 2;
        }
        if (i == '3') {
            cse = 3;
        }
        if (i == '4') {
            cse = 4;
        }
        if (i == '7') {
            cse = 5;
        }
        switch (cse) {
            case 1:
                for (int j = 1; j < Xpos.size(); j++) {
                    if (Xpos[j] == '2' && Xpos[j+1] == '3') {
                        return 2;
                    }
                    if (Xpos[j] == '4'){
                        for (int k = Xpos.find('4')+1; k < Xpos.size(); k++) {
                            if (Xpos[k] == '7') {
                                return 2;
                            }
                        }
                    }
                    if (Xpos[j] == '5'){
                        for (int k = Xpos.find('5')+1; k < Xpos.size(); k++) {
                            if (Xpos[k] == '9') {
                                return 2;
                            }
                        }
                    }
                }
            case 2:
                for (int j = Xpos.find('2')+1; j < Xpos.size(); j++) {
                    if (Xpos[j] == '5') {
                        for (int k = Xpos.find('5')+1; k < Xpos.size(); k++) {
                            if (Xpos[k] == '8') {
                                return 2;
                            }
                        }
                    }
                }
            case 3:
                for (int j = Xpos.find('3')+1; j < Xpos.size(); j++) {
                    if (Xpos[j] == '5') {
                        for (int k = Xpos.find('5')+1; k < Xpos.size(); k++) {
                            if (Xpos[k] == '7') {
                                return 2;
                            }
                        }
                    }
                    if (Xpos[j] == '6') {
                        for (int k = Xpos.find('6')+1; k < Xpos.size(); k++) {
                            if (Xpos[k] == '9') {
                                return 2;
                            }
                        }
                    }
                }
            case 4:
                for (int j = Xpos.find('4')+1; j < Xpos.size(); j++) {
                    if (Xpos[j] == '5') {
                        for (int k = Xpos.find('5')+1; k < Xpos.size(); k++) {
                            if (Xpos[k] == '6') {
                                return 2;
                            }
                        }
                    }
                }
            case 5:
                for (int j = Xpos.find('7')+1; j < Xpos.size(); j++) {
                    if (Xpos[j] == '8' && Xpos[j+1] == '9') {
                        return 2;
                    }
                }
        }
    }
    if (missing == 0) {
        return -1;
    }
    return 0;
}

int main() {
    char table[3][3];
    int check;
    printf("Welcome!\n");
    printf("Default table: \n\n");
    setup(table);
    printArr(table);
    while (true) {
        check = yourTurn(table);
        if (check == -1) {
            break;
        }
        if (check == 1) {
            int check2 = checkWinner(table);
            if (check2 == -1) {
                printArr(table);
                printf("\nGame Over!\n");
                return 0;
            }
            if (check2 == 1) {
                printArr(table);
                printf("\nYou win!\n");
                return 0;
            }
            botTurn(table);
            int check3 = checkWinner(table);
            if (check3 == 2) {
                printArr(table);
                printf("\nBot wins...\n");
                return 0;
            }
            printArr(table);
        }
    }

    return 0;
}