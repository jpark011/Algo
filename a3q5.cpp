#include <string>
#include <algorithm>
#include <iostream>

using namespace std;

static string* getMinAlignment(const string& X, const string& Y, int d, int a) {
  int m = X.length();
  int n = Y.length();
  int A[m+1][n+1];
  string* ret = new string[3];

  // init array
  for (int i = 0; i <= m; i++) {
    A[i][0] = i*d;
  }
  for (int j = 0; j <= n; j++) {
    A[0][j] = j*d;
  }

  // dynamic programming
  // get min cost
  for (int i = 1; i <= m; i++) {
    for (int j = 1; j <= n; j++) {
      int left = A[i][j-1] + d;
      int up = A[i-1][j] + d;
      int diag = (X[i-1] == Y[j-1])? A[i-1][j-1] : A[i-1][j-1] + a;

      A[i][j] = min(diag, min(left, up));
    }
  }

  // cout << "X: " << X << endl;
  // cout << "Y: " << Y << endl;
  // cout << "d: " << d << endl;
  // cout << "a: " << a << endl;
  // cout << "min cost: " << A[m][n] << endl;
  // for (int i = 0; i <= m; i++) {
  //   for (int j = 0; j <= n; j++) {
  //     cout << A[i][j] << " ";
  //   }
  //   cout << endl;
  // }

  // reconstruct
  int i = m;
  int j = n;
  while (0 < i || 0 < j) {
    int left = (0 < j)? A[i][j-1] + d : -1;
    int up = (0 < i)? A[i-1][j] + d : -1;
    int diag = (X[i-1] == Y[j-1])? A[i-1][j-1] : A[i-1][j-1] + a;

    char r0, r1, r2;
    if (A[i][j] == left) {
      j--;
      r0 = '-';
      r1 = ' ';
      r2 = Y[j];
    } else if (A[i][j] == up) {
      i--;
      r0 = X[i];
      r1 = ' ';
      r2 = '-';
    } else {
      i--; j--;
      r0 = X[i];
      r1 = (X[i] == Y[j])? '|' : ' ';
      r2 = Y[j];
    }

    // cout << i << endl;
    // cout << j << endl;
    // cout << r0 << endl;
    // cout << r1 << endl;
    // cout << r2 << endl << endl;

    // prepend to the beginning
    ret[0].insert(ret[0].begin(), r0);
    ret[1].insert(ret[1].begin(), r1);
    ret[2].insert(ret[2].begin(), r2);
  }

  return ret;
}

int main(int argc, char const *argv[]) {
  /* code */
  // if (argc != 5) {
  //   cerr << "Wrong # params!!" << endl;
  //   cerr << "Usage: ./DNA <X> <Y> <d> <a>" << endl;
  //   return 1;
  // }

  // get inputs from std
  string X;
  string Y;
  int d;
  int a;

  cin >> X;
  cin >> Y;
  cin >> d;
  cin >> a;

  string* alignment = getMinAlignment(X, Y, d, a);
  // string* alignment = getMinAlignment("ACTTTTACGGGGGATCCCACACA", "CTTACTGGGGCCTTCACA", 1, 1);
  // print
  for (int i = 0; i < 3; i++) {
    cout << alignment[i] << endl;
  }

  return 0;
}
