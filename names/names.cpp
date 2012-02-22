#include <cstdio>
#include <cstring>
#include <set>

using namespace std;

void next( char *name ) {
    char f = *name;
    char *t = name;

    while ( t[ 1 ] ) {
        t[ 0 ] = t[ 1 ];
        ++t;
    }
    t[ 0 ] = f;
}

int main() {
    FILE *in = fopen( "names.in", "r" ), *out = fopen( "names.out", "w" );
    int N;
    char localMin[ 30 ];
    char globalMin[ 30 ];
    char globalMinScrambled[ 30 ];
    char name[ 30 ];

    for ( int i = 0; i < 25; ++i ) {
        globalMinScrambled[ i ] = 'z';
    }
    globalMinScrambled[ 25 ] = '\0';

    fscanf( in, "%i", &N );
    for ( int i = 0; i < N; ++i ) {
        fscanf( in, "%s", &name );
        int l = strlen( name );
        strncpy( localMin, name, 25 );
        while ( l-- ) {
            next( name );
            if ( strcmp( name, localMin ) < 0 ) {
                strncpy( localMin, name, 25 );
            }
        }
        if ( strcmp( localMin, globalMinScrambled ) < 0 ) {
            strncpy( globalMinScrambled, localMin, 25 );
            strncpy( globalMin, name, 25 );
        }
    }
    fprintf( out, "%s\n", globalMin );

    return 0;
}
