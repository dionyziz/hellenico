#include <cstdio>

using namespace std;

int main() {
    FILE* in = fopen( "mosaic.in", "r" ),
        * out = fopen( "mosaic.out", "w" );
    int N, M, i, j, x, y, a, b, count = 0;
    char A[ 101 ][ 101 ];
    int Q[ 256 ], C[ 5 ];

    Q[ 'a' ] = 0;
    Q[ 'p' ] = 1;
    Q[ 'g' ] = 2;
    Q[ 'x' ] = 3;
    Q[ 'k' ] = 4;

    fscanf( in, "%i %i", &N, &M );
    for ( i = 0; i < N; ++i ) {
        fscanf( in, "%s", A[ i ] );
    }
    
    for ( i = 0; i < N; ++i ) {
        for ( j = 0; j < M; ++j ) {
            if ( A[ i ][ j ] == 'x' ) {
                C[ 0 ] = C[ 1 ] = C[ 2 ] = C[ 3 ] = C[ 4 ] = 0;
                for ( x = -1; x <= 1; ++x ) {
                    for ( y = -1; y <=1 ; ++y ) {
                        a = i + x;
                        b = j + y;
                        if ( a < 0 || b < 0
                          || a >= N || b >= M
                          || ( x == 0 && y == 0 ) ) {
                            continue;
                        }
                        ++C[ Q[ ( int )A[ a ][ b ] ] ];
                    }
                }
                if ( C[ Q[ 'p' ] ] <= 2 && C[ Q[ 'g' ] ] >= 2 && C[ Q[ 'x' ] ] == 0 ) {
                    ++count;
                }
            }
        }
    }
    fprintf( out, "%i\n", count );
    return 0;
}
