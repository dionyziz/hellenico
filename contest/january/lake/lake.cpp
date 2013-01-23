#include <cstdio>
#include <cstdlib>

int B[ 5002 ], N, M, Q, i, u, v;

inline bool adj( int u, int v ) {
    return abs( ( u - v ) % N ) == 1
        || B[ ( ( v - u ) + N ) % N ] != u % 2;
}

int main() {
    FILE* fi = fopen( "lake.in", "r" ),
        * fo = fopen( "lake.out", "w" );

    fscanf( fi, "%i %i", &N, &M );
    for ( i = 0; i < M; ++i ) {
        fscanf( fi, "%i", &u );
        B[ u ] = 1;
    }
    fscanf( fi, "%i", &Q );
    for ( i = 0; i < Q; ++i ) {
        fscanf( fi, "%i %i", &u, &v );
        if ( u == v ) {
            fprintf( fo, "0\n" );
        }
        else if ( adj( u, v ) ) {
            fprintf( fo, "1\n" );
        }
        else {
            fprintf( fo, "2\n" );
        }
    }
    return 0;
}
