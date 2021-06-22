// Page Replacement Algorithm.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;
void START_MENU()
{
    printf(" _________________________________________\n");
    printf("|  -----Page Replacement Algorithm-----   |\n");
    printf("|      1. Default referenced sequence     |\n");
    printf("|      2. Manual input sequence           |\n");
    printf("|_________________________________________|\n");
    printf("Choice:");
}
void MANUALINPUT()
{
    printf(" _________________________________________\n");
    printf("|  -----Page Replacement Algorithm-----   |\n");
    printf("|_________________________________________|\n");
    printf("Sequence length:");
}
void FRAMEINPUT()
{
    printf(" _________________________________________\n");
    printf("|  -----Page Replacement Algorithm-----   |\n");
    printf("|_________________________________________|\n");
    printf("Input page frames:");
}

void ALGORITHM_MENU()
{
    printf(" _________________________________________\n");
    printf("|  -----Page Replacement Algorithm-----   |\n");
    printf("|          1. FIFO algorithm              |\n");
    printf("|          2. OPT algorithm               |\n");
    printf("|          3. LRU algorithm               |\n");
    printf("|_________________________________________|\n");
    printf("Choice:");
}
int COUNTCHAR(int n) {
    int dem = 0;
    while (n >= 10) {
        n /= 10;
        dem++;
    }
    return dem;
}
void PRINTTABLE(int** table, int rowheight, int leng, int* faultaru)
{
    int* space = new int[leng];
    for (int len = 0;len < leng;len++)
    {
        space[len] = 0;
        for (int row = 0;row < rowheight;row++)
        {
            if (COUNTCHAR(table[row][len]) > space[len])
            {
                space[len] = COUNTCHAR(table[row][len]);
            }
        }
    }
    for (int row = 0;row < rowheight;row++)
    {
        for (int len = 0;len < leng;len++)
        {
            if (table[row][len] != -1) cout << table[row][len];
            else cout << " ";
            for (int count = COUNTCHAR(table[row][len]);count < space[len] + 2;count++)
            {
                cout << " ";
            }
        }
        cout << endl;
    }
    for (int len = 0;len < leng;len++)
    {
        if (faultaru[len] == 1) cout << "*";
        else cout << " ";
        for (int j = 0;j < space[len] + 2;j++) cout << " ";
    }
    int dem = 0;
    for (int i = 0;i < leng;i++) if (faultaru[i] == 1) dem++;
    cout << "\nNumber of Page Fault:" << dem;
}

void FIFO(int* sequence, int leng, int pageframes)
{
    int fault;
    int** table = new int* [pageframes];
    int* arrivaltime = new int[pageframes];
    int* faultarr = new int[leng];
    for (int i = 0;i < leng;i++) faultarr[i] = 0;
    for (int i = 0;i < pageframes;i++)
    {
        table[i] = new int[leng];
        for (int j = 0;j < leng;j++)
        {
            table[i][j] = -1;
        }
    }

    for (int len = 0;len < leng;len++)
    {
        if (len > 0)
        {
            for (int row = 0;row < pageframes;row++)
            {
                table[row][len] = table[row][len - 1];
            }
        }
        bool existdata = false;
        for (int row = 0;row < pageframes;row++)
        {
            if (sequence[len] == table[row][len])
            {
                existdata = true;
            }
        }
        if (existdata == false)
        {
            faultarr[len] = 1;
            bool declared = false;
            int mintime = 0;
            for (int row = 0;row < pageframes;row++)
            {
                if (declared == false)
                {
                    if (table[row][len] == -1)
                    {
                        table[row][len] = sequence[len];
                        arrivaltime[row] = len;
                        declared = true;
                    }
                }
                if (arrivaltime[row] < arrivaltime[mintime])
                {
                    mintime = row;
                }
            }
            if (declared == false)
            {
                table[mintime][len] = sequence[len];
                arrivaltime[mintime] = len;
            }
        }
    }
    int** resulttable = new int* [pageframes + 1];
    for (int i = 0;i < pageframes + 1;i++) resulttable[i] = new int[leng];
    for (int i = 0;i < leng;i++) resulttable[0][i] = sequence[i];
    for (int i = 1;i < pageframes + 1;i++)
    {
        for (int j = 0;j < leng;j++)
        {
            resulttable[i][j] = table[i - 1][j];
        }
    }
    PRINTTABLE(resulttable, pageframes + 1, leng, faultarr);
    cout << endl;
}

void LRU(int* sequence, int leng, int pageframes)
{
    int fault;
    int** table = new int* [pageframes];
    int* arrivaltime = new int[pageframes];
    int* faultarr = new int[leng];
    for (int i = 0;i < leng;i++) faultarr[i] = 0;
    for (int i = 0;i < pageframes;i++)
    {
        table[i] = new int[leng];
        for (int j = 0;j < leng;j++)
        {
            table[i][j] = -1;
        }
    }

    for (int len = 0;len < leng;len++)
    {
        if (len > 0)
        {
            for (int row = 0;row < pageframes;row++)
            {
                table[row][len] = table[row][len - 1];
            }
        }
        bool existdata = false;
        for (int row = 0;row < pageframes;row++)
        {
            if (sequence[len] == table[row][len])
            {
                existdata = true;
                arrivaltime[row] = len;
            }
        }
        if (existdata == false)
        {
            faultarr[len] = 1;
            bool declared = false;
            int mintime = 0;
            for (int row = 0;row < pageframes;row++)
            {
                if (declared == false)
                {
                    if (table[row][len] == -1)
                    {
                        table[row][len] = sequence[len];
                        arrivaltime[row] = len;
                        declared = true;
                    }
                }
                if (arrivaltime[row] < arrivaltime[mintime])
                {
                    mintime = row;
                }
            }
            if (declared == false)
            {
                table[mintime][len] = sequence[len];
                arrivaltime[mintime] = len;
            }
        }
    }
    int** resulttable = new int* [pageframes + 1];
    for (int i = 0;i < pageframes + 1;i++) resulttable[i] = new int[leng];
    for (int i = 0;i < leng;i++) resulttable[0][i] = sequence[i];
    for (int i = 1;i < pageframes + 1;i++)
    {
        for (int j = 0;j < leng;j++)
        {
            resulttable[i][j] = table[i - 1][j];
        }
    }
    PRINTTABLE(resulttable, pageframes + 1, leng, faultarr);
    cout << endl;
}

void OPT(int* sequence, int leng, int pageframes)
{
    int fault;
    int** table = new int* [pageframes];
    int* arrivaltime = new int[pageframes];
    int* faultarr = new int[leng];
    for (int i = 0;i < leng;i++) faultarr[i] = 0;
    for (int i = 0;i < pageframes;i++)
    {
        table[i] = new int[leng];
        for (int j = 0;j < leng;j++)
        {
            table[i][j] = -1;
        }
    }

    for (int len = 0;len < leng;len++)
    {
        if (len > 0)
        {
            for (int row = 0;row < pageframes;row++)
            {
                table[row][len] = table[row][len - 1];
            }
        }
        bool existdata = false;
        for (int row = 0;row < pageframes;row++)
        {
            if (sequence[len] == table[row][len])
            {
                existdata = true;
                arrivaltime[row] = len;
            }
        }
        if (existdata == false)
        {
            faultarr[len] = 1;
            bool declared = false;
            int maxtime = 0;
            int maxtimeplace = 0;
            for (int row = 0;row < pageframes;row++)
            {
                if (declared == false)
                {
                    if (table[row][len] == -1)
                    {
                        table[row][len] = sequence[len];
                        arrivaltime[row] = len;
                        declared = true;
                    }
                }
                if (declared == false)
                {
                    for (int start = len + 1;start < leng;start++)
                    {
                        if (sequence[start] == table[row][len])
                        {
                            if (maxtime < start - len)
                            {
                                maxtime = start - len;
                                maxtimeplace = row;

                            }
                            break;
                        }
                        if (start == leng - 1)
                        {
                            if (maxtime == start - len + 1)
                            {
                                if (arrivaltime[maxtimeplace] > arrivaltime[row])
                                {
                                    maxtime = start - len + 1;
                                    maxtimeplace = row;
                                }

                            }
                            if (maxtime < start - len + 1)
                            {
                                maxtime = start - len + 1;
                                maxtimeplace = row;
                            }

                        }
                    }
                }
            }
            if (declared == false)
            {
                table[maxtimeplace][len] = sequence[len];
                arrivaltime[maxtimeplace] = len;
            }
        }
    }
    int** resulttable = new int* [pageframes + 1];
    for (int i = 0;i < pageframes + 1;i++) resulttable[i] = new int[leng];
    for (int i = 0;i < leng;i++) resulttable[0][i] = sequence[i];
    for (int i = 1;i < pageframes + 1;i++)
    {
        for (int j = 0;j < leng;j++)
        {
            resulttable[i][j] = table[i - 1][j];
        }
    }
    PRINTTABLE(resulttable, pageframes + 1, leng, faultarr);
    cout << endl;
}

int main()
{
    int choice, leng, pageframes;
    
    START_MENU();
    cin >> choice;
    int* sequence;
    if (choice == 1)
    {
        int a[] = { 1,9,5,2,1,9,2,5,0,0,7 };
        sequence = a;
        leng = 11;
    }
    if (choice == 2)
    {
        MANUALINPUT();
        cin >> leng;
        sequence = new int[leng];
        for (int i = 0;i < leng;i++) cin >> sequence[i];
    }
    FRAMEINPUT();
    cin >> pageframes;
    ALGORITHM_MENU();
    do { cin >> choice; }     
    while (choice < 1 || choice>3);
    if (choice == 1) FIFO(sequence, leng, pageframes);
    if (choice == 2) OPT(sequence, leng, pageframes);
    if (choice == 3) LRU(sequence, leng, pageframes);
}

/*

5 253 956 2616 1991962 61 2 5415 313 6

LRU 7 0 1 2 0 3 0 4 2 3 0 3 2 1 2 0 1 7 0 1

*/


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
