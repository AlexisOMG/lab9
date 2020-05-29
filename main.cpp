#include "declaration.h"
#include <ctime>

int main() {
    srand(time(0));
    cout << "TEEST 1:\n";
    map <string, bool> dict;
    for (int i = 0; i < 10; ++i) {
        char c = char('a' + i);
        string key = "";
        key += c;
        dict[key] = true;
        cout << key << " " << (dict[key] ? "true\n" : "false\n");
    }
    vector < Bool<string> > arr(10);
    int t = 0;
    for (auto i : dict) {
        arr[t++] = Bool<string>(i.first);
    }
    for (int i = 1; i < t; ++i) {
        arr[0] = arr[0] + arr[i];
    }
    cout << "formula1: " << arr[0] << " = " << (arr[0](dict) ? "true\n" : "false\n");
    arr[0] = !arr[0];
    cout << "!formula1: " << arr[0] << " = " << (arr[0](dict) ? "true\n" : "false\n");

    cout << "\nTEST 2:\n";
    dict["j"] = false;
    t = 0;
    for (auto i : dict) {
        cout << i.first << " " << (i.second ? "true\n" : "false\n");
        arr[t++] = Bool<string>(i.first);
    }
    for (int i = 1; i < t - 1; ++i) {
        arr[0] = arr[0] + arr[i];
    }
    arr[0] = arr[0] * arr[t - 1];
    cout << "formula: " << arr[0] << " = " << (arr[0](dict) ? "true\n" : "false\n");

    cout << "\nTEST 3:\n";
    map <int, bool> dict1;
    for (int i = 10; i < 20; ++i) {
        dict1[i] = !(rand()%2);
    }
    vector < Bool<int> > arr1(10);
    t = 0;
    for (auto i : dict1) {
        cout << i.first << " " << (i.second ? "true\n" : "false\n");
        arr1[t++] = Bool<int>(i.first);
    }
    for (int i = 1; i < 6; ++i) {
        arr1[0] = arr1[0] + arr1[i];
    }
    arr1[0] = arr1[0] * arr1[6];
    for (int i = 7; i < 10; ++i) {
        arr1[0] = arr1[0] + arr1[i];
    }
    cout << "formula: " << arr1[0] << " = " << (arr1[0](dict1) ? "true\n" : "false\n");
    return 0;
}
