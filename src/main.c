#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int card[4] ;


double eval(double num1, char op, double num2){
    if (op == '+') {
        return num1 + num2;
    }
    else if (op == '-') {
        return num1 - num2;
    }
    else if (op == '*') {
        return num1 * num2;
    }
    else if (op == ':') {
        return num1 / num2;
    }
    else {
        printf("DEBUG");
    }
}

int card_to_num(char c){
    if (c == 'A' || c == 'a'){
        return 1;
    }
    if (c == 'J' || c == 'j'){
        return 11;
    }
    if (c == 'Q' || c == 'q'){
        return 12;
    }
    if (c == 'K' || c == 'k'){
        return 13;
    }
    else {
        return c - '0';
    }
}
void find(int * num){
    int goal = 24;
    char result [1000][30] = {"."}; 

    int count = 0; 
    char op [] = {'+','-','*',':'};

    clock_t start = clock();
    /* Permutasi angka */
    for (int l = 0; l < 4; l ++){
        int num1 = num[l];
        for (int m = 0; m < 4; m ++){
            if (m == l) {
                continue;
            }
            int num2 = num[m];
            for (int n = 0; n < 4; n ++){
                if (n == l || n == m){
                    continue;
                }
                int num3 = num[n];
                for (int o = 0; o < 4; o ++){
                    if (o == m || o == n || o == l){
                        continue;
                    }
                    int num4 = num[o];

                    /* Iterasi operator */
                    for (int i = 0 ; i < 4; i ++ ){
                        char op1 = op[i];
                        for (int j = 0; j < 4; j ++){
                            char op2 = op[j];
                            for (int k = 0; k < 4; k ++){
                                char op3 = op[k];

                                /* Kombinasi Parenthesis */

                                /* ((A op B) op C) op D */
                                if ((eval(eval(eval(num1, op1, num2), op2, num3), op3, num4)) == goal){
                                    sprintf(result[count], "((%d %c %d) %c %d) %c %d\n", num1, op1, num2, op2, num3, op3, num4);
                                    count ++;
                                }

                                /* (A op (B op C)) op D */
                                if ((eval(eval(num1, op1, eval(num2, op2, num3)), op3, num4)) == goal){
                                    sprintf(result[count], "(%d %c (%d %c %d)) %c %d\n", num1, op1, num2, op2, num3, op3, num4);
                                    count ++;
                                }
                                /* A op ((B op C) op D) */
                                if ((eval(num1, op1, eval(eval(num2, op2, num3), op3, num4))) == goal){
                                    sprintf(result[count], "%d %c ((%d %c %d) %c %d)\n", num1, op1, num2, op2, num3, op3, num4);
                                    count ++;
                                }

                                /* A op (B op (C op D)) */
                                if ((eval(num1, op1, eval(num2, op2, eval(num3, op3, num4)))) == goal){
                                    sprintf(result[count], "%d %c (%d %c (%d %c %d))\n", num1, op1, num2, op2, num3, op3, num4);
                                    count ++;

                                }
                                /* (A op B) op (C op D) */
                                if ((eval(eval(num1, op1, num2), op2, eval(num3, op3, num4))) == goal){
                                    sprintf(result[count], "(%d %c %d) %c (%d %c %d)\n", num1, op1, num2, op2, num3, op3, num4);
                                    count ++;
                                }
                            }
                        }
                    }


                    
                }
            }
        }
    }
    clock_t end = clock();
    printf("%d solutions found! \n",count);


    for (int i = 0; i < count; i ++){
        printf(result[i]);
    }

    double duration = (double) (end - start)/(CLOCKS_PER_SEC * 1000000);
    printf("Time taken to execute (microsecond): %f\n", duration);

    printf("Apakah anda ingin menyimpan hasil dalam file? (y/n) ");
    char cc;
    scanf(" %c",&cc);
    if (cc == 'y'){
        printf("Masukkan nama file :");
        char name[30];
        scanf("%s", name);
        strcat(name, ".txt");
        FILE *fp;
        fp = fopen(name, "w");
        for (int i = 0; i < count; i++){
            fputs(result[i], fp);
        }
        fclose(fp);
        printf("Hasil berhasil disimpan dalam file.\n");
    }
    else {
        printf("Hasil tidak disimpan pada file.\n");
    }
}

void menu(){
    int cards[4];
    printf("1. Masukkan Kartu\n");
    printf("2. Generate Random Cards\n");
    printf("3. EXIT\n");
    int cc;
    do {
        scanf("%d", &cc);
    } while (cc < 1 || cc > 3);
    
    if (cc == 1){
        printf("Silakan masukkan 4 buah kartu \neg: A 4 7 Q\n");
        char str[5][3] = {".",".",".",".","." };
        scanf("%s", str[0]);
        scanf("%s", str[1]);
        scanf("%s", str[2]);
        scanf("%s", str[3]);
        if (str[3][0] == '.'){
            printf("Kartu yang kamu masukkan kurang! Harap masukkan 4 kartu.\n");
            return;
        }
        else if (str[4][0] != '.'){
            printf("Kartu yang kamu masukkan terlalu banyak! Harap masukkan 4 kartu.\n");
            return;
        }
        else {
            for (int i = 0; i < 4; i ++){
                if (str[i][0] == 'J' || str[i][0] == 'j'){
                    cards[i] = 11;
                }
                else if (str[i][0] == 'Q' || str[i][0] == 'q'){
                    cards[i] = 12;
                }
                else if (str[i][0] == 'K' || str[i][0] == 'k'){
                    cards[i] = 13;
                }
                else if (str[i][0] == 'A' || str[i][0] == 'a'){
                    cards[i] = 1;
                }
                else {
                    cards[i] = atoi(str[i]);
                    if (cards[i] < 1 || cards[i] > 10) {
                        printf("Kartu yang kamu masukkan tidak valid! Harap masukkan kartu yang valid\nKartu yang valid yaitu: A, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, J, Q, K\n");
                        return;
                    }
                }

            }
        }
        find(cards);
    }
    else if (cc == 2){
        srand((unsigned int) time(NULL));
        int temp;

        printf("Kartu Anda adalah :");
        for (int i = 0; i < 4; i ++){
            temp = 1 + (rand() % 13);
            if (temp == 1){
                printf(" A");
            }
            else if (temp == 11){
                printf(" J");
            }
            else if (temp == 12){
                printf(" Q");
            }
            else if (temp == 13){
                printf(" K");
            }
            else {
                printf(" %d", temp);
            }
            cards[i] = temp;
        }
        putchar('\n');

        find(cards);
    }
    else if (cc == 3){
        printf("Bye-bye ~\n");
        exit(0);
    }
}

void init(){
    printf("Welcome to 24 Solver !\n");                                
}

int main(){
    init();
    while (1){
        menu();
    }
}
