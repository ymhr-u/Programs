#include <iostream>
#include <string>

using namespace std;
int main() {
  string s;
  cin >> s;

  for (int i = 0; i < s.length(); i++) {
    if (s[i] >= 'A' && s[i] <'N') {
      s[i] += 13;
    } else if (s[i] >= 'N' && s[i] < 'a') {
      s[i] -= 13;
    } else if (s[i] >= 'a' && s[i] < 'n') {
      s[i] += 13;
    } else if (s[i] >= 'n' && s[i] <= 'z') {
      s[i] -= 13;
    }
  }

  cout << s << endl;

  return 0;
}
