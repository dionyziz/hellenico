#include <cstdio>
#include <set>

using namespace std;

set< int > primes;
int N;

void eratosthenes() {
    primes.insert( 2 );

    for ( int candidate = 3; candidate < N; ++candidate ) {
        bool primeq = true;
        for ( set< int >::iterator disprover = primes.begin();
              disprover != primes.end();
              ++disprover ) {
            if ( candidate % *disprover == 0 ) {
                primeq = false;
                break;
            }
            if ( ( *disprover ) * ( *disprover ) > candidate ) {
                break;
            }
        }
        if ( primeq ) {
            primes.insert( candidate );
        }
    }
}

int main() {
    FILE *fi = fopen( "goldbach.in", "r" ), *fo = fopen( "goldbach.out", "w" );

    fscanf( fi, "%i", &N );
    eratosthenes();
    for ( set< int >::iterator prime = primes.begin(); prime != primes.end(); ++prime ) {
        set< int >::iterator complement = primes.find( N - *prime );
        if ( complement != primes.end() ) {
            fprintf( fo, "%i %i\n", *prime, *complement );
            return 0;
        }
    }
}
