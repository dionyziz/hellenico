#include <cstdio>

using namespace std;

const int MAX_N = 502;

int main() {
    FILE* in = fopen( "paso.in", "r" ),
        * out = fopen( "paso.out", "w" );
    int N, a;
    bool A[ 3 * MAX_N ][ 3 * MAX_N ];

    fscanf( in, "%i", &N );
    for ( int i = 0; i < 3 * N; ++i ) {
        for ( int j = 0; j < 3 * N; ++j ) {
            fscanf( in, "%i", &a );
            A[ i ][ j ] = a;
        }
    }
    for ( int i = 0; i < N; ++i ) {
        for ( int j = 0; j < N; ++j ) {
            int c = 0;
            for ( int k = 0; k < 3; ++k ) {
                for ( int l = 0; l < 3; ++l ) {
                    c += A[ 3 * i + k ][ 3 * j + l ];
                }
            }
            fprintf( out, "%i", c > 4 );
            if ( j < N - 1 ) {
                fprintf( out, " " );
            }
        }
        fprintf( out, "\n" );
    }
    return 0;
}
