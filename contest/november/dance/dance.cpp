#include <cstdio>
#include <set>
#include <cassert>

using namespace std;

const bool LEFT = false;
const bool RIGHT = true;
const int INF = 300000009;

int loffset = 0, roffset = 0;

struct Dancer {
    int location;
    bool direction;
    int closest;
    bool done;
    int steps;
};
Dancer dancers[ 300123 ];

bool cmpllocation( int a, int b ) {
    return dancers[ a ].location < dancers[ b ].location;
}

bool cmprlocation( int a, int b ) {
    return dancers[ a ].location > dancers[ b ].location;
}

inline int dist( int i ) {
    if ( dancers[ i ].closest == -1 ) {
        return -1;
    }
    return dancers[ dancers[ i ].closest ].location + loffset - ( dancers[ i ].location + roffset );
}

bool cmpdistance( int a, int b ) {
    if ( dancers[ a ].closest == -1 ) {
        if ( dancers[ b ].closest == -1 ) {
            return dancers[ a ].location < dancers[ b ].location;
        }
        return false;
    }
    if ( dancers[ b ].closest == -1 ) {
        return true;
    }
    return dist( a ) < dist( b );
}

typedef set< int, bool( * )( int, int ) > dset;

dset left( cmpllocation );
dset right( cmprlocation );
dset next( cmpdistance );

void progress( int amount ) {
    roffset += amount;
    loffset -= amount;
}

int main() {
    FILE* in = fopen( "dance.in", "r" ),
        * out = fopen( "dance.out", "w" );
    int A, B, L, R, i, pos,
        offLeft, offRight, offClose;
    dset::iterator n;

    fscanf( in, "%i %i", &A, &B );
    A *= 2; B *= 2;
    
    fscanf( in, "%i %i", &L, &R );
    for ( i = 0; i < L + R; ++i ) {
        dancers[ i ].done = false;
        dancers[ i ].steps = 0;
    }
    for ( i = 0; i < L; ++i ) {
        fscanf( in, "%i", &pos );
        dancers[ i ].location = 2 * pos;
        dancers[ i ].direction = LEFT;
        dancers[ i ].closest = -1;
        left.insert( i );
    }
    for ( i = L; i < L + R; ++i ) {
        fscanf( in, "%i", &pos );
        dancers[ i ].location = 2 * pos;
        dancers[ i ].direction = RIGHT;
        n = left.lower_bound( i );
        if ( n == left.end() ) {
            dancers[ i ].closest = -1;
        }
        else {
            dancers[ i ].closest = *n;
        }
        right.insert( i );
        next.insert( i );
    }
    while ( !left.empty() || !right.empty() ) {
        if ( left.empty() ) {
            printf( "Noone going left.\n" );
            offLeft = INF;
        }
        else {
            n = left.begin();
            assert( n != left.end() );
            int p = *n;
            offLeft = dancers[ p ].location + loffset - A;
            printf( "Left-most dancers[ %i ] at %i.\n", p, dancers[ p ].location + loffset );
        }
        if ( right.empty() ) {
            printf( "Noone going right.\n" );
            offRight = INF;
        }
        else {
            n = right.begin();
            assert( n != right.end() );
            int p = *n;
            offRight = B - ( dancers[ p ].location + roffset );
            printf( "Right-most dancers[ %i ] at %i.\n", p, dancers[ p ].location + roffset );
        }
        if ( next.empty() ) {
            offClose = INF;
        }
        else {
            n = next.begin();
            assert( n != next.end() );
            int p = *n;
            Dancer d = dancers[ p ];
            assert( d.direction == RIGHT );
            assert( !d.done );
            offClose = dist( *( next.begin() ) );
            assert( offClose % 2 == 0 );
            offClose /= 2;
        }
        printf( "offLeft = %i\toffRight = %i\toffClose = %i\n", offLeft, offRight, offClose );
        if ( offLeft <= offRight && offLeft <= offClose ) {
            printf( "Fall off left after %i steps.\n", offLeft );
            n = left.begin();
            int p = *n;
            assert( n != left.end() );
            progress( offLeft );
            dancers[ p ].done = true;
            dancers[ p ].steps += loffset;
            left.erase( n );
        }
        else if ( offRight <= offLeft && offRight <= offClose ) {
            printf( "Fall off right after %i steps.\n", offRight );
            n = right.begin();
            assert( n != right.end() );
            int p = *n;
            progress( offRight );
            dancers[ p ].done = true;
            dancers[ p ].steps += roffset;
            right.erase( n );
            n = next.find( p );
            assert( n != next.end() );
            next.erase( n );
        }
        else {
            printf( "Collision after %i steps.\n", offClose );
            assert( offClose >= 0 );
            
            assert( offClose != INF );
            assert( offClose < offLeft );
            assert( offClose < offRight );
            progress( offClose );

            n = next.begin();
            assert( n != next.end() );
            int p = *n;

            printf( "Swapping BEFORE: [ %i ] -> <- [ %i ].\n", p, dancers[ p ].closest );

            Dancer d = dancers[ p ];
            assert( d.direction == RIGHT );
            d.steps = d.steps + roffset - loffset;
            printf( "p location before: %i\n", d.location + roffset );
            d.location = d.location + roffset - loffset;
            printf( "p location after: %i\n", d.location + loffset );
            d.direction = LEFT;
            int q = d.closest;
            d.closest = -1;
            dancers[ p ] = d;
            next.erase( n );
            n = right.find( p );
            assert( n != right.end() );
            right.erase( n );
            left.insert( p );

            assert( q != -1 );
            Dancer e = dancers[ q ];
            assert( e.direction == LEFT );
            e.steps = e.steps + loffset - roffset;
            e.location = e.location + loffset - roffset;
            e.direction = RIGHT;
            n = left.lower_bound( q );
            if ( n == left.end() ) {
                e.closest = -1;
            }
            else {
                e.closest = *n;
            }
            n = right.lower_bound( p );
            if ( n != right.end() ) {
                int r = *n;
                printf( "r = %i.\n", r );
                assert( dancers[ r ].direction == RIGHT );
                dancers[ r ].closest = p;
                right.erase( n );
                right.insert( r );
            }
            dancers[ q ] = e;
            n = left.find( q );
            assert( n != left.end() );
            left.erase( n );
            right.insert( q );
            next.insert( q );

            printf( "After collision %i going left, %i going right.\n", left.size(), right.size() );
        }
    }

    for ( i = 0; i < L + R; ++i ) {
        assert( dancers[ i ].steps % 2 == 0 );
        fprintf( out, "%i\n", dancers[ i ].steps / 2 );
    }

    return 0;
}
