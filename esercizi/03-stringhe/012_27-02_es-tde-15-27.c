//
//  main.c
//  es tde 15 27
//
//  Created by Francesco Roscio Ricon on 27/02/26.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void f( int * a, int * n ) {
  if( *n % 2 ) {
    printf("%d", a[*n] );
    (*n)--;
    printf("%d", *(a+*n) );
    f( a, n );
    (*n)++;
  }
  return;
}

int main() {
  int i = 5, *v;
  char p[6], *d[6];
  d[i] = (char *) malloc( i );
  strcpy( d[i], "EURO"  );
  strcpy( p  , "ADIEU" );
  v = (int *) malloc(sizeof(int)*8);
  printf("%s_",*(d+i));
  for( i=0; i<4; i++ ) {
    *(v+i) = *(p+i) - (*p+i);
    d[i] = p+i;
    f( v, &i );
  }
  return 0;
}
// wtf
