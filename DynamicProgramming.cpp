// [746. Min Cost Climbing Stairs](https://leetcode.com/problems/min-cost-climbing-stairs/)

// Statement  
// Given cost of each step, find the minimum cost to reach the top. You can climb either 1 or 2 steps at a time.

// Approach  
// dp[i] = cost[i] + min(dp[i-1], dp[i-2])  
// Return min(dp[n-1], dp[n-2]) — since you can reach the top from either of the last two steps

// Top-Down  
// int result = min(mincost(cost, dp, step+1), mincost(cost, dp, step+2)) + cost[step];  
// return dp[step] = result;

// Bottom-Up  
// dp[0] = cost[0];  
// dp[1] = cost[1];  
// for (int i = 2; i < n; ++i)  
//     dp[i] = cost[i] + min(dp[i-1], dp[i-2]);  
// return min(dp[n-1], dp[n-2]);

class Solution {
public:
    // int mincost(vector<int> &cost, vector<int> &dp, int step){
    //     if(step>=cost.size()) return 0;
    //     if(dp[step]!=-1) return dp[step];
    //     int mincostHere = cost[step] + min(mincost(cost, dp, step+1), mincost(cost, dp, step+2));
    //     dp[step]=mincostHere;
    //     return dp[step];
    // }
    int minCostClimbingStairs(vector<int>& cost) {
        // vector<int> dp(cost.size(), -1);
        // // return min(mincost(cost, dp, 0), mincost(cost, dp, 1));
        // dp[0]=cost[0];
        // dp[1]=min(cost[0]+cost[1], cost[1]+0); //direct step 1 or step0+step1(actually this is of no use since adding a postive will never be min)
        // for(int i=2; i<cost.size(); i++){
        //     dp[i]=cost[i] + min (dp[i-1], dp[i-2]);
        // }
        // return min(dp[cost.size()-1], dp[cost.size()-2]) ; ///****
        int prev2=cost[0], prev1=cost[1], curr=-1;
        for(int i=2; i<cost.size(); i++){
            curr = cost[i] + min(prev1, prev2);
            prev2 = prev1;
            prev1 = curr;
        }
        return min(prev1, prev2);
    }
};

// [64. Minimum Path Sum](https://leetcode.com/problems/minimum-path-sum/)

// Statement  
// Given an m x n grid filled with non-negative numbers, find a path from top-left to bottom-right with minimum sum, only moving right or down.

// Approach  
// dp[i][j] = grid[i][j] + min(dp[i-1][j], dp[i][j-1])  
// Choose min path from top or left and add current grid cost.

// Top-Down  
// int result = min(pathSum(i+1, j, grid, memo), pathSum(i, j+1, grid, memo)) + grid[i][j];  
// return memo[i][j] = result;

// Bottom-Up  
// dp[0][0] = grid[0][0];  
// for each cell (i,j):  
//     dp[i][j] = grid[i][j] + min(dp[i-1][j], dp[i][j-1])  
// return dp[n-1][m-1]

class Solution {
public:
    // int minpath(vector<vector<int>>& grid, int r, int c, vector<vector<int>> &dp){
    //     int n=grid.size(), m=grid[0].size();
    //     if(r==n-1 && c==m-1)return grid[r][c];
    //     if(r==n || c==m)return INT_MAX; // cant take 201 as the sum before can be so small and adding this would give us min path as well
    //     if(dp[r][c]!=-1) return dp[r][c];
    //     return dp[r][c] = grid[r][c] + min(minpath(grid, r+1, c, dp), minpath(grid, r, c+1, dp));
    // }
    int minPathSum(vector<vector<int>>& grid) {
        int n=grid.size(), m=grid[0].size();
        // vector<vector<int>> dp(n, vector<int> (m, -1));
        // return minpath(grid, 0, 0, dp);

        // dp[0][0]=grid[0][0];
        // int sum=0;
        // for(int j=0; j<m; j++){
        //     sum+=grid[0][j];
        //     dp[0][j]=sum;
        // }
        // for(int i= 1; i<n; i++){
        //     for(int j=0; j<m; j++){
        //         int top = (i-1>=0) ? dp[i-1][j] : INT_MAX;
        //         int left = (j-1>=0) ? dp[i][j-1] : INT_MAX;
        //         dp[i][j] = grid[i][j] + min(top, left);
        //     }
        // }

        vector<int> prev(m, 0);
        for(int i= 0; i<n; i++){
            vector<int> curr(m, 0);
            for(int j=0; j<m; j++){
                if(i==0 && j==0)curr[j]=grid[i][j];
                else{
                    int top = (i-1>=0) ? prev[j] : INT_MAX;
                    int left = (j-1>=0) ? curr[j-1] : INT_MAX;
                    curr[j] = grid[i][j] + min(top,left);
                }
            }
            prev=curr;
        }
        return prev[m-1];
        // return dp[n-1][m-1];
        
    }
};

// [322. Coin Change](https://leetcode.com/problems/coin-change/)

// Statement  
// Given a list of coins and a target amount, return the minimum number of coins needed to make the amount.  
// Return -1 if it's not possible to form the amount.

// Approach  
// Choose the minimum of two choices at every index: take the coin or skip it.  
// If you take the coin, stay on the same index (because you can take it again).  
// If you skip, move to next index.  
// Try every combination and store the result of subproblems.

// Top-Down  
// long result = min(1 + mincoins(coins, amount - coins[ind], ind),  
//                   mincoins(coins, amount, ind + 1));  
// return memo[ind][amount] = result;

// Bottom-Up  
// dp[i][j] = min(  
//      1 + dp[i - coins[j]][j]   // take same coin  
//      dp[i][j-1]                // don't take this coin  
// )  
// return dp[amount][n-1];

class Solution {
public:
    // return min((amount/coins[ind])+mincoins(coins, amount%coins[ind], ind+1), mincoins(coins, amount, ind+1)); //this is greedy since taking max no.of coins of one kind is not always correct we might take only some coins of kind less than max no.of coins of that kind possible!!
    
    // ind only in first case since we can choose to take this coin again or move to next; if we take ind+1 it becomes not taking this again and always moving to next

    // long mincoins(vector<int>& coins, int amount, int ind, vector<vector<long>> &dp) {
    //     if (amount == 0) return 0;
    //     if (amount < 0 || ind == coins.size()) return INT_MAX;
    //     if(dp[ind][amount]!=-1)return dp[ind][amount];
    //     return dp[ind][amount]= min(1 + mincoins(coins, amount - coins[ind], ind, dp),  // take
    //                mincoins(coins, amount, ind + 1, dp));              // not take
    // }

    int coinChange(vector<int>& coins, int amount) {
        int n= coins.size(), m=amount;
        vector<vector<long>> dp(m+1, vector<long> (n, INT_MAX));
        // long res = mincoins(coins, amount, 0, dp);
        // return (res >= INT_MAX ) ? -1 : (int)res;  // 

        for(int i=0; i<m+1; i++){
            for(int j=0; j<n; j++){
                if(i==0)dp[0][j]=0; //no.of coins required to make total=0 is zero;
                else{
                    int take = (i-coins[j]>=0 && dp[i-coins[j]][j]!=INT_MAX) ? 1+dp[i-coins[j]][j] : INT_MAX;
                    int not_take = (j-1>=0) ? dp[i][j-1] : INT_MAX;
                    dp[i][j] = min(take, not_take);
                }
            }
        }
        return (dp[m][n-1]!=INT_MAX) ? dp[m][n-1]:-1;
    }
};

// [931. Minimum Falling Path Sum](https://leetcode.com/problems/minimum-falling-path-sum/)

// Statement  
// Given a square matrix, find the minimum falling path sum from the top to the bottom.
// You may move to the element directly below or diagonally left/right in the next row.

// Approach  
// At each cell, choose the minimum of the three possible cells from the row above: directly above, top-left, or top-right.
// Add the current cell’s value to the min of those paths.

// Top-Down  
// int result = matrix[row][col] + min(  
//     minpath(row+1, col),  
//     minpath(row+1, col-1),  
//     minpath(row+1, col+1)  
// );  
// return memo[row][col] = result;

// Bottom-Up  
// dp[i][j] = matrix[i][j] + min(dp[i-1][j], dp[i-1][j-1], dp[i-1][j+1])  
// return min(dp[n-1][0]...dp[n-1][n-1]);

class Solution {
    // int minpath(vector<vector<int>>& matrix, int row, int col, vector<vector<int>> & dp){
    //     int n = matrix.size();
    //     if(row==n)return 0;
    //     if(dp[row][col]!=-1)return dp[row][col];
    //     int left = (col-1>=0) ?  minpath(matrix, row+1, col-1, dp) : INT_MAX;
    //     int right = (col+1<n) ? minpath(matrix, row+1, col+1, dp) : INT_MAX;
    //     return dp[row][col] = matrix[row][col] + min(left, min(minpath(matrix, row+1, col, dp), right));

    // }
public:
    int minFallingPathSum(vector<vector<int>>& matrix) {

        // int mini = INT_MAX;
        // for(int i=0; i<n; i++){   
        //     mini = min(mini, minpath(matrix, 0, i, dp));
        // }
        // return mini;     

        int n = matrix.size();
        vector<vector<int>> dp(n, vector<int>(n, -1));
        for(int i=0; i<n; i++){
            dp[0][i]=matrix[0][i];
        }
        for(int i=1; i<n; i++){
            for(int j=0; j<n; j++){
                int left = (j-1>=0) ? dp[i-1][j-1] : INT_MAX;
                int right = (j+1<n) ? dp[i-1][j+1] : INT_MAX;
                dp[i][j] = matrix[i][j] + min(left, min(dp[i-1][j], right));
            }
        }
        int ans=INT_MAX;
        for(int i=0; i<n; i++){
            ans = min (ans, dp[n-1][i]);
        }
        return ans;

    }
};

// [983. Minimum Cost For Tickets](https://leetcode.com/problems/minimum-cost-for-tickets/)

// Statement  
// You are given a list of travel days and the cost of 1-day, 7-day, and 30-day passes.
// Find the minimum cost to cover all travel days.

// Approach  
// At each travel day, take the minimum cost of buying a 1-day, 7-day, or 30-day pass and move to the next uncovered day accordingly.

// Top-Down  
// result = min(
//     cost[0] + f(day+1),
//     cost[1] + f(day+7),
//     cost[2] + f(day+30)
// );
// return memo[day] = result;

// Bottom-Up  
// for (int day = 1; day <= days.back(); ++day) {
//     if (day not in travel days) dp[day] = dp[day - 1];
//     else dp[day] = min({
//         dp[day - 1] + cost[0],
//         dp[day - 7] + cost[1],
//         dp[day - 30] + cost[2]
//     });
// }
// return dp[lastDay];

class Solution {
public:
    // int mincost(vector<int>& days, vector<int>& costs, int start, vector<int> &dp){
    //     if(start>days.back())return 0;
    //     if(dp[start]!=INT_MAX) return dp[start];
    //     int actualday=0;
    //     for(int i=0; i<days.size(); i++){
    //         if(days[i]>=start){actualday = days[i]; break;}
    //     }
        
    //     return dp[start] = min(costs[0]+mincost(days, costs, actualday+1, dp), min(costs[1]+mincost(days, costs, actualday+7, dp), costs[2]+mincost(days, costs, actualday+30, dp)));

    // }
    int mincostTickets(vector<int>& days, vector<int>& costs) {
        vector<int> dp(days.back()+1, 0); 
        // return mincost(days, costs, days[0], dp);

        int i=0;
        for(int day=1; day<=days.back(); day++){
            if(day<days[i])dp[day]=dp[day-1];
            else{
                i++;
                dp[day] = min({
                    dp[max(0, day-1)]+costs[0],
                    dp[max(0, day-7)]+costs[1],
                    dp[max(0, day-30)]+costs[2]
                });
            }
            
        }
    return dp[days.back()];
    }
};

