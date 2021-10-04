#include <cstdio>
#include <cstring>
#include <algorithm>
#include <ctime>

// #define SHOW

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

        // init();
        // start = clock();
        // recursive();
        // printf("recursive: %lf\n", (double)(clock() - start)*1000/CLOCKS_PER_SEC);

        init();
        start = clock();
        next_permutation();
        printf("next_permutation: %lf\n", (double)(clock() - start)*1000/CLOCKS_PER_SEC);

        init();
        start = clock();
        neighbour_exchange();
        printf("neighbour: %lf\n", (double)(clock() - start)*1000/CLOCKS_PER_SEC);
    }

    void neighbour_exchange() {
        int idx_N = N, t_N = -1;
        while (true) {
            #ifdef SHOW
            puts(s+1);
            #endif

            int i = N;
            r[i] += 1;
            if (r[i] < N) {
                char c = s[idx_N];
                idx_N += t_N;
                s[idx_N-t_N] = s[idx_N];
                s[idx_N] = c;
                continue;
            }
            while (r[i] == i) {
                r[i] = 0;
                r[--i] += 1;
            }
            if (i == 0) break;
            int j = 1;
            char c = 'a'+i-1;
            while (s[j] != c) j++;
            // 只需考虑最后一位的运算结果，1为奇，0为偶
            int t = (r[i-1] ^ (~i & r[i-2])) & 1;
            t = (t << 1) - 1;
            c = s[j+t], s[j+t] = s[j], s[j] = c;
            t_N = (r[N-1] ^ (~N & r[N-2])) & 1;
            t_N = (t_N << 1) - 1;
        }
    }

    // void neighbour_exchange() {
    //     while (true) {
    //         #ifdef SHOW
    //         puts(s+1);
    //         #endif

    //         int i = N;
    //         r[i] += 1;
    //         while (r[i] == i) {
    //             r[i] = 0;
    //             r[--i] += 1;
    //         }
    //         if (i == 0) break;
    //         int j = 1;
    //         char c = 'a'+i-1;
    //         while (s[j] != c) j++;
    //         // 只需考虑最后一位的运算结果，1为奇，0为偶
    //         int t = (r[i-1] ^ (~i & r[i-2])) & 1;
    //         t = (t << 1) - 1;
    //         c = s[j+t], s[j+t] = s[j], s[j] = c;
    //     }
    // }

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
    perm.generate(13);
    return 0;
}