#include <cstdio>
#include <cstdlib>

int cmp( const void *a, const void *b ) {
    return *( int* )( a ) - *( int* )( b );
}

int main() {
    FILE *in = fopen( "acropolis.in", "r" ), *out = fopen( "acropolis.out", "w" );
    int i, j, N, A[ 1005 ], B[ 1005 ];

    fscanf( in, "%i", &N );
    for ( i = 0, j = 0; i < N; ++i ) {
        fscanf( in, "%i", &B[ i ] );
        if ( B[ i ] != 1 ) {
            A[ j ] = B[ i ];
            ++j;
        }
    }
    qsort( A, j, sizeof( int ), cmp );
    for ( i = 0, j = 0; i < N; ++i ) {
        if ( B[ i ] == 1 ) {
            fprintf( out, "%i\n", 1 );
        }
        else {
            fprintf( out, "%i\n", A[ j ] );
            ++j;
        }
    }

    return 0;
}
