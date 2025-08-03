// fractional knapsack

#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define nl endl

int frac(vector<int> &profit, vector<int> &eachItemsWeight, int weight)
{
    // pair
    vector<pair<int, int>> items;
    for (int i = 0; i < profit.size(); i++)
    {
        items.push_back({profit[i], eachItemsWeight[i]});
    }

    // ratios
    vector<pair<double, int>> ratios;
    for (int i = 0; i < profit.size(); i++)
    {
        double itemsRatio = (double)items[i].first / items[i].second;
        ratios.push_back({itemsRatio, i});
    }

    // des sort
    sort(ratios.rbegin(), ratios.rend());

    int currentWt = 0;
    double totalProfit = 0.0;

    for (int i = 0; i < profit.size(); i++)
    {
        int currentItemIndex = ratios[i].second;
        int itemsProfit = items[currentItemIndex].first;
        int itemsWt = items[currentItemIndex].second;

        if (currentWt + itemsWt <= weight)
        {
            currentWt += itemsWt;
            totalProfit += itemsProfit;
        }

        else
        {
            int remainWt = weight - currentWt;
            double remainProfit = (double)itemsProfit * remainWt / itemsWt;

            totalProfit += remainProfit;
            break;
        }
    }

    return totalProfit;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int weight = 10;
    vector<int> profit = {40, 30, 18, 50};
    vector<int> eachItemsWeight = {5, 6, 9, 4};

    cout << "Maximum Profit: " << frac(profit, eachItemsWeight, weight) << nl;

    return 0;
}