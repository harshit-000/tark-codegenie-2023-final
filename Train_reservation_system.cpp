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
};

int isTrainAvailable(string source,string destination,Train t[],int n) {
    for(int i=0;i<n;i++) {
        if(source == t[i].source && destination == t[i].destination) return i;
    }
    return -1;
}

int main() {

    long long int log = 100000001;

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

        string temp;
        getline(cin,temp);

        string word;
        getline(cin,word);
        istringstream ss(word);
        string str;

        while(ss >> str) {
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
        
        string sr,dt,dte,coa;
        int set;    
        cin >> sr;
        if(sr == "") break;
        cin >> dt >> dte >> coa >> set;
        int trIdx = isTrainAvailable(sr,dt,t,noOfTrains);
        if(trIdx == -1) {
            cout << "No Trains Available.\n";
            continue;
        }
        int cost = 0;
        int date = stoi(dte.substr(8,2));
        if(coa == "SL") {
            if(set > st[date][trIdx].sl) {
                cout << "No Seats Available.\n";
                continue;   
            }
            else{
                st[date][trIdx].sl -= set;
                cost += (set*1*t[trIdx].distance);
            }
        }
        else if(coa == "2A") {
            if(set > st[date][trIdx].towA) {
                cout << "No Seats Available.\n";
                continue;
            }
            else{
                st[date][trIdx].towA -= set;
                cost += (set*3*t[trIdx].distance);
            }
        }
        else if(coa == "3A") {
            if(set > st[date][trIdx].threeA) {
                cout << "No Seats Available.\n";
                continue;
            }
            else{
                st[date][trIdx].threeA -= set;
                cost += (set*2*t[trIdx].distance);
            }
        }
        else {
            if(set > st[date][trIdx].firstA) {
                cout << "No Seats Available.\n";
                continue;
            }
            else{
                st[date][trIdx].firstA -= set;
                cost += (set*4*t[trIdx].distance);
            }
        }

        cout << log << " " << cost << "\n";
        log++;
        
    }

    // BOOK TICKET

    return 0;
}