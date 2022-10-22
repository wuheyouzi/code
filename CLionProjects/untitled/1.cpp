#include <iostream>
#include <vector>
using namespace std;

pair <string, string> cut(string s) {
    int t = s.find(":");
    return make_pair(s.substr(0, t), s.substr(t + 1));
}

int main() {
    int n;
    cin >> n;
    vector < pair<int, string> > v;
    for (int i = 1; i <= n; i++) {
        int id;
        string obj;
        cin >> id >> obj;
        v.emplace_back(id, obj);
    }
    int qNum;
    cin >> qNum;
    for (int i = 1; i <= qNum; i++){
        int objNum;
        cin >> objNum;
        bool found = false;
        vector < pair<int, string> > :: iterator it;
        for (it = v.begin(); it != v.end(); it++){
            if (it->first == objNum){
                found = true;
                pair <string, string> t = cut(it->second);
                cout << t.first << " " << t.second << endl;
                break;
            }
        }
        if (!found) {
            cout << "Object not found." << endl;
        }
    }
    return 0;
}
