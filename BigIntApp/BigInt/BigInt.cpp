// BigInt.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"

#include <string>
#include <vector>
#include <cctype>
#include <cassert>
#include "BigInt.h"

using namespace std;

static vector<int> vadd(const vector<int> &a, const vector<int> &b)
{
    assert(a.size() && b.size());
    vector<int> r;
    int len = max(a.size(), b.size());
    r.reserve(len);
    int cur, last = 0;
    for (int i = 0; i < len; i++) {
        int curA = i < int(a.size()) ? a[i] : 0;
        int curB = i < int(b.size()) ? b[i] : 0;
        cur = curA + curB + last;
        r.push_back(cur % 10);
        last = cur / 10;
    }
    if (last > 0) r.push_back(last);
    return r;
}

static vector<int> vsub(const vector<int> &a, const vector<int> &b)
{
    assert(a.size() && b.size());
    assert(a.size() >= b.size());
    vector<int> r;
    int len = a.size();
    r.reserve(len);
    int cur, last = 0;
    for (int i = 0; i < len; i++) {
        cur = a[i] - (i < int(b.size()) ? b[i] : 0) - last;
        r.push_back((cur + 10) % 10);
        last = cur < 0;
    }
    assert(last == 0);
    while (r.size() > 1 && r.back() == 0) r.pop_back();
    return r;
}

static vector<int> vmul(const vector<int> &a, const vector<int> &b)
{
    assert(a.size() && b.size());
    int len = a.size() + b.size();
    vector<int> r (len, 0);
    for (int i = 0; i < int(a.size()); i++)
        for (int j = 0; j < int(b.size()); j++)
            r[i + j] += a[i] * b[j];
    int cur, last = 0;
    for (int i = 0; i < len; i++) {
        cur = r[i] + last;
        r[i] = cur % 10;
        last = cur / 10;
    }
    while (r.size() > 1 && r.back() == 0) r.pop_back();
    return r;
}

static vector<int> vdiv(const vector<int> &a, const vector<int> &b)
{
    assert(a.size() && b.size());
    assert(b.size() > 1 || b[0] != 0);
    if (a.size() < b.size())
        return vector<int> (1, 0);
    int len = a.size() - b.size() + 1;
    vector<int> t (a);
    vector<int> r (len, 0);
    for (int i = len - 1; i >= 0; i--)
        while (1) {
            bool less_flag = false;
            for (int j = t.size() - 1; j >= i; j--) {
                int curA = t[j];
                int curB = j - i < int(b.size()) ? b[j - i] : 0;
                if (curA != curB) {
                    less_flag = curA < curB;
                    break;
                }
            }
            if (less_flag) break;
            r[i]++;
            int cur, last = 0;
            for (int j = i; j < int(t.size()); j++) {
                cur = t[j] - (j - i < int(b.size()) ? b[j - i] : 0) - last;
                t[j] = (cur + 10) % 10;
                last = cur < 0;
            }
            while (t.size() > i + b.size() && t.back() == 0) t.pop_back();
        }
    while (r.size() > 1 && r.back() == 0) r.pop_back();
    return r;
}

static int icmp(int a, int b)
{
    return (a > b) - (a < b);
}

static int vcmp(const vector<int> &a, const vector<int> &b)
{
    assert(a.size() && b.size());
    if (a.size() != b.size())
        return icmp(a.size(), b.size());
    for (int i = a.size() - 1; i >= 0; i--)
        if (a[i] != b[i])
            return icmp(a[i], b[i]);
    return 0;
}

static vector<int> stov(const string &a)
{
    assert(isnum(a));
    vector<int> r;
    r.reserve(a.length());
    for (int i = a.length() - 1; i >= 0; i--)
        r.push_back(a[i] - '0');
    return r;
}

static string vtos(const vector<int> &a)
{
    assert(a.size());
    string r;
    r.reserve(a.size());
    for (int i = a.size() - 1; i >= 0; i--)
        r += a[i] + '0';
    return r;
}





bool isnum(const string &s)
{
    if (s.length() == 0)
        return false;
    if (s.length() > 1 && s[0] == '0')
        return false;
    for (int i = 0; i < int(s.length()); i++)
        if (!isdigit(s[i]))
            return false;
    return true;
}

string add(const string &a, const string &b)
{
    return vtos(vadd(stov(a), stov(b)));
}

string sub(const string &a, const string &b)
{
    return vtos(vsub(stov(a), stov(b)));
}

string mul(const string &a, const string &b)
{
    return vtos(vmul(stov(a), stov(b)));
}

string div(const string &a, const string &b)
{
    return vtos(vdiv(stov(a), stov(b)));
}

int cmp(const string &a, const string &b)
{
    return vcmp(stov(a), stov(b));
}

