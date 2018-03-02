#include <cstring>
#include <cstdlib>
#include <string>
#include <algorithm>
#include <iostream>

using namespace std;

static char** getMinAlignment(const char* X, const char* Y, int d, int a) {
  int m = strlen(X);
  int n = strlen(Y);
  int longer = (m > n)? m : n;
  int A[m+1][n+1];
  char** ret = new char*[3];
  for (int i = 0; i < 3; i++) {
    ret[i] = new char[longer+1];
    ret[i][longer] = '\0';
  }


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
  int k = longer-1;
  while (0 < i && 0 < j) {
    int left = A[i][j-1] + d;
    int up = A[i-1][j] + d;
    int diag = (X[i-1] == Y[j-1])? A[i-1][j-1] : A[i-1][j-1] + a;

    if (A[i][j] == left) {
      j--;
      ret[0][k] = '-';
      ret[1][k] = ' ';
      ret[2][k] = Y[j];
      k--;
    } else if (A[i][j] == up) {
      i--;
      ret[0][k] = X[i];
      ret[1][k] = ' ';
      ret[2][k] = '-';
      k--;
    } else {
      i--; j--;
      ret[0][k] = X[i];
      ret[1][k] = (X[i] == Y[j])? '|' : ' ';
      ret[2][k] = Y[j];
      k--;
    }
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
  string tmp;

  getline(cin, tmp);
  char X[tmp.length()];
  strcpy(X, tmp.c_str());

  getline(cin, tmp);
  char Y[tmp.length()];
  strcpy(Y, tmp.c_str());

  getline(cin, tmp);
  int d = atoi(tmp.c_str());

  getline(cin, tmp);
  int a = atoi(tmp.c_str());

  char** alignment = getMinAlignment(X, Y, d, a);
  // print
  for (int i = 0; i < 3; i++) {
    cout << alignment[i] << endl;
  }

  return 0;
}
