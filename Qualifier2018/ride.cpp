#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 1000000007;
int ITER = 1000;
int B;

struct Ride {
    int a, b, x, y, s, f, i;
    // TreeNode(int x) : val(x), left(NULL), right(NULL) {}
    Ride(int a, int b, int x, int y, int s, int f, int i) : a(a), b(b), x(x), y(y), s(s), f(f), i(i) {}
};

bool comp(Ride *r1, Ride *r2) {
    int t1 = r1->s + abs(r1->x - r1->a) + abs(r1->y - r1->b);
    int t2 = r2->s + abs(r2->x - r2->a) + abs(r2->y - r2->b);
    return t1 < t2;
}

bool comp2(Ride *r1, Ride *r2) {
    int t1 = r1->s + r1->f + abs(r1->x - r1->a) + abs(r1->y - r1->b);
    int t2 = r2->s + r2->f + abs(r2->x - r2->a) + abs(r2->y - r2->b);
    return t1 < t2;
}

struct Car {
    int a, b, t;
    vector<int> v;
    Car(int a, int b, int t) : a(a), b(b), t(t) {}
};

Ride *scan(int i) {
    int a, b, x, y, s, f;
    cin >> a >> b >> x >> y >> s >> f;
    return new Ride(a, b, x, y, s, f, i);
} 

bool isFeasible(Ride *r, Car *c) {
    int pd = abs(c->a - r->a) + abs(c->b - r->b);
    int jd = abs(r->x - r->a) + abs(r->y - r->b);
    int dt = max(c->t + pd, r->s) + jd;
    return dt <= r->f;  // CHECK
}

void update(Ride *r, Car *c) {
    int pd = abs(c->a - r->a) + abs(c->b - r->b);
    int jd = abs(r->x - r->a) + abs(r->y - r->b);
    int dt = max(c->t + pd, r->s) + jd;
    c->t = dt;
}

pair<int,int> getProfit(Ride *r, Car *c) {
    int p = 0;
    int pd = abs(c->a - r->a) + abs(c->b - r->b);
    int jd = abs(r->x - r->a) + abs(r->y - r->b);
    int pr = jd + (c->t + pd <= r->s ? B : 0);
    int z = max(r->s, c->t + pd) + jd;
    return {-z, pr};
    // return jd + (c->t + pd <= r->s ? B : 0) - pd;
}

void sherlock(int tt) {
    int r, c, f, n, b, t;
    cin >> r >> c >> f >> n >> b >> t;
    B = b;
    vector<Ride*> rides(n);
    for (int i = 0; i< n; i++) {
        rides[i] = scan(i);
    }
    vector<Car*> fleet(f);
    for (int i = 0; i < f; i++) {
        fleet[i] = new Car(0, 0, 0);
    } 
    int finalScore = 0;
    // sort(rides.begin(), rides.end(), comp);
    for (int k = 0; k < ITER; k++) {
        if (k == 0) sort(rides.begin(), rides.end(), comp);
        else if (k == 1) sort(rides.begin(), rides.end(), comp2);
        else random_shuffle(rides.begin(), rides.end());
        int score = 0;
        for (int i = 0; i < f; i++) {
            fleet[i]->a = 0;
            fleet[i]->b = 0;
            fleet[i]->t = 0;
            fleet[i]->v.clear();
        }
        for (int i = 0; i < n; i++) {
            int p = INT_MIN;
            int wj = -1;
            int wp = 0;
            for (int j = 0; j < f; j++) {
                // feasible
                // cout << "kuch tp hua" << endl;
                if (!isFeasible(rides[i], fleet[j])) continue;
                // profit: start bonus 
                pair<int,int> z = getProfit(rides[i], fleet[j]);
                if (z.first > p) {
                    p = z.first;
                    wj = j;
                    wp = z.second;
                }
            }
            if (wp > 0) {
                score += wp;
                update(rides[i], fleet[wj]);
                fleet[wj]->a = rides[i]->x;
                fleet[wj]->b = rides[i]->y;
                fleet[wj]->v.push_back(i);
            }
        }
        finalScore = max(finalScore, score);
    }
    cout << finalScore << endl;
    // for (int i = 0; i < f; i++) {
    //     cout << fleet[i]->v.size() << " ";
    //     for (auto x : fleet[i]->v) {
    //         cout << x << " ";
    //     }
    //     cout << endl;
    // }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int tt = 1;
    for (int t = 1; t <= tt; t++) sherlock(t);
    return 0;
}