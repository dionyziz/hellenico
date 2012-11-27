#include <cstdio>

using namespace std;

int main() {
    FILE* in = fopen( "trlights.in", "r" ),
        * out = fopen( "trlights.out", "w" );
    char a;
    int r = 0;
    
    for ( int i = 0; i < 10; ++i ) {
        fscanf( in, "%c", &a );
        r += a == 'r';
    }
    if ( r >= 5 ) {
        fprintf( out, "*\n" );
    }
    else if ( r == 0 ) {
        fprintf( out, "****\n" );
    }
    else if ( r % 2 == 0 ) {
        fprintf( out, "***\n" );
    }
    else {
        fprintf( out, "**\n" );
    }

    return 0;
}
