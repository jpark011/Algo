#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <iostream>

using namespace std;

static char** getMinAlignment(const char* X, const char* Y, int d, int a) {
  int m = strlen(X);
  int n = strlen(Y);
  int longer = (m > n)? m : n;
  int A[m][n];
  char** ret = new char*[3];
  for (int i = 0; i < 3; i++) {
    ret[i] = new char[longer+1];
    ret[i][longer] = '\0';
  }


  // init array
  for (int i = 0; i < m; i++) {
    A[i][0] = i*d;
  }
  for (int j = 0; j < n; j++) {
    A[0][j] = j*d;
  }

  // dynamic programming
  // get min cost
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      A[i][j] = min(
        A[i-1][j-1] + (X[i] == Y[j])? 0 : a,
        min(
          A[i-1][j] + d,
          A[i][j-1] + d
        )
      );
    }
  }

  // reconstruct
  int i = m-1;
  int j = n-1;
  int k = longer;
  while (0 <= i && 0 <= j) {
    int left = A[i][j-1];
    int up = A[i-1][j];
    int diag = A[i-1][j-1];
    int smallest = min(diag, min(left, up));

    if (smallest == left) {
      ret[0][k] = '-';
      ret[1][k] = ' ';
      ret[2][k] = Y[j];
      j--;
    } else if (smallest == up) {
      ret[0][k] = X[i];
      ret[1][k] = ' ';
      ret[2][k] = '-';
      i--;
    } else {
      ret[0][k] = X[i];
      ret[1][k] = (X[i] == Y[j])? '|' : ' ';
      ret[2][k] = Y[j];
      i--; j--;
    }
  }

  return ret;
}

int main(int argc, char const *argv[]) {
  /* code */
  if (argc != 5) {
    cerr << "Wrong # params!!" << endl;
    cerr << "Usage: ./DNA <X> <Y> <d> <a>" << endl;
    return 1;
  }

  // get inputs from std
  const char* X = argv[1];
  const char* Y = argv[2];
  int d = atoi(argv[3]);
  int a = atoi(argv[4]);

  char** alignment = getMinAlignment(X, Y, d, a);
  // print
  for (int i = 0; i < 3; i++) {
    cout << alignment[i] << endl;
    delete alignment[i];
  }
  delete alignment;

  return 0;
}
