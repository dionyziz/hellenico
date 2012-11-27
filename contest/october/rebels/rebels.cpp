#include <cstdio>
#include <algorithm>

using namespace std;

const int MAX_K = 102;
const int MAX_N = 302;

int k, n;
int a[ MAX_K ], b[ MAX_N ],
    centers[ MAX_K ], cut[ MAX_K ];

int main() {
    FILE* in = fopen( "rebels.in", "r" ),
        * out = fopen( "rebels.out", "w" );
    int i;

    fscanf( in, "%i %i", &k, &n );

    // printf( "k = %i\nn = %i\n", k, n );

    for ( i = 0; i < k; ++i ) {
        fscanf( in, "%i", &a[ i ] );
        centers[ i ] = a[ i ];
        cut[ i ] = -1;
    }
    sort( a, a + k );
    // for ( i = 0; i < k; ++i ) {
    //     printf( "Truck %i at location %i.\n", i, a[ i ] );
    // }
    sort( centers, centers + k );
    for ( i = 0; i < n; ++i ) {
        fscanf( in, "%i", &b[ i ] );
    }
    sort( b, b + n );
    // for ( i = 0; i < n; ++i ) {
    //     printf( "Moto %i at location %i.\n", i, b[ i ] );
    // }
    bool converged = true;
    int totalcost = 0;
    do {
        printf( "No convergence.\n" );
        converged = true;
        int m = 0;

        for ( i = 0; i < n && m < k - 1; ++i ) {
            if ( abs( b[ i ] - centers[ m ] ) >= abs( b[ i ] - centers[ m + 1 ] ) ) {
                if ( cut[ m ] != i ) {
                    printf( "Setting cut[ %i ] = %i\n", m, i );
                    converged = false;
                    cut[ m ] = i;
                }
                ++m;
                --i;
            }
        }
        for ( i = m; i < k; ++i ) {
            cut[ i ] = n;
        }
        printf( "Cuts:\n" );
        for ( i = 0; i < k; ++i ) {
            printf( "cut[ %i ] = %i\n", i, cut[ i ] );
        }
        printf( "Centers:\n" );
        for ( i = 0; i < k; ++i ) {
            printf( "centers[ %i ] = %i\n", i, centers[ i ] );
        }
        int j = 0;
        totalcost = 0;
        for ( i = 0; i < k; ++i ) {
            int cost = 0;
            printf( "For i = %i, j is %i\n", i, j );
            for ( int q = j; q < cut[ i ]; ++q ) {
                cost += abs( a[ i ] - b[ q ] );
            }
            // printf( "a[ %i ] = %i.\n", i, a[ i ] );
            printf( "Unmoved cost for truck %i is %i.\n", i, cost );
            int children, bestq;
            if ( i == 0 ) {
                children = cut[ i ];
            }
            else {
                children = cut[ i ] - cut[ i - 1 ];
            }
            printf( "Children = %i\n", children );
            int mincost = cost;
            bestq = -1;

            cost = abs( a[ i ] - b[ j ] );
            for ( int q = j + 1; q < cut[ i ]; ++q ) {
                cost += abs( b[ j ] - b[ q ] );
            }
            printf( "Cost for moving to child 0 = %i.\n", cost );
            if ( cost < mincost ) {
                printf( "(minimum)\n" );
                bestq = j;
                mincost = cost;
            }
            for ( int q = j + 1; q < cut[ i ]; ++q ) {
                printf( "Attempting move to child %i.\n", q );
                cost += ( ( q - j ) - ( cut[ i ] - q ) ) * ( b[ q ] - b[ q - 1 ] );
                cost += abs( a[ i ] - b[ q ] ) - abs( a[ i ] - b[ q - 1 ] );
                printf( "Cost is %i.\n", cost );
                if ( cost < mincost ) {
                    printf( "(new minimum)\n" );
                    mincost = cost;
                    bestq = q;
                }
            }
            if ( bestq == -1 ) {
                if ( centers[ i ] != a[ i ] ) {
                    printf( "Center change.\n" );
                    converged = false;
                    centers[ i ] = a[ i ];                
                }
            }
            else {
                if ( centers[ i ] != b[ bestq ] ) {
                    printf( "Center change.\n" );
                    converged = false;
                    centers[ i ] = b[ bestq ];
                    printf( "centers[ %i ] = %i\n", i, centers[ i ] );
                }
            }
            totalcost += mincost;
            j = cut[ i ];
            // printf( "End of iteration j = %i.\n", j );
        }
    } while ( !converged );

    fprintf( out, "%i\n", totalcost );

    return 0;
}
