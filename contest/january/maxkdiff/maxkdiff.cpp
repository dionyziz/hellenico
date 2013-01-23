#include <cstdio>
#include <map>

using namespace std;

int main() {
    FILE* fi = fopen( "maxkdiff.in", "r" ),
        * fo = fopen( "maxkdiff.out", "w" );
    int N, K, i, a, key, m = 0;
    map< int, int > interval;
    map< int, int >::iterator it;

    fscanf( fi, "%i %i", &N, &K );
    int A[ N ];
    for ( i = 0; i < N; ++i ) {
        fscanf( fi, "%i", &a );
        A[ i ] = a;
        if ( i >= K ) {
            key = A[ i - K ];
            if ( --interval[ key ] == 0 ) {
                interval.erase( key );
            }
        }
        if ( interval.find( a ) == interval.end() ) {
            interval[ a ] = 1;
        }
        else {
            ++interval[ a ];
        }
        m = max( m, ( int )interval.size() );
    }
    fprintf( fo, "%i\n", m );

    return 0;
}
