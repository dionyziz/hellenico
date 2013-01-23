#include <cstdio>

int main() {
    FILE* fi = fopen("cake.in", "r"),
        * fo = fopen("cake.out", "w");
    unsigned int N, x, i, k = 0;

    fscanf( fi, "%i %i", &N, &x );
    x = N / x + 1;
    for ( i = 0; x; ++i, x >>= 1 ) { // floor( lg( N / x + 1 ) )
        if ( x & 1 ) {
            k = i;
        }
    }
    fprintf( fo, "%i\n", k );

    return 0;
}
