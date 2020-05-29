#ifndef DECLARATION_H
#define DECLARATION_H

#include <iostream>
#include <vector>
#include <map>
using namespace std;

template <typename T>
class Bool {
public:
    vector <T> vars;
    vector <bool> inv;
    vector <string> comm;
    int n;
    Bool(T var);
    Bool(){}
    Bool<T> operator+ (const Bool &obj);
    Bool<T> operator* (const Bool &obj);
    Bool<T> operator! ();
    Bool<T>& operator=(const Bool &obj);
    bool operator() (map <T, bool> dict);
    template <typename K>
    friend ostream& operator<<(ostream &a, const Bool<K> &obj);
};

template <typename K>
ostream& operator<<(ostream &a, const Bool<K> &obj) {
    int cnt = 0;
    for (int i = 0; i < obj.comm.size(); ++i) {
        if (obj.comm[i] == "&&") {
            ++cnt;
        }
    }
    if (cnt < obj.comm.size()) {
        for (int i = 0; i < cnt; ++i) cout << "(";
    }
    for (int i = 0; i < obj.vars.size(); ++i) {
        if (obj.inv[i]) {
            a << "!";
        }
        a << obj.vars[i];
        if (i < obj.comm.size()) {
            if (cnt < obj.comm.size() && obj.comm[i] == "&&") a << ")";
            a << " " << obj.comm[i] << " ";
        }
    }
    return a;
}

template <typename T>
Bool<T>::Bool(T var) {
    vars.push_back(var);
    inv.push_back(false);
    n = 1;
}

template <typename T>
Bool<T> Bool<T>::operator+(const Bool &obj) {
    Bool <T> res;
    res.vars.insert(res.vars.end(), this->vars.begin(), this->vars.end());
    res.vars.insert(res.vars.end(), obj.vars.begin(), obj.vars.end());
    res.n = this->vars.size() + obj.vars.size();
    if (this->comm.size() != this->vars.size() - 1 || obj.comm.size() != obj.vars.size() - 1) {
        throw -1;
    }
    res.comm.insert(res.comm.end(), this->comm.begin(), this->comm.end());
    res.comm.push_back("||");
    res.comm.insert(res.comm.end(), obj.comm.begin(), obj.comm.end());
    res.inv.insert(res.inv.end(), this->inv.begin(), this->inv.end());
    res.inv.insert(res.inv.end(), obj.inv.begin(), obj.inv.end());
    return res;
}

template <typename T>
Bool<T> Bool<T>::operator*(const Bool &obj) {
    Bool <T> res;
    res.vars.insert(res.vars.end(), this->vars.begin(), this->vars.end());
    res.vars.insert(res.vars.end(), obj.vars.begin(), obj.vars.end());
    res.n = this->vars.size() + obj.vars.size();
    if (this->comm.size() != this->vars.size() - 1 || obj.comm.size() != obj.vars.size() - 1) {
        throw -1;
    }
    res.comm.insert(res.comm.end(), this->comm.begin(), this->comm.end());
    res.comm.push_back("&&");
    res.comm.insert(res.comm.end(), obj.comm.begin(), obj.comm.end());
    res.inv.insert(res.inv.end(), this->inv.begin(), this->inv.end());
    res.inv.insert(res.inv.end(), obj.inv.begin(), obj.inv.end());
    return res;
}

template <typename T>
Bool<T> Bool<T>::operator!() {
    Bool <T> res;
    res.vars.insert(res.vars.end(), this->vars.begin(), this->vars.end());
    res.n = this->n;
    res.inv = vector <bool> (res.n, false);
    res.comm.resize(res.n - 1, "");
    for (size_t i = 0; i < this->inv.size(); ++i) {
        res.inv[i] = !this->inv[i];
    }
    for (size_t i = 0; i < this->comm.size(); ++i) {
        res.comm[i] = (this->comm[i] == "&&" ? "||" : "&&");
    }
    return res;
}

template <typename T>
bool Bool<T>::operator()(map <T, bool> dict) {
    if (this->comm.size() != this->vars.size() - 1 || this->inv.size() != this->vars.size()) {
        throw -1;
    }
    if (dict.find(this->vars[0]) == dict.end()) {
        throw 1;
    }
    bool ans = inv[0] && dict[this->vars[0]];
    for (size_t i = 1; i < this->vars.size(); ++i) {
        if (dict.find(this->vars[i]) == dict.end()) {
            throw 1;
        }
        ans = (this->comm[i - 1] == "||" ? (ans || (dict[this->vars[i]] ^ this->inv[i])) : (ans && (dict[this->vars[i]] ^ this->inv[i])));
    }
    return ans;
}

template <typename T>
Bool<T>& Bool<T>::operator=(const Bool &obj) {
    if (this == &obj) return *this;
    this->vars.resize(0);
    this->inv.resize(0);
    this->comm.resize(0);
    this->n = obj.n;
    this->vars.insert(this->vars.end(), obj.vars.begin(), obj.vars.end());
    this->inv.insert(this->inv.end(), obj.inv.begin(), obj.inv.end());
    this->comm.insert(this->comm.end(), obj.comm.begin(), obj.comm.end());
    return *this;
}

#endif
