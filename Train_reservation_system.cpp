#include<bits/stdc++.h>
using namespace std;

// Train Class
class Train {
    public:
    string trainNo;
    string source;
    string destination;
    int distance;
    int date;
    unordered_map<string,int> coaches;
};

class Seat {
    public:
    int sl;
    int towA;
    int threeA;
    int firstA;
}

bool isTrainAvailable(string source,string destination,Train t[],int n) {
    for(int i=0;i<n;i++) {
        if(source == t[i].source && destination == t[i].destination) return i;
    }
    return -1;
}

int main() {


    // TRAIN INPUT
    int noOfTrains;
    cin >> noOfTrains;

    Train t[noOfTrains];
    int i=0;
    while(i < noOfTrains) {
        string tno,sou,dest;
        cin >> tno >> sou >> dest;

        int idx1 = sou.length();
        int idx2 = dest.length();

        while(sou[idx1] != '-') idx1--;
        while(dest[idx2] != '-') idx2--;
        int dist = stoi(dest.substr(idx2+1,dest.length()+idx2+2));
        sou = sou.substr(0,idx1);
        dest = dest.substr(0,idx2);

        t[i].trainNo = tno;
        t[i].source = sou;
        t[i].destination = dest;
        t[i].distance = dist;

        cout << t[i].trainNo << " " << t[i].source << " " << t[i].destination << " " << t[i].distance << "\n";

        while(1) {
            string str;
            cin >> str;
            if(str == "") break;
            if(str[0] >= '0' && str[0] <= '9') continue;
            int len = str.length();
            int site = stoi(str.substr(3,len));
            str = str.substr(0,2);
            if(str[0] == 'S') str = "SL";
            else if(str[0] == 'B') str = "3A";
            else if(str[0] == 'A') str = "2A";
            else str = "1A";
            t[i].coaches[str] += site;
        }
        i++;
    }
    // TRAIN INPUT

    // BOOK TICKET 

    Seat st[32][noOfTrains];

    for(int i=1;i<32;i++) {
        for(int j=0;j<noOfTrains;j++) {
            st[i][j].sl = t[j].coaches["SL"];
            st[i][j].threeA = t[j].coaches["3A"];
            st[i][j].towA = t[j].coaches["2A"];
            st[i][j].firstA = t[j].coaches["1A"];
        }
    }

    while(1) {
        
        stirng sr,dt,date,coa,set;
        cin >> sr >> dt >> dt >> coa >> set;

        int trIdx = isTrainAvailable(sr,dt,t,noOfTrains);
        if(trIdx == -1) {
            cout << "No Trains Available\n";
            continue;
        }

        int date = stoi(dt.substr(8,2));
        if()


        
    }

    // BOOK TICKET

    return 0;
}