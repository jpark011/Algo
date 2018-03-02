#include <string>
#include <algorithm>
#include <iostream>

using namespace std;

static string* getMinAlignment(const string& X, const string& Y, int d, int a) {
  int m = X.length();
  int n = Y.length();
  int longer = (m > n)? m : n;
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
  while (0 < i && 0 < j) {
    int left = A[i][j-1] + d;
    int up = A[i-1][j] + d;
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

    ret[0].append(1, r0);
    ret[1].append(1, r1);
    ret[2].append(1, r2);
  }


  reverse(ret[0].begin(), ret[0].end());
  reverse(ret[1].begin(), ret[1].end());
  reverse(ret[2].begin(), ret[2].end());
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
  getline(cin, X);

  string Y;
  getline(cin, Y);

  string in;
  getline(cin, in);
  int d = stoi(in);

  getline(cin, in);
  int a = stoi(in);

  string* alignment = getMinAlignment(X, Y, d, a);
  // print
  for (int i = 0; i < 3; i++) {
    cout << alignment[i] << endl;
  }

  return 0;
}
