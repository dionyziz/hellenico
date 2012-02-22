#include <cstdio>

using namespace std;

int main() {
    FILE *in = fopen( "time.in", "r" ), *out = fopen( "time.out", "w" );
    int H, M, S, t, m, s;

    fscanf( in, "%i:%i:%i", &H, &M, &S );
    t = S + 60 * M + 60 * 60 * H;
    t *= 2;
    s = t % 60;
    t /= 60;
    m = t % 60;
    t /= 60;
    fprintf( out, "%02i:%02i:%02i\n", t, m, s );

    return 0;
}
