#include <cstdio>
#include <algorithm>

using namespace std;

int main() {
    FILE *in = fopen( "tickets.in", "r" ), *out = fopen( "tickets.out", "w" );
    int A, B, C, D, N;

    fscanf( in, "%i %i %i %i %i", &N, &A, &B, &C, &D );
    int cost = 10 * N;
    cost = min( cost, 9 * max( N, A ) );
    cost = min( cost, 8 * max( N, B ) );
    cost = min( cost, 7 * max( N, C ) );
    cost = min( cost, 5 * max( N, D ) );
    fprintf( out, "%i\n", cost );

    return 0;
}
