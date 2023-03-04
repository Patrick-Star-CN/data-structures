#include <iostream>
#include <string>
using namespace std;

int solution(int n, string s) {
    if (n <= 3) {
        return 0;
    }
    int l = 1, r = n - 2, ans = 0;
    for (; l < r; ++l, --r) {
        while (s[l] == s[0]) {
            l++;
        }
        while (s[r] == s[n - 1]) {
            r--;
        }
        if (l < r && s[l] != s[0] && s[r] != s[n - 1]) {
            ans++;
        }
    }
    return ans;
}


int main() {
    int n;
    string s;
    cin >> n >> s;
    cout << solution(n, s);
    return 0;
}