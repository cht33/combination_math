#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <ctime>

// #define SHOW

struct Permutation {
    const static int MAXN = 1000;
    int N;
    char s[2*MAXN]; // output string
    char s1[2*MAXN]; // backup
    int lb;
    char* st;
    int r[MAXN]; // radix number
    int cnt;
    int next[MAXN];

    void init() {
        memset(s, 0, 2*MAXN*sizeof(char));
        memset(r, 0, MAXN*sizeof(int));
        for (int i = 1; i <= N; i++) {
            s[i] = 'a' + i - 1;
            s1[i-1] = 'a' + i - 1;
        }
        s[0] = 0;
        cnt = 1;
        lb = N;
        st = s+1;
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
        heap();
        printf("heap: %lf\n", (double)(clock() - start)*1000/CLOCKS_PER_SEC);

        // init();
        // start = clock();
        // new_recursive();
        // printf("new_recursive: %lf\n", (double)(clock() - start)*1000/CLOCKS_PER_SEC);

        // init();
        // start = clock();
        // next_permutation();
        // printf("next_permutation: %lf\n", (double)(clock() - start)*1000/CLOCKS_PER_SEC);

        // init();
        // start = clock();
        // increase_base();
        // printf("increase_base: %lf\n", (double)(clock() - start)*1000/CLOCKS_PER_SEC);

        // init();
        // start = clock();
        // new_increase_base();
        // printf("new_increase_base: %lf\n", (double)(clock() - start)*1000/CLOCKS_PER_SEC);

        // init();
        // start = clock();
        // decrease_base();
        // printf("decrease_base: %lf\n", (double)(clock() - start)*1000/CLOCKS_PER_SEC);

        init();
        start = clock();
        neighbour_exchange();
        printf("neighbour_exchange: %lf\n", (double)(clock() - start)*1000/CLOCKS_PER_SEC);
    }

    void heap() {
        #ifdef SHOW
        puts(st);
        #endif
        int i = 1;
        while (i < N) {
            if (r[i] < i) {
                int t = (i & 1) ? r[i] : 0;
                char c = st[t]; st[t] = st[i], st[i] = c;
                #ifdef SHOW
                puts(st);
                #endif
                r[i]++, i = 1;
            } else {
                r[i++] = 0;
            }
        }
    }

    void increase_base() {
        while(true){
            for(int i = 0;i <= N;i ++)next[i] = i - 1;
            for(int i = N - 2;i >= 0;i --){
                int itemcnt = r[i];
                int preindex = N;
                int index = next[N];
                while(itemcnt){
                    preindex = index;
                    index = next[index];
                    itemcnt --;
                }
                s[index + 1] = 'a' + i + 1;
                next[preindex] = next[index];
            }
            s[next[N] + 1] = 'a';

            #ifdef SHOW
            puts(s+1);
            #endif

            int i = 0;
            r[i] ++;
            while(r[i] >= i + 2){
                r[i] -= i + 2;
                r[++i] ++;
            }
            if(r[N - 1])break;
        }
    }

    void new_increase_base() {
        int pointer[MAXN];
        for(int i = 1;i <= N;i ++){
            pointer[i] = i;
        }
        while(true) {
            #ifdef SHOW
            puts(s+1);
            #endif

            int i = 2;
            r[i] ++;
            while(r[i] >= i){
                r[i] -= i;
                r[++i] ++;
            }

            if(i == N + 1)break;

            for(int j = 1;j < i; j ++) {
                int pj = pointer[j], pi = pointer[i];
                if (pj < pi) {
                    char c = s[pi]; s[pi] = s[pj], s[pj] = c;
                    pointer[i] = pj, pointer[j] = pi;
                    break;
                }
            }
            int l = 1, r = i - 1;
            while(l < r){
                int pl = pointer[l], pr = pointer[r];
                char c = s[pl]; s[pl] = s[pr], s[pr] = c;
                pointer[l] = pr, pointer[r] = pl;
                l ++; r --;
            }
        }
    }

    void decrease_base() {
        auto st = s+1;
        int idx_N = N-1;
        while (true) {
            #ifdef SHOW
            puts(st);
            #endif

            int i = N;
            r[i] += 1;
            if (r[i] < N) {
                char c = st[idx_N];
                idx_N -= 1;
                st[idx_N+1] = st[idx_N];
                st[idx_N] = c;
                continue;
            }
            while (r[i] == i) {
                r[i] = 0;
                r[--i] += 1;
            }
            if (i == 0) break;
            int j = 0;
            char c = 'a'+i-1;
            while (st[j] != c) j++;
            c = st[j], st[j] = st[j-1], st[j-1] = c;
            int t = N-i;
            for (j = 0; j < t; j++) {
                st[N+j] = st[t-1-j];
            }
            if (t < 2) st += t;
            else {
                memmove(s, st+t, N*sizeof(char));
                st = s;
            }
            st[N] = 0;
            idx_N = N-1;
        }
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

    void new_recursive() {
        if (lb == 0) {
            #ifdef SHOW
            puts(s+1);
            #endif
            return;
        }
        for (int i = 0; i < lb; i++) {
            s[cnt++] = s1[i];
            std::swap(s1[i], s1[--lb]);
            new_recursive();
            std::swap(s1[i], s1[lb++]);
            cnt--;
        }
    }

    void increase_base_recursive() {
        for (int i = N; i > 0; i--) {
            if (r[i] != 0) continue;
            r[i] = 1;

            #ifdef SHOW
            s[i] = 'a' + N - cnt++;
            #else
            s[cnt++] = i;
            #endif

            if (cnt == N+1) {
                #ifdef SHOW
                puts(s+1);
                #endif
            } else {
                increase_base_recursive();
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
            // std::reverse(s+i+1, s+N+1);
            auto l = s+i+1, r = s+N;
            while (l < r)
                c = *l, *l = *r, *r = c, l++, r--;
        }
    }
} perm;

int main() {
    int n;
    std::cin >> n;

    perm.generate(n);
    return 0;
}