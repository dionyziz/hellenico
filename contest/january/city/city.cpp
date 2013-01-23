#include <cstdio>
#include <algorithm>

using namespace std;

bool A[ 101 ][ 101 ];
int B[ 101 ];
int i, j, k, N;

bool cmp( int a, int b ) {
    return A[ a ][ b ];
}

void floyd_warshall() {
    for ( k = 0; k < N; ++k ) {
        for ( i = 0; i < N; ++i ) {
            for ( j = 0; j < N; ++j ) {
                A[ i ][ j ] = A[ i ][ j ] || ( A[ i ][ k ] && A[ k ][ j ] );
            }
        }
    }
}

int main() {
    FILE* fi = fopen( "city.in", "r" ),
        * fo = fopen( "city.out", "w" );

    fscanf( fi, "%i", &N );

    for ( i = 0; i < N - 1; ++i ) {
        fscanf( fi, "%i", &k );
        --k;
        B[ i ] = i;
        if ( k < N ) {
            A[ i ][ k ] = true;
        }
        for ( j = i + 1; j < k; ++j ) {
            A[ j ][ i ] = true;
        }
    }
    B[ N - 1 ] = N - 1;

    floyd_warshall();
    sort( B, B + N, cmp );

    for ( k = 0; k < N; ++k ) {
        for ( i = k; i < N - 1 && !A[ B[ i ] ][ B[ i + 1 ] ]; ++i ) {}
        for ( j = 0; j < i - k + 1; ++j ) {
            fprintf( fo, "%i\n", i - k + 1 );
        }
        k = i;
    }

    return 0;
}
