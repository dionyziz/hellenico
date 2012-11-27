#include <cstdio>
#include <list>
#include <queue>
#include <vector>

using namespace std;

struct Edge {
    int v;
    int type;
};
vector< list< Edge > > E;
int N, M, i;

int BFS( int s, int t, int type ) {
    queue< pair< int, int > > q;
    pair< int, int > r;
    int u;
    bool visited[ 10001 ];

    for ( i = 0; i < N; ++i ) {
        visited[ i ] = false;
    }
    q.push( make_pair( s, 0 ) );
    visited[ s ] = true;
    while ( !q.empty() ) {
        r = q.front();
        u = r.first;
        q.pop();
        if ( u == t ) {
            return r.second;
            break;
        }
        for ( list< Edge >::iterator it = E[ u ].begin(); it != E[ u ].end(); ++it ) {
            if ( type == 1 || it->type == 0 ) {
                if ( !visited[ it->v ] ) {
                    // printf( "Pushed %i.\n", it->v );
                    q.push( make_pair( it->v, r.second + 1 ) );
                    visited[ it->v ] = true;
                }
            }
        }
    }
    return -1;
}

int main() {
    FILE* in = fopen( "jigsaw.in", "r" ),
        * out = fopen( "jigsaw.out", "w" );
    int A, B, C, D, u, v, type;

    fscanf( in, "%i %i", &N, &M ); 
    fscanf( in, "%i %i %i", &A, &B, &C );
    --A; --B; --C;

    for ( i = 0; i < N; ++i ) {
        E.push_back( list< Edge >() );
    }

    for ( i = 0; i < M; ++i ) {
        fscanf( in, "%i %i %i", &u, &v, &type );
        --u; --v;
        E[ u ].push_back( ( Edge ){ v, type } );
        E[ v ].push_back( ( Edge ){ u, type } );
    }

    D = BFS( A, B, 0 );
    if ( D == -1 ) {
        D = BFS( A, C, 0 ) + BFS( C, B, 1 );
    }
    fprintf( out, "%i\n", D );

    return 0;
}
