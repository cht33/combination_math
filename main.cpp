#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <ctime>

// #define SHOW

struct Permutation {
    const static int MAXN = 1000;
    int N;
    int mediation[MAXN]; // 中介数
    char s[2*MAXN]; // 构造的排列
    char* st;
    int next[MAXN]; // 递增和递减中，按定义用中介数生成排列用的数组
    int cnt; // 递归算法和新递归算法中用来标记递归层数
    int mark[MAXN]; // 递归算法中，标记特定位已经被使用过
    int stack_arr[MAXN]; // 基于堆的算法中，迭代模拟递归用的数组
    int boundary; // 新递归算法中，用来维护可用集的边界
    char useable_chars[2*MAXN]; // 新递归算法中，可用集数组

    void init() {
        memset(s, 0, 2*MAXN*sizeof(char));
        memset(mediation, 0, MAXN*sizeof(int));
        memset(stack_arr, 0, MAXN*sizeof(int));
        for (int i = 1; i <= N; i++) {
            s[i] = 'a' + i - 1;
            useable_chars[i] = 'a' + i - 1;
        }
        s[0] = 0;
        cnt = 1;
        boundary = N;
        st = s+1;
    }

    void generate(int n) {
        N = n;
        auto start = clock();

        init();
        start = clock();
        next_permutation();
        printf("STL next_permutation: %.2lfms\n", (double)(clock() - start)*1000/CLOCKS_PER_SEC);

        init();
        start = clock();
        recursive();
        printf("recursive: %.2lfms\n", (double)(clock() - start)*1000/CLOCKS_PER_SEC);

        init();
        start = clock();
        increase_base();
        printf("increase_base: %.2lfms\n", (double)(clock() - start)*1000/CLOCKS_PER_SEC);

        init();
        start = clock();
        optimized_increase_base();
        printf("optimized_increase_base: %.2lfms\n", (double)(clock() - start)*1000/CLOCKS_PER_SEC);

        init();
        start = clock();
        decrease_base();
        printf("decrease_base: %.2lfms\n", (double)(clock() - start)*1000/CLOCKS_PER_SEC);

        init();
        start = clock();
        optimized_decrease_base();
        printf("optimized_decrease_base: %.2lfms\n", (double)(clock() - start)*1000/CLOCKS_PER_SEC);

        init();
        start = clock();
        neighbour_exchange();
        printf("neighbour_exchange: %.2lfms\n", (double)(clock() - start)*1000/CLOCKS_PER_SEC);

        init();
        start = clock();
        optimized_neighbour_exchange();
        printf("optimized_neighbour_exchange: %.2lfms\n", (double)(clock() - start)*1000/CLOCKS_PER_SEC);

        init();
        start = clock();
        dictionary();
        printf("dictionary: %.2lfms\n", (double)(clock() - start)*1000/CLOCKS_PER_SEC);

        init();
        start = clock();
        heap();
        printf("Heap's algorithm: %.2lfms\n", (double)(clock() - start)*1000/CLOCKS_PER_SEC);

        init();
        start = clock();
        new_recursive();
        printf("new_recursive: %.2lfms\n", (double)(clock() - start)*1000/CLOCKS_PER_SEC);
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
            if (mark[i] != 0) continue;
            mark[i] = 1;
            s[cnt++] = 'a' + i - 1;

            if (cnt == N+1) {
                #ifdef SHOW
                puts(s+1);
                #endif
            } else {
                recursive();
            }
            mark[i] = 0;
            cnt--;
        }
    }

    void increase_base() {
        while(true){
            
            // 初始化链表结构
            for(int i = 1;i <= N + 1;i ++)next[i] = i - 1;

            // 按照定义把中介数转为对应的排列
            for(int i = N;i >= 2;i --){
                int emptycnt = mediation[i];
                int preindex = N + 1;
                int index = next[N + 1];
                while(emptycnt){
                    preindex = index;
                    index = next[index];
                    emptycnt --;
                }
                s[index] = 'a' + i - 1;
                next[preindex] = next[index];
            }
            s[next[N + 1]] = 'a';

            #ifdef SHOW
            puts(s+1);
            #endif

            // 递增进制数加一
            int i = 2;
            mediation[i] ++;
            while(mediation[i] >= i){
                mediation[i] -= i;
                mediation[++ i] ++;
            }
            if(i == N + 1)break;
        }
    }

    void optimized_increase_base() {
        
        // 初始化位置数组，pointer[x]表示x当前在排列中的位置
        int pointer[MAXN];
        for(int i = 1;i <= N;i ++){
            pointer[i] = i;
        }
        while(true) {
            
            #ifdef SHOW
            puts(s+1);
            #endif

            // 递增进制数加一
            int i = 2;
            mediation[i] ++;
            while(mediation[i] >= i){
                mediation[i] -= i;
                mediation[++ i] ++;
            }
            if(i == N + 1)break;

            // 将最大的k在1-k的子排列中前移一位
            for(int j = 1;j < i; j ++) {
                int pj = pointer[j], pi = pointer[i];
                if (pj < pi) {
                    char c = s[pi]; s[pi] = s[pj], s[pj] = c;
                    pointer[i] = pj, pointer[j] = pi;
                    break;
                }
            }

            // 翻转1-(k-1)，进位前他们必然是逆序
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

        while(true){
            
            // 初始化链表结构
            for(int i = 1;i <= N + 1;i ++)next[i] = i - 1;

            // 按照定义把中介数转为对应的排列
            for(int i = N;i >= 2;i --){
                int emptycnt = mediation[i];
                int preindex = N + 1;
                int index = next[N + 1];
                while(emptycnt){
                    preindex = index;
                    index = next[index];
                    emptycnt --;
                }
                s[index] = 'a' + i - 1;
                next[preindex] = next[index];
            }
            s[next[N + 1]] = 'a';
            
            #ifdef SHOW
            puts(s + 1);
            #endif

            // 递减进制数加一
            int i = N;
            mediation[i] ++;
            while (mediation[i] == i) {
                mediation[i] = 0;
                mediation[-- i] += 1;
            }
            if (i == 0) break;
        }

    }

    void optimized_decrease_base() {
        auto st = s+1;
        int idx_N = N-1;
        while (true) {
            
            #ifdef SHOW
            puts(st);
            #endif

            // 递减进制数加一(包含最低位的快速计算)
            int i = N;
            mediation[i] += 1;
            if (mediation[i] < N) {
                char c = st[idx_N];
                idx_N -= 1;
                st[idx_N+1] = st[idx_N];
                st[idx_N] = c;
                continue;
            }
            while (mediation[i] == i) {
                mediation[i] = 0;
                mediation[-- i] += 1;
            }
            if (i == 0) break;

            // 将最小的k在1-k的子排列中前移一位
            int j = 0;
            char c = 'a'+i-1;
            while (st[j] != c) j++;
            c = st[j], st[j] = st[j-1], st[j-1] = c;
            
            // 将位于高位的逆序n,n-1,..,n-k+1移动到低位并翻转
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
        while (true) {
            
            #ifdef SHOW
            puts(s+1);
            #endif

            // 递减进制数加一
            int i = N;
            mediation[i] += 1;
            while (mediation[i] == i) {
                mediation[i] = 0;
                mediation[--i] += 1;
            }
            if (i == 0) break;

            memset(s, 0, 2*MAXN*sizeof(char));
            
            // 按照定义处理大于2的位
            for(int i = N;i >= 3;i --){
                // 判断当前位的方向
                int is_right = (i & 1) ? (mediation[i - 1] & 1) : ((mediation[i - 1] + mediation[i - 2]) & 1);
                // 在方向的指导下，数空位插入
                int emptycnt = mediation[i];
                int index = is_right ? 1 : N;
                int delta = is_right ? 1 : -1;
                while(emptycnt || s[index] != 0){
                    if(s[index] == 0){
                        emptycnt --;
                    }
                    index += delta;
                }
                s[index] = 'a' + i - 1;
            }

            // 单独处理2的情况，2的方向一定向左
            int emptycnt = mediation[2];
            int index = N;
            while(emptycnt || s[index] != 0){
                if(s[index] == 0){
                    emptycnt --;
                }
                index --;
            }
            s[index] = 'b';

            // 将1填在最后一个空位
            index = N;
            while(true){
                if(s[index] == 0){
                    s[index] = 'a';
                    break;
                }
                index --;
            }
        }
    }

    void optimized_neighbour_exchange() {
        int idx_N = N, t_N = -1;
        while (true) {
            #ifdef SHOW
            puts(s+1);
            #endif

            int i = N;
            mediation[i] += 1;
            if (mediation[i] < N) {
                char c = s[idx_N];
                idx_N += t_N;
                s[idx_N-t_N] = s[idx_N];
                s[idx_N] = c;
                continue;
            }
            while (mediation[i] == i) {
                mediation[i] = 0;
                mediation[--i] += 1;
            }
            if (i == 0) break;
            int j = 1;
            char c = 'a'+i-1;
            while (s[j] != c) j++;
            // 只需考虑最后一位的运算结果，1为奇，0为偶
            int t = (mediation[i-1] ^ (~i & mediation[i-2])) & 1;
            t = (t << 1) - 1;
            c = s[j+t], s[j+t] = s[j], s[j] = c;
            t_N = (mediation[N-1] ^ (~N & mediation[N-2])) & 1;
            t_N = (t_N << 1) - 1;
        }
    }

    void dictionary() {
        while (true) {
            
            #ifdef SHOW
            puts(s+1);
            #endif

            // 首先找到第一个高位数值小于低位数值的点
            int i = N-1;
            while (s[i+1] < s[i]) i--;
            if (i == 0) break;
            
            // 再找到尾部序列中，大于这个高位数值的最小值
            int j = N;
            while (s[j] < s[i]) j--;
            
            // 交换二者
            char c = s[j];
            s[j] = s[i], s[i] = c;
            
            // 将剩余的序列翻转
            // std::reverse(s+i+1, s+N+1);
            auto l = s+i+1, r = s+N;
            while (l < r)
                c = *l, *l = *r, *r = c, l++, r--;
        }
    }

    void heap() {
        
        #ifdef SHOW
        puts(st);
        #endif
        
        int i = 1;
        while (i < N) {
            if (stack_arr[i] < i) {
                int t = (i & 1) ? stack_arr[i] : 0;
                char c = st[t]; st[t] = st[i], st[i] = c;
                
                #ifdef SHOW
                puts(st);
                #endif
                
                stack_arr[i]++, i = 1;
            } else {
                stack_arr[i++] = 0;
            }
        }
    }

    void new_recursive() {
        if (boundary == 0) {
            #ifdef SHOW
            puts(s+1);
            #endif
            return;
        }
        // 每层迭代只能在可用集中探索
        for (int i = 1; i <= boundary; i++) {
            // 使用了可用集第i位元素
            s[cnt++] = useable_chars[i];
            // 维护可用集，可用集大小减一，第i位元素出集
            std::swap(useable_chars[i], useable_chars[boundary--]);
            new_recursive();
            // 维护可用集，可用集大小加一，第i位元素入集
            std::swap(useable_chars[i], useable_chars[++boundary]);
            cnt--;
        }
    }

    // void increase_base_recursive() {
    //     for (int i = N; i > 0; i--) {
    //         if (mediation[i] != 0) continue;
    //         mediation[i] = 1;

    //         #ifdef SHOW
    //         s[i] = 'a' + N - cnt++;
    //         #else
    //         s[cnt++] = i;
    //         #endif

    //         if (cnt == N+1) {
    //             #ifdef SHOW
    //             puts(s+1);
    //             #endif
    //         } else {
    //             increase_base_recursive();
    //         }
    //         mediation[i] = 0;
    //         cnt--;
    //     }
    // }
} perm;

int main(int argc, char** argv) {
    if(argc != 2){
        std::cout << "Usage:" << std::endl;
        std::cout << "./main lengh(int)" << std::endl;
    }
    int n = atoi(argv[1]);
    perm.generate(n);
    return 0;
}