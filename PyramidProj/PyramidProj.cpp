#include <iostream>
#include <string>
#include <iomanip>
#include <windows.h> //Sleep, COORD
#include <ctime>    //time()

using namespace std;

string aster(32, '*'), Sdash(58, '-'), under(70, '_');
bool isRepeated;

//for char positioning
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

class menu {
public:
    void welcome(int w, int l) {
        cout << R"( 


            =========================================
            =========================================
                                                
                                                  ________________
           /\                                     \              /
          /  \';.                                 '\      ##    /
        ##### \  ';.       -"'`     ,' '.    ..  .==\     ##   /
        ##  ## ##   ## ## ### ` ####  ## ## ### ' ##   #####  / 
       /#####   ## ##  ###  , ##   ## ### ##  ##. ## ##   ## /
      / ##        ##   ##  .  #### ## ##  , ` ## `## #### ##/
     /  ##       ##\ ;` ` -         `- -.           `',.\  /
    /_______________\                                   `\/

            =========================================
      
    )";
        cout << "    Win : " << w << endl;
        cout << "    \tLoss: " << l << endl;
        cout << "\t\t-------------------";
        cout << "\n\t\t[1]Play" << endl;
        cout << "\t\t[2]Instructions" << endl;
        cout << "\t\t[3]Exit" << endl;
        cout << "\t\t-------------------";

    }

    void instruct() {
        system("cls");
        cout << R"(
       
                                       INSTRUCTIONS:


                                                               /:\             
                /\ /\ /\ /\                                   /1:2\
                /\ /\ /\ /\                                  /::3::\                                                       
                                                                                                             
        1. Before the game, the player              2. Each Pyramid Chip consists 
            will choose only five (5) out               of numbers that correspond                      
            of eight Pyramid Chips                      to each side of the chip                       
                                                                                                   

                                                                                          
                    /:\ \##3##/                         
     Player's ->   /1:2\ \2#1/   <- Opponent's               /\  /\  /\   /\  /\
                  /::3::\ \#/                                I   II  III  IV  V
                                                         
        3. Compared to the player's,                4. With the player having the first
            the opponent's chip is inverted             turn, they will be prompted 
            and has a different color                   to choose a chip with a corresponding
                                                        number in their deck



                 /`\ \`````/ /`\                                  /:\ \::4::/
                / 1 \ \   / / 2 \                                /1:5\ \4:4/
               /.....\ \./ /.....\                              /::4::\ \:/

        5. After picking a chip, the                 6. If the chip is laid down beside 
            player will now choose a slot                the opponent's chip, the numbers
            to lay down the chip, with a                 from the adjacent sides will be compared.
            corresponding number                         If the player's chip has a higher number,
                                                        the opponent's chip will now belong to the 
                                                        player--Adding 1 point to the player's score



        7. The main goal to win the game
            is to gain more points than the
            opponent's until each deck is empty
                                                              

    )";


    }
};
class display {
public:
    void board() {
        gotoxy(22, 5); cout << "/`\\ \\`````/ /`\\";
        gotoxy(21, 6); cout << "/ 1 \\ \\   / / 2 \\";
        gotoxy(20, 7); cout << "/.....\\ \\./ /.....\\";
        gotoxy(20, 9); cout << "\\`````/ /`\\ \\`````/ /`\\";
        gotoxy(21, 10); cout << "\\   / / 3 \\ \\   / / 4 \\";
        gotoxy(22, 11); cout << "\\./ /.....\\ \\./ /.....\\";
        gotoxy(26, 13); cout << "\\`````/ /`\\ \\`````/";
        gotoxy(27, 14); cout << "\\   / / 5 \\ \\   /";
        gotoxy(28, 15); cout << "\\./ /.....\\ \\./";

    }

    void enChip(int i, int j, int k, int x, int y) {
        gotoxy(x, y); cout << "\\##" << k << "##/";
        gotoxy(x + 1, y + 1); cout << "\\" << j << "#" << i << "/";
        gotoxy(x + 2, y + 2); cout << "\\#/";

    }
    void enChipL(int i, int j, int k, int x, int y) {               //function if the chip was taken by player
        Sleep(400);
        gotoxy(x, y); cout << "\\::" << k << "::/";
        Sleep(400);
        gotoxy(x + 1, y + 1); cout << "\\" << j << ":" << i << "/";
        Sleep(400);
        gotoxy(x + 2, y + 2); cout << "\\:/";

    }
    void plChip(int i, int j, int k, int x, int y) {
        gotoxy(x + 2, y); cout << "/:\\";
        gotoxy(x + 1, y + 1); cout << "/" << i << ":" << j << "\\";
        gotoxy(x, y + 2); cout << "/::" << k << "::\\";
    }
    void plChipL(int i, int j, int k, int x, int y) {               //function if the chip was taken by opponent
        Sleep(400);
        gotoxy(x + 2, y); cout << "/#\\";
        Sleep(400);
        gotoxy(x + 1, y + 1); cout << "/" << i << "#" << j << "\\";
        Sleep(400);
        gotoxy(x, y + 2); cout << "/##" << k << "##\\";
    }
    void erase(int x, int y) {
        gotoxy(x, y); cout << "       ";
        gotoxy(x, y + 1); cout << "       ";
        gotoxy(x, y + 2); cout << "       ";
    }
};

class Cards {
public:
    int cardA[3] = { 2,7,3 };
    int cardB[3] = { 4,4,4 };
    int cardC[3] = { 8,1,1 };
    int cardD[3] = { 6,4,7 };
    int cardE[3] = { 5,9,4 };
    int cardF[3] = { 2,5,8 };
    int cardG[3] = { 2,6,2 };
    int cardH[3] = { 3,4,5 };

    void copyDeck(int num, int copy[3]) {                                   //copy chosen array into deck
        int i;
        switch (num) {
        case 1:
            for (i = 0; i < 3; ++i) {
                copy[i] = cardA[i];
            }
            break;
        case 2:
            for (i = 0; i < 3; ++i) {
                copy[i] = cardB[i];
            }
            break;
        case 3:
            for (i = 0; i < 3; ++i) {
                copy[i] = cardC[i];
            }
            break;
        case 4:
            for (i = 0; i < 3; ++i) {
                copy[i] = cardD[i];
            }
            break;
        case 5:
            for (i = 0; i < 3; ++i) {
                copy[i] = cardE[i];
            }
            break;
        case 6:
            for (i = 0; i < 3; ++i) {
                copy[i] = cardF[i];
            }
            break;
        case 7:
            for (i = 0; i < 3; ++i) {
                copy[i] = cardG[i];
            }
            break;
        case 8:
            for (i = 0; i < 3; ++i) {
                copy[i] = cardH[i];
            }
            break;
        }
    }


};

class player : public Cards {
public:
    int i, num1, num2, num3, num4, num5;
    int set1[3] = { 0 };
    int set2[3] = { 0 };
    int set3[3] = { 0 };
    int set4[3] = { 0 };
    int set5[3] = { 0 };
    void GetCard() {
        cout << under << endl;
        cout << under << endl;
        cout << "\n\n\t\t\t***********************" << endl;
        cout << "\t\t\t* PICK 5 CHIPS! (1-8) *" << endl;
        cout << "\t\t\t***********************";
        cout << R"(


            I  /:\        II  /:\       III  /:\        IV  /:\
              /2:7\          /4:4\          /8:1\          /6:4\ 
             /::3::\        /::4::\        /::1::\        /::7::\


            V  /:\        VI  /:\       VII  /:\       VIII /:\
              /5:9\          /2:5\          /2:6\          /3:4\
             /::4::\        /::8::\        /::2::\        /::5::\

    )";
        while (true) {
            cout << "\t" << Sdash;
            cout << "\n First Chip: ";
            cin >> num1;
            if (num1 < 1 || num1 > 8) {
                cout << "Please Choose from 1 to 8 only." << endl;
            }
            else {
                break;
            }
        }
        copyDeck(num1, set1);

        while (true) {
            cout << " Second Chip: ";
            cin >> num2;
            if (num2 == num1) {
                cout << "Chip Already Selected." << endl;
            }
            else if (num2 < 1 || num2 > 8) {
                cout << "Please Choose from 1 to 8 only." << endl;
            }
            else {
                break;
            }
        }
        copyDeck(num2, set2);

        while (true) {
            cout << " Third Chip: ";
            cin >> num3;
            if (num3 == num2 || num3 == num1) {
                cout << "Chip Already Selected." << endl;
            }
            else if (num3 < 1 || num3 > 8) {
                cout << "Please Choose from 1 to 8 only." << endl;
            }
            else {
                break;
            }
        }
        copyDeck(num3, set3);

        while (true) {
            cout << " Fourth Chip: ";
            cin >> num4;
            if (num4 == num3 || num4 == num2 || num4 == num1) {
                cout << "Chip Already Selected." << endl;
            }
            else if (num4 < 1 || num4 > 8) {
                cout << "Please Choose from 1 to 8 only." << endl;
            }
            else {
                break;
            }
        }
        copyDeck(num4, set4);

        while (true) {
            cout << " Fifth Chip: ";
            cin >> num5;
            if (num5 == num4 || num5 == num3 || num5 == num2 || num5 == num1) {
                cout << "Chip Already Selected." << endl;
            }
            else if (num5 < 1 || num5 > 8) {
                cout << "Please Choose from 1 to 8 only." << endl;
            }
            else {
                break;
            }
        }
        copyDeck(num5, set5);

    }
};

class enemy : public Cards {
public:
    int i = 0, j = 0;
    int enSet1[3] = { 0 };
    int enSet2[3] = { 0 };
    int enSet3[3] = { 0 };
    int enSet4[3] = { 0 };
    int enSet5[3] = { 0 };

    void GetNum() {
        int number;
        int arr[5] = { 0 };

        for (i = 0; i < 5; ++i) {
            do {
                isRepeated = false;
                number = (rand() % 8) + 1;
                for (j = 0; j < 5; ++j) {                              //to avoid repetition in random generated numbers
                    if (number == arr[j]) {
                        isRepeated = true;
                    }
                }
            } while (isRepeated == true);


            arr[i] = number;

        }

        copyDeck(arr[0], enSet1);
        copyDeck(arr[1], enSet2);
        copyDeck(arr[2], enSet3);
        copyDeck(arr[3], enSet4);
        copyDeck(arr[4], enSet5);

    }

};

class game : public player, public enemy, public display {
public:
    int p1, p2, p3, p4, p5, e1, e2, e3, e4, e5;
    int plPick, plSlot, enPick, enSlot, plPoint, enPoint, w;
    int plArr[3] = { 0 }, enArr[3] = { 0 };
    int picknum[5] = { 0 }, pickloc[5] = { 0 }, ennum[5] = { 0 }, enloc[5] = { 0 };
    int plBoard1[3];
    int plBoard2[3];
    int plBoard3[3];
    int plBoard4[3];
    int plBoard5[3];
    int enBoard1[3];
    int enBoard2[3];
    int enBoard3[3];
    int enBoard4[3];
    int enBoard5[3];
    void arrReset() {
        p1 = 0, p2 = 0, p3 = 0, p4 = 0, p5 = 0, e1 = 0, e2 = 0, e3 = 0, e4 = 0, e5 = 0;
        plPoint = 5, enPoint = 5;
        for (int i = 0; i < 5; i++) {
            picknum[i] = 0;
            pickloc[i] = 0;
            ennum[i] = 0;
            enloc[i] = 0;
        }
        for (int i = 0; i < 3; i++) {
            plBoard1[i] = 0;
            plBoard2[i] = 0;
            plBoard3[i] = 0;
            plBoard4[i] = 0;
            plBoard5[i] = 0;
            enBoard1[i] = 0;
            enBoard2[i] = 0;
            enBoard3[i] = 0;
            enBoard4[i] = 0;
            enBoard5[i] = 0;
        }
    }
    void deck() {
        gotoxy(12, 20); cout << "/:\\        /:\\        /:\\        /:\\        /:\\";
        gotoxy(11, 21); cout << "/" << set1[0] << ":" << set1[1] << "\\      /" << set2[0] << ":" << set2[1] <<
            "\\      /" << set3[0] << ":" << set3[1] << "\\      /" << set4[0] << ":" << set4[1] << "\\      /" << set5[0] << ":" << set5[1] << "\\";
        gotoxy(10, 22); cout << "/::" << set1[2] << "::\\    /::" << set2[2] << "::\\    /::" <<
            set3[2] << "::\\    /::" << set4[2] << "::\\    /::" << set5[2] << "::\\";
        gotoxy(13, 23); cout << "I         II         III        IV          V";
    }
    void setPlCard(int i) {


        gotoxy(50, 1); cout << "____________________";
        gotoxy(49, 2); cout << "/                   |";
        gotoxy(48, 3); cout << "/   ## YOUR TURN ##  |";
        gotoxy(47, 4); cout << "/_____________________|";

        do {
            isRepeated = false;
            gotoxy(7, 25); cout << "-------------------------------------------------";
            gotoxy(7, 26); cout << " Pick a Chip (1-5): ";
            cin >> plPick;
            gotoxy(37, 26); cout << "                                ";
            for (int j = 0; j < 5; ++j) {
                if (plPick == picknum[j]) {
                    gotoxy(37, 26); cout << "!! CHIP ALREADY SELECTED !!";
                    isRepeated = true;
                }
            }
            if (plPick < 1 || plPick > 5) {
                gotoxy(37, 26); cout << "!! CHOOSE FROM 1 TO 5 ONLY !!";
                isRepeated = true;
            }
        } while (isRepeated == true);

        picknum[i] = plPick;


        do {
            isRepeated = false;
            gotoxy(7, 27); cout << " Choose Slot (1-5): ";
            cin >> plSlot;
            gotoxy(37, 27); cout << "                             ";
            for (int j = 0; j < 5; ++j) {
                if (plSlot == pickloc[j]) {
                    gotoxy(37, 27); cout << "!! SLOT ALREADY OCCUPIED !!" << endl;
                    isRepeated = true;
                }
            }
            if (plSlot < 1 || plSlot > 5) {
                gotoxy(37, 27); cout << "!! CHOOSE FROM 1 TO 5 ONLY !!" << endl;
                isRepeated = true;
            }

        } while (isRepeated == true);

        pickloc[i] = plSlot;
        //player
        switch (plPick) {
        case 1:
            erase(10, 20);
            for (int j = 0; j < 3; ++j) {
                plArr[j] = set1[j];
            }
            break;
        case 2:
            erase(21, 20);
            for (int j = 0; j < 3; ++j) {
                plArr[j] = set2[j];
            }
            break;
        case 3:
            erase(32, 20);
            for (int j = 0; j < 3; ++j) {
                plArr[j] = set3[j];
            }
            break;
        case 4:
            erase(43, 20);
            for (int j = 0; j < 3; ++j) {
                plArr[j] = set4[j];
            }
            break;
        case 5:
            erase(54, 20);
            for (int j = 0; j < 3; ++j) {
                plArr[j] = set5[j];
            }
            break;
        }
    }
    void setEnCard(int i) {
        do {
            isRepeated = false;
            enPick = (rand() % 5) + 1;
            for (int j = 0; j < 5; ++j) {
                if (enPick == ennum[j]) {
                    isRepeated = true;
                }
            }
        } while (isRepeated == true);
        ennum[i] = enPick;

        do {
            isRepeated = false;
            enSlot = (rand() % 5) + 1;
            for (int j = 0; j < 5; ++j) {
                if (enSlot == enloc[j]) {
                    isRepeated = true;
                }
            }
        } while (isRepeated == true);
        enloc[i] = enSlot;

        //opponent
        switch (enPick) {
        case 1:
            for (int j = 0; j < 3; ++j) {
                enArr[j] = enSet1[j];
            }
            break;
        case 2:
            for (int j = 0; j < 3; ++j) {
                enArr[j] = enSet2[j];
            }
            break;
        case 3:
            for (int j = 0; j < 3; ++j) {
                enArr[j] = enSet3[j];
            }
            break;
        case 4:
            for (int j = 0; j < 3; ++j) {
                enArr[j] = enSet4[j];
            }
            break;
        case 5:
            for (int j = 0; j < 3; ++j) {
                enArr[j] = enSet5[j];
            }
            break;
        }
    }
    void plLocate() {
        gotoxy(50, 1); cout << "____________________";
        gotoxy(49, 2); cout << "/                   |";
        gotoxy(48, 3); cout << "/   OPPONENT'S TURN! |";
        gotoxy(47, 4); cout << "/_____________________|";
        switch (plSlot) {
        case 1:
            plChip(plArr[0], plArr[1], plArr[2], 20, 5);
            for (int j = 0; j < 3; ++j) {
                plBoard1[j] = plArr[j];
            }
            if (plBoard1[1] > enBoard5[1] && enBoard5[1] != 0 && e5 == 0) {
                e5++;
                enChipL(enBoard5[0], enBoard5[1], enBoard5[2], 26, 5);
                plPoint++;
                enPoint--;
            }
            if (plBoard1[2] > enBoard4[2] && enBoard4[2] != 0 && e4 == 0) {
                e4++;
                enChipL(enBoard4[0], enBoard4[1], enBoard4[2], 20, 9);
                plPoint++;
                enPoint--;
            }
            break;
        case 2:
            plChip(plArr[0], plArr[1], plArr[2], 32, 5);
            for (int j = 0; j < 3; ++j) {
                plBoard2[j] = plArr[j];
            }
            if (plBoard2[0] > enBoard5[0] && enBoard5[0] != 0 && e5 == 0) {
                e5++;
                enChipL(enBoard5[0], enBoard5[1], enBoard5[2], 26, 5);
                plPoint++;
                enPoint--;
            }
            if (plBoard2[2] > enBoard3[2] && enBoard3[2] != 0 && e3 == 0) {
                e3++;
                enChipL(enBoard3[0], enBoard3[1], enBoard3[2], 32, 9);
                plPoint++;
                enPoint--;
            }
            break;
        case 3:
            plChip(plArr[0], plArr[1], plArr[2], 26, 9);
            for (int j = 0; j < 3; ++j) {
                plBoard3[j] = plArr[j];
            }
            if (plBoard3[0] > enBoard4[0] && enBoard4[0] != 0 && e4 == 0) {
                e4++;
                enChipL(enBoard4[0], enBoard4[1], enBoard4[2], 20, 9);
                plPoint++;
                enPoint--;
            }
            if (plBoard3[1] > enBoard3[1] && enBoard3[1] != 0 && e3 == 0) {
                e3++;
                enChipL(enBoard3[0], enBoard3[1], enBoard3[2], 32, 9);
                plPoint++;
                enPoint--;
            }
            if (plBoard3[2] > enBoard2[2] && enBoard2[2] != 0 && e2 == 0) {
                e2++;
                enChipL(enBoard2[0], enBoard2[1], enBoard2[2], 26, 13);
                plPoint++;
                enPoint--;
            }
            break;
        case 4:
            plChip(plArr[0], plArr[1], plArr[2], 38, 9);
            for (int j = 0; j < 3; ++j) {
                plBoard4[j] = plArr[j];
            }
            if (plBoard4[0] > enBoard3[0] && enBoard3[0] != 0 && e3 == 0) {
                e3++;
                enChipL(enBoard3[0], enBoard3[1], enBoard3[2], 32, 9);
                plPoint++;
                enPoint--;
            }
            if (plBoard4[2] > enBoard1[2] && enBoard1[2] != 0 && e1 == 0) {
                e1++;
                enChipL(enBoard1[0], enBoard1[1], enBoard1[2], 38, 13);
                plPoint++;
                enPoint--;
            }
            break;
        case 5:
            plChip(plArr[0], plArr[1], plArr[2], 32, 13);
            for (int j = 0; j < 3; ++j) {
                plBoard5[j] = plArr[j];
            }
            if (plBoard5[0] > enBoard2[0] && enBoard2[0] != 0 && e2 == 0) {
                e2++;
                enChipL(enBoard2[0], enBoard2[1], enBoard2[2], 26, 13);
                plPoint++;
                enPoint--;
            }
            if (plBoard5[1] > enBoard1[1] && enBoard1[1] != 0 && e1 == 0) {
                e1++;
                enChipL(enBoard1[0], enBoard1[1], enBoard1[2], 38, 13);
                plPoint++;
                enPoint--;
            }
            break;
        }
    }
    void enLocate() {
        switch (enSlot) {
        case 1:
            enChip(enArr[0], enArr[1], enArr[2], 38, 13);
            for (int j = 0; j < 3; ++j) {
                enBoard1[j] = enArr[j];
            }
            if (enBoard1[1] > plBoard5[1] && plBoard5[1] != 0 && p5 == 0) {
                p5++;
                plChipL(plBoard5[0], plBoard5[1], plBoard5[2], 32, 13);
                enPoint++;
                plPoint--;
            }
            if (enBoard1[2] > plBoard4[2] && plBoard4[2] != 0 && p4 == 0) {
                p4++;
                plChipL(plBoard4[0], plBoard4[1], plBoard4[2], 38, 9);
                enPoint++;
                plPoint--;
            }
            break;
        case 2:
            enChip(enArr[0], enArr[1], enArr[2], 26, 13);
            for (int j = 0; j < 3; ++j) {
                enBoard2[j] = enArr[j];
            }
            if (enBoard2[0] > plBoard5[0] && plBoard5[0] != 0 && p5 == 0) {
                p5++;
                plChipL(plBoard5[0], plBoard5[1], plBoard5[2], 32, 13);
                enPoint++;
                plPoint--;
            }
            if (enBoard2[2] > plBoard3[2] && plBoard3[2] != 0 && p3 == 0) {
                p3++;
                plChipL(plBoard3[0], plBoard3[1], plBoard3[2], 26, 9);
                enPoint++;
                plPoint--;
            }
            break;
        case 3:
            enChip(enArr[0], enArr[1], enArr[2], 32, 9);
            for (int j = 0; j < 3; ++j) {
                enBoard3[j] = enArr[j];
            }
            if (enBoard3[0] > plBoard4[0] && plBoard4[0] != 0 && p4 == 0) {
                p4++;
                plChipL(plBoard4[0], plBoard4[1], plBoard4[2], 38, 9);
                enPoint++;
                plPoint--;
            }
            if (enBoard3[1] > plBoard3[1] && plBoard3[1] != 0 && p3 == 0) {
                p3++;
                plChipL(plBoard3[0], plBoard3[1], plBoard3[2], 26, 9);
                enPoint++;
                plPoint--;
            }
            if (enBoard3[2] > plBoard2[2] && plBoard2[2] != 0 && p2 == 0) {
                p2++;
                plChipL(plBoard2[0], plBoard2[1], plBoard2[2], 32, 5);
                enPoint++;
                plPoint--;
            }
            break;
        case 4:
            enChip(enArr[0], enArr[1], enArr[2], 20, 9);
            for (int j = 0; j < 3; ++j) {
                enBoard4[j] = enArr[j];
            }
            if (enBoard4[0] > plBoard3[0] && plBoard3[0] != 0 && p3 == 0) {
                p3++;
                plChipL(plBoard3[0], plBoard3[1], plBoard3[2], 26, 9);
                enPoint++;
                plPoint--;
            }
            if (enBoard4[2] > plBoard1[2] && plBoard1[2] != 0 && p1 == 0) {
                p1++;
                plChipL(plBoard1[0], plBoard1[1], plBoard1[2], 20, 5);
                enPoint++;
                plPoint--;
            }
            break;
        case 5:
            enChip(enArr[0], enArr[1], enArr[2], 26, 5);
            for (int j = 0; j < 3; ++j) {
                enBoard5[j] = enArr[j];
            }
            if (enBoard5[0] > plBoard2[0] && plBoard2[0] != 0 && p2 == 0) {
                p2++;
                plChipL(plBoard2[0], plBoard2[1], plBoard2[2], 32, 5);
                enPoint++;
                plPoint--;
            }
            if (enBoard5[1] > plBoard1[1] && plBoard1[2] != 0 && p1 == 0) {
                p1++;
                plChipL(plBoard1[0], plBoard1[1], plBoard1[2], 20, 5);
                enPoint++;
                plPoint--;
            }
            break;
        }
    }
    void score() {
        for (int i = 0; i < 10; i++) {
            gotoxy(70, i); cout << "**";
            gotoxy(89, i); cout << "**";
        }
        gotoxy(70, 10); cout << "**-----------------**\n";
        gotoxy(70, 11); cout << "**    S C O R E    **\n";
        gotoxy(70, 12); cout << "**                 **\n";
        gotoxy(70, 13); cout << "**                 **\n";
        gotoxy(70, 14); cout << "**  PLAYER  : " << plPoint << "\t **\n";
        gotoxy(70, 15); cout << "**  OPPONENT: " << enPoint << "\t **\n";
        gotoxy(70, 16); cout << "**-----------------**\n";
        for (int i = 0; i < 12; i++) {
            gotoxy(70, 17 + i); cout << "**";
            gotoxy(89, 17 + i); cout << "**";
            gotoxy(0, 29); cout << aster << aster << "***************************";
        }
    }
    void result() {
        if (plPoint > enPoint) {
            w = 1;
            gotoxy(2, 18);  cout << R"(

        ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
        :: ##  ##   ####   ##  ##    ##      ##  ##  ###  ##    ##  ::
        ::  ####   ##  ##  ##  ##    ##  ##  ##  ##  ## # ##    ##  ::
        ::   ##    ##  ##  ##  ##     ## ## ##   ##  ##  ###        ::
        ::   ##     ####    ####       ##  ##    ##  ##   ##    ##  ::
        ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
            'Enter any character to return to main menu'
            ``````````````````````````````````````````````

    )";
        }
        else if (plPoint < enPoint) {
            w = 2;
            gotoxy(2, 18);  cout << R"(

        ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
        :: ##  ##   ####   ##  ##    ;;      ;;;;   ;;;;; ;;;;;;    ::
        ::  ####   ##  ##  ##  ##    ;;     ;;  ;; ;;;    ;;        ::
        ::   ##    ##  ##  ##  ##    ;;     ;;  ;;    ;;; ;;--      ::
        ::   ##     ####    ####     ;;;;;;  ;;;;  ;;;;;  ;;;;;;    ::
        ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
                'Enter any character to return to main menu'
                ````````````````````````````````````````````                 

    )";
        }
        else {
            w = 0;
            gotoxy(2, 18);  cout << R"(

        ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
        ::         =====   =====    =====   ==      ==   ==         ::
        ::         ==  ==  ==  ==  ==   ==  ==  ==  ==   ==         ::
        ::         ==  ==  ====    =======   == == ==               ::
        ::         =====   ==  ==  ==   ==    ==  ==     ==         ::
        ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
                'Enter any character to return to main menu'
                ````````````````````````````````````````````

    )";
        }
    }
};


int main()
{
    menu m;
    game play;
    int i, menum, win = 0, lose = 0;
    char rtrn;
    srand(time(NULL));

    system("cls");

    while (true) {

        system("cls");
        m.welcome(win, lose);

        cout << "\n\tEnter number: ";
        cin >> menum;
        switch (menum) {
        case 1:
            system("cls");
            play.GetCard();
            play.GetNum();
            system("cls");
            cout << under << endl;
            cout << under << endl;
            play.arrReset();
            play.board();
            play.deck();

            for (i = 0; i < 5; ++i) {
                play.score();
                play.setPlCard(i);
                play.plLocate();
                Sleep(1500);
                play.setEnCard(i);
                play.enLocate();

            }
            play.score();
            play.result();

            if (play.w == 1) {
                win++;
            }
            else if (play.w == 2) {
                lose++;
            }

            cin >> rtrn;
            break;
        case 2:
            m.instruct();
            cout << "\n   'Enter a character to return to Main Menu'";
            cin >> rtrn;
            break;
        case 3:
            return 0;
        }


    }
}


