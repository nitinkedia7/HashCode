#include <bits/stdc++.h>
using namespace std;

int main()
{
    int b, l, D;
    cin >> b >> l >> D;
    vector<int> books(b);
    for (int i = 0; i < b; i++)
    {
        cin >> books[i];
    }
    vector<vector<int>> lib(l);
    vector<int> signUp(l);
    vector<int> rate(l);
    for (int i = 0; i < l; i++)
    {
        int n;
        cin >> n;
        cin >> signUp[i] >> rate[i];
        for (int j = 0; j < n; j++)
        {
            int id;
            cin >> id;
            lib[i].push_back(id);
        }
    }
    vector<bool> avail(b, true);
    vector<bool> selected(l, false);
    vector<int> ans;
    vector<vector<int>> ansBooks;
    int d = 0;
    while (d < D)
    {
        pair<double, int> maxScore = {INT_MAX, INT_MAX};
        // int maxScore = INT_MAX;
        // double maxScore = 0;
        int selectedLib = -1;
        for (int i = 0; i < l; i++)
        {
            if (selected[i])
                continue;
            int numBooks = (D - (d + signUp[i])) * rate[i];
            int curScore = 0;
            int selectedBooks = 0;
            for (int j = 0; j < lib[i].size(); j++)
            {
                int id = lib[i][j];
                if (!avail[id])
                    continue;
                if (numBooks > 0)
                {
                    curScore += books[id];
                    numBooks--;
                    selectedBooks++;
                }
                else
                    break;
            }
            double days = signUp[i] + ((double)selectedBooks) / rate[i];
            double currate = curScore / days;
            pair<double, int> cs = {-1 * currate - (curScore / 6000.0), 0};
            // int cs = signUp[i];
            if (cs < maxScore)
            {
                maxScore = cs;
                selectedLib = i;
            }
        }
        if (selectedLib == -1)
            break;
        ans.push_back(selectedLib);
        vector<int> usedBooks;
        int numBooks = (D - (d + signUp[selectedLib])) * rate[selectedLib];
        for (int i = 0; i < lib[selectedLib].size(); i++)
        {
            int id = lib[selectedLib][i];
            if (!avail[id])
                continue;
            if (numBooks > 0)
            {
                usedBooks.push_back(id);
                avail[id] = false;
                numBooks--;
            }
            else
                break;
        }
        ansBooks.push_back(usedBooks);
        selected[selectedLib] = true;
        d += signUp[selectedLib];
    }
    int totalScore = 0;
    for (int i = 0; i < b; i++)
    {
        if (!avail[i])
            totalScore += books[i];
    }
    cout << totalScore << endl;
    cout << ans.size() << endl;
    for (int i = 0; i < ans.size(); i++)
    {
        cout << ans[i] << " " << ansBooks[i].size() << endl;
        for (auto x : ansBooks[i])
        {
            cout << x << " ";
        }
        cout << endl;
    }
    return 0;
}