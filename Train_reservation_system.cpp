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

        map<pair<string,int>,Seat> st;
        
        while(1) {
            string sr,dt,dte,coa;
            int set;
            cin >> sr;
            if(sr == "") break;
            cin >> dt >> dte >> coa >> set;
            int trIdx = isTrainAvailable(sr,dt,t,noOfTrains);
            bool b1 = false;
            pair<string,int> p;
            if(trIdx == -1) {
                cout << "No Trains Available.\n";
                b1 = true;
            }
            else {
                p = {dte,trIdx};
            }
            Seat stss;
            if(trIdx != -1 && st.find(p) == st.end()) {
                stss.sl = t[trIdx].coaches["SL"];
                stss.towA = t[trIdx].coaches["2A"];
                stss.threeA = t[trIdx].coaches["3A"];
                stss.firstA = t[trIdx].coaches["1A"];
            }
            else if(trIdx != -1){
                stss = st[p];
            }
            int cost = 0;
            if(trIdx != -1) {
                if(coa == "SL") {
                    if(stss.sl < set) {
                        cout << "No Seats Available.\n";
                        b1 = true;
                    }
                    else {
                        stss.sl -= set;
                        cost += (set*1*t[trIdx].distance);
                    }
                }
                else if(coa == "2A") {
                    if(set > stss.towA) {
                        cout << "No Seats Available.\n";
                        b1 = true;
                    }
                    else{
                        stss.towA -= set;
                        cost += (set*3*t[trIdx].distance);
                    }
                }
                else if(coa == "3A") {
                    if(set > stss.threeA) {
                        cout << "No Seats Available.\n";
                        b1 = true;
                    }
                    else{
                        stss.threeA -= set;
                        cost += (set*2*t[trIdx].distance);
                    }
                }
                else {
                    if(set > stss.firstA) {
                        cout << "No Seats Available.\n";
                        continue;
                    }
                    else{
                        stss.firstA -= set;
                        cost += (set*4*t[trIdx].distance);
                    }
                }
                st[p] = stss;
            }
            if(!b1) {cout << log << " " << cost << "\n"; log++;}
            
        }

        // BOOK TICKET

        return 0;
    }
