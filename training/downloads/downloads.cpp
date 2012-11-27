#include <stdio.h>
#include <math.h>
#include <stdio.h>

int main() {
    FILE* fi = fopen( "downloads.in", "r" );
    FILE* fo = fopen( "downloads.out", "w" );
    int N, i, T, X, bandwidth = 0, totalsize = 0;

    fscanf( fi, "%i\n", &N );

    for ( i = 0; i < N; ++i ) {
        fscanf( fi, "%i %i\n", &T, &X );
        bandwidth += T;
        totalsize += T * X;
    }
    fprintf( fo, "%d\n", ( int )floor( ( float )totalsize / ( float )bandwidth + 0.5 ) );

    return 0;
}
