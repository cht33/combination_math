#include <cstdio>
#include <cstring>
#include <algorithm>
#include <ctime>

#define SHOW

struct Permutation {
    const static int MAXN = 20;
    int N;
    char s[2*MAXN]; // output string
    int r[MAXN]; // radix number
    int cnt;

    void init() {
        memset(s, 0, 2*MAXN*sizeof(char));
        memset(r, 0, MAXN*sizeof(int));
        for (int i = 1; i <= N; i++)
            s[i] = 'a' + i - 1;
        s[0] = 0;
        cnt = 1;
    }

    void generate(int n) {
        N = n;
        auto start = clock();
        init();
        start = clock();
        dictionary();
        printf("dictionary: %lf\n", (double)(clock() - start)*1000/CLOCKS_PER_SEC);

        init();
        start = clock();
        recursive();
        printf("recursive: %lf\n", (double)(clock() - start)*1000/CLOCKS_PER_SEC);

        init();
        start = clock();
        next_permutation();
        printf("next_permutation: %lf\n", (double)(clock() - start)*1000/CLOCKS_PER_SEC);
    }

    void neighbour_exchange() {
        while (true) {
            #ifdef SHOW
            puts(s+1);
            #endif
        }
    }

    void next_permutation() {
        auto st = s+1;
        do {
            #ifdef SHOW
            puts(st);
            #endif
        } while (std::next_permutation(st, st+N));
    }

    void recursive() {
        for (int i = 1; i <= N; i++) {
            if (r[i] != 0) continue;
            r[i] = 1;

            #ifdef SHOW
            s[cnt++] = 'a' + i - 1;
            #else
            s[cnt++] = i;
            #endif

            if (cnt == N+1) {
                #ifdef SHOW
                puts(s+1);
                #endif
            } else {
                recursive();
            }
            r[i] = 0;
            cnt--;
        }
    }

    void dictionary() {
        while (true) {
            #ifdef SHOW
            puts(s+1);
            #endif

            int i = N-1;
            while (s[i+1] < s[i]) i--;
            if (i == 0) break;
            int j = N;
            while (s[j] < s[i]) j--;
            char c = s[j];
            s[j] = s[i], s[i] = c;
            std::reverse(s+i+1, s+N+1);
        }
    }
} perm;

int main() {
    perm.generate(3);
    return 0;
}