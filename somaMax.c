#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#define CROSSOVER 20
#define Q 3
#define P 5

typedef struct {
  int left;
  int right;
  int sum;
} MSS;

MSS bruteForce (int *A, int low, int high) {
  int i, j, temp;
  MSS ret = {low, high, A[low]};

  for(i = low; i < high; i++) {
    temp = 0;
    for(j = i; j < high; j++) {
      temp += A[j];
      if(temp >= ret.sum) {
        ret.left = i;
        ret.right = j+1;
        ret.sum = temp;
      }
    }
  }
  return ret;
}

MSS recursiveCROSS (int *A, int low, int mid, int high) {
  int i, j, left_sum, right_sum;
  MSS ret = {low, high, 0};
  left_sum = right_sum = INT_MIN;

  for(i = mid-1; i >= low; i--) {
    ret.sum += A[i];
    if(ret.sum >= left_sum) {
      left_sum = ret.sum;
      ret.left = i;
    }
  }

  ret.sum = 0;
  for(j = mid; j < high; j++) {
    ret.sum += A[j];
    if(ret.sum >= right_sum) {
      right_sum = ret.sum;
      ret.right = j+1;
    }
  }
  ret.sum = left_sum+right_sum;
  return ret;
}

MSS recursive (int *A, int low, int high) {
  if((high-low) < CROSSOVER)
    return bruteForce(A, low, high);
  else {
    int mid = (low+high)/2;
    MSS left = recursive(A, low, mid);
    MSS right = recursive(A, mid, high);
    MSS cross = recursiveCROSS(A, low, mid, high);
    if(left.sum >= right.sum && left.sum >= cross.sum)
      return left;
    else if(right.sum >= left.sum && right.sum >= cross.sum)
      return right;
    else
      return cross;
  }
}

void e(int ini, int n) {
  int i, j;
  for(i = 0; i < 10; i++) {
    for(j = 0; j < n; j++) printf(" ");
    printf("%2d", ini+i);
  }
}

void imprime (int *A, int left, int right, int t) {
  int i;
  printf("\nVetor original:\n");
  printf("x  :");
  e(1, P-2);
  printf("\n%-*d:", Q, 0);
  for(i = 0; i < t; i++) {
    printf("%+*d", P, A[i]);
    if(i != 0 && i != (t-1) && (i+1)%10 == 0)
      printf("\n%-*d:", Q, i+1);
  }
  printf("\n\n");

  printf("\nVetor resposta:\n");
  printf("x  :");
  e(1, P-2);
  printf("\n%-*d:", Q, 0);
  for(i = 0; i < t; i++) {
    if(i == left)
      printf(" [");
    else if(i == right)
      printf("] ");
    else
      printf("  ");
    printf("%+*d", P-2, A[i]);
    if(i != 0 && i != (t-1) && (i+1)%10 == 0)
      printf("\n%-*d:", Q, i+1);
  }
  if(right == i)
    printf("] ");
  printf("\n\n");
}

int main () {
  srand(time(NULL));
  int i, t, n = 30;
  scanf("%d", &t);
  int A[t];
  for(i = 0; i < t; i++)
    A[i] = rand()%199 - 99;

  MSS res = {0, t, INT_MIN};
  double time_bf, time_rc;
  while(1) {
    clock_t start, stop;

    start = clock();
    for (i = 0; i < 1000000; i++)
      res = bruteForce(A, 0, n);
    stop = clock();
    time_bf = ((double) (stop-start)) / CLOCKS_PER_SEC;

    start = clock();
    for (i = 0; i < 1000000; i++)
      res = recursive(A, 0, n);
    stop = clock();
    time_rc = ((double) (stop-start)) / CLOCKS_PER_SEC;

    if(time_bf > time_rc || n == t)
      break;
    n++;
  }

  int op;
  printf("\nImprimir?");
  scanf("%d", &op);
  if(op)
    imprime(A, res.left, res.right, t);

  printf("\nTempo gasto (BRUTE): %21.10g ?s.\n", time_bf);
  printf("\nTempo gasto (RECUR): %21.10g ?s.\n", time_rc);
  printf("\n\nN = %d.\nSoma = %d.\nLeft = %d\nRight = %d.\n\n", n, res.sum, res.left+1, res.right);

  return 0;
}
