// C_Program_for_Round_Robin_RR.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <stdio.h>
#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;
vector <int> queue;
typedef struct Process									//Tạo kiểu process
{
    int arr, bur, star = -1, finish, tat, wt, rp;
    string Pronum;
};

void SelectionSortarrival(Process* pn, int n)						//Xếp theo thời gian xuất hiện
{
    for (int i = 0;i < n;i++)
    {
        int min = i;
        for (int j = i;j < n;j++)
        {
            if (pn[j].arr < pn[min].arr)
            {
                min = j;
            }
        }
        Process temp = pn[i];
        pn[i] = pn[min];
        pn[min] = temp;
    }
}
int* originalburst = new int[10];							//Lưu trữ time burst ban đầu
void PrintAllDetail(Process* pn, int n)							//In tất cả thông tin hiện tại
{
    cout << "Pname            ArrivalTime  BurstTime  Start  TAT  Finish" << endl;
    for (int i = 0;i < n;i++)
    {
        cout << pn[i].Pronum
            << setw(28 - pn[i].Pronum.size()) << pn[i].arr
            << setw(11) << pn[i].bur
            << setw(7) << pn[i].star
            << setw(5) << pn[i].tat
            << setw(8) << pn[i].finish
            << "                           Wait time:" << pn[i].wt << endl << endl;
    }
}
void PrintAllDetail2(Process* pn, int n)						//In tất cả thông tin
{
    cout << "Pname            ArrivalTime     BurstTime     Start     Finish     Rptime     Waittime     TAT" << endl;
    for (int i = 0;i < n;i++)
    {
        cout << pn[i].Pronum
            << setw(28 - pn[i].Pronum.size()) << pn[i].arr
            << setw(14) << originalburst[i]
            << setw(10) << pn[i].star
            << setw(10) << pn[i].finish
            << setw(12) << pn[i].rp
            << setw(13) << pn[i].wt
            << setw(8) << pn[i].tat << endl << endl;
    }
}
void PrintAllQueue(Process* pn, int n)
{
    cout << "queue size : " << queue.size() << endl;
    for (int i = 0;i < queue.size();i++)
    {
        cout << "Print queue : " << pn[queue[i]].Pronum << pn[queue[i]].arr << pn[queue[i]].bur << endl;
    }
}

void SelectionSortBurst(Process* pn)							//Xếp hàng đợi theo burst time
{
    //int a;
    //cout << "queue size : "<<queue.size()<< endl;
    //cin >> a;
    for (int i = 0;i < queue.size();i++)
    {
        int min = i;
        for (int j = i; j < queue.size(); j++)
        {
            if (pn[queue[min]].bur > pn[queue[j]].bur) min = j;
        }
        int temp = queue[i];
        queue[i] = queue[min];
        queue[min] = temp;
    }
}

int logarit(int n) {
    int dem = 0;
    while (n >= 10) {
        n /= 10; // hay n = n /10;
        dem++;
    }
    return dem;
}
void PrintGantt(int robincount,int exect,Process *pn,int time)
{
    //cout <<setw(5)<< time - robincount << setw(2*pn[exect].Pronum.size()-3) << pn[exect].Pronum << setw(pn[exect].Pronum.size()+logarit(time)-2) << time << endl;
    cout << setw(5) << time - robincount << setw(2 * pn[exect].Pronum.size() - 3) << pn[exect].Pronum;
}
int main()
{
    int n,roundrobin;
    printf("Enter the number of processes:");
    cin >> n;
    cout << "Enter the number of RoundRobin:";
    cin >> roundrobin;
    Process* pn = new Process[10];
    for (int i = 0;i < n;i++)
    {
        cout << "Enter the Process Name,Arrival Time & Burst Time:";
        cin >> pn[i].Pronum >> pn[i].arr >> pn[i].bur;
        pn[i].star = -1;
    }
    SelectionSortarrival(pn, n);
    int  executing = 0, queueAdded = 0, arrcount = 1, Runningflag = 0,robincount=0,allt=0;
    for (int i = 0;i < n;i++) originalburst[i] = pn[i].bur;
    double avgwaittime = 0, avgturnaround = 0;
    cout << endl << "Gantt chart" << endl;
    //cout << "Start" << setw(13) << "Name" << setw(9) << "Stop"<<endl;
    for (int time = 0;queue.size() != 0 || Runningflag != 0 || queueAdded < n;time++)
    {
        allt = time;
        if (Runningflag == 1) robincount++;
        while (time == pn[queueAdded].arr)
        {
            int temp = queueAdded;
            queue.push_back(temp);
            queueAdded++;

        }
        if (Runningflag == 0)
        {
            if (queue.size() != 0)
            {
                executing = queue[0];
                queue.erase(queue.begin());
                if (pn[executing].star == -1)
                {
                    pn[executing].star = time;
                    pn[executing].rp = time - pn[executing].arr;
                }
                Runningflag = 1;
            }
        }
        if (Runningflag == 1)
        {

            if (pn[executing].bur == 0)
            {
                PrintGantt(robincount, executing, pn, time);
                pn[executing].finish = time;
                pn[executing].tat = pn[executing].finish - pn[executing].arr;
                pn[executing].wt = pn[executing].tat - originalburst[executing];
                avgturnaround += pn[executing].tat;
                avgwaittime += pn[executing].wt;
                robincount = 0;
                if (queue.size() != 0)
                {
                    executing = queue[0];
                    queue.erase(queue.begin());
                    if (pn[executing].star == -1)
                    {
                        pn[executing].star = time;
                        pn[executing].rp = time - pn[executing].arr;
                    }
                    pn[executing].bur--;
                }
                else
                {
                    Runningflag = 0;
                }
            }
            else if(robincount==roundrobin&&queue.size()!=0)
            {
                PrintGantt(robincount, executing, pn, time);
                int temp = executing;
                executing = queue[0];
                queue.erase(queue.begin()); 
                if (pn[executing].star == -1)
                {
                    pn[executing].star = time;
                    pn[executing].rp = time - pn[executing].arr;
                }
                queue.push_back(temp);
                pn[executing].bur--;
                robincount = 0;
            }
            else  pn[executing].bur--;
        }
    }
    cout <<setw(6)<< allt<<endl<<endl;
    PrintAllDetail2(pn, n);
    avgturnaround /= n;
    avgwaittime /= n;
    cout << "AVG Wait:" << avgwaittime << endl << "AVG TAT :" << avgturnaround;
}

/*
case 1
3
2
Procces1 3 5
Process2 2 6
Process3 6 3

case 2
4
3
Procces1 9 5
Process2 2 6
Process3 13 3
Process4 12 5

case 3
3
3
Process1 0 20
Process2 2 2
Process3 7 3

case 4
9
5
Procces1 0 50
Process2 2 45
Process3 4 40
Process4 6 35
Process5 8 30
Process6 10 25
Process7 12 20
Process8 14 15
Process9 16 10

case 5
4
22
Procces1 0 5
Process2 0 6
Process3 0 3
Process4 0 5

case 6
3
7
Procces1 0 65
Process2 0 73
Process3 0 17
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
