#include <iostream>
#include <cmath>
#include <queue>
#include <algorithm>
#include <iterator>

using std::sort;
using std::deque;
using std::string;
using std::cout;



float euclidean(char [3][3], char[3][3]);
int findPlace(char [3][3], char, float &);
float findGPlace(char [3][3], char, float &);
void add(int **);
/*
    4 5 7      (0 + 1)2 +      
    3 1 2
    8 6 x
*/

struct Process{
    int pid;
    int burst;
    int arrival;


};

bool operator<(const Process& a, const Process& b) {
          return a.arrival < b.arrival;
    }

int main() {
    char x[3][3];
    char right[3][3] = {{'x','1','2'},{'3','4','5'},{'6','7','8'}};
    string temp ="7245x6831";
    float sum = 0;

    deque<Process> d;

    Process pro;
    Process pro1;
    Process pro2;
    Process pro3;
    Process pro4;
    pro.arrival = 5;
    pro2.arrival = 1;
    pro3.arrival = 9;
    pro3.arrival = -3;
    pro4.arrival = 10;

    d.push_back(pro);
    d.push_back(pro1);
    d.push_back(pro2);
    d.push_back(pro3);
    d.push_back(pro4);


    sort(d.begin(),d.end());

    for (int i = 0; i < 5; i++) {
        Process temp = d.front();
        cout << d.front().arrival << " ";
        d.pop_front();
    }
    

    int *h;
    //add(&h);

    //cout << *h;
    //delete h;


    //sum += sqrt((0-2)*(0-2) + (0-1)*(0-1));
    //cout << sum;

    /*for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            temp += x[i][j]; 
        }
    }*/

    //cout << temp;

    //float ans = euclidean(x,right);

    //cout << "Euclidean distance is " << ans;

    return 0;
}

void add(int **h) {
    *h = new int;
    **h = 7;
}


float euclidean(char arr[3][3], char r[3][3]) {
    float x1 = 0, x2 = 0, y1 = 0, y2 = 0;
    float sum = 0;
    char num = '0';

    for (int i = 0; i < 3; i++) {       // Hardcoded size to 3 here. Change later
        for (int j = 0; j < 3; j++) {
            if (arr[i][j] != num and arr[i][j] != 'x') {
                cout << "iCOOR: " << i << " jCOOR" << " " << j << "\n";
                x1 = findGPlace(r,arr[i][j],y1);     // x1,y1 = goal position for number
                x2 = findPlace(arr,arr[i][j],y2);     // x2,y2 = actual position on board
                sum += sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));
                //cout << ((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1)) << "  ";
            }
            cout << "\n";
            num++;
        }
    }
    return sum;
}

int findPlace(char arr[3][3], char target, float &idx) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (arr[i][j] == target) {
                idx = j;    //return y2
                return i;   //return x2
            }
        }
    }

    return 0;
}

float findGPlace(char arr[3][3], char target, float &idx) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (arr[i][j] == target) {
                idx = j;    //return y2
                return i;   //return x2
            }
        }
    }

    return 0;
}

