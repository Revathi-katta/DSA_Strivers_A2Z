// The problems that can be solved using this tool generally satisfy the following criteria :

// You are explicitly asked to return a collection of all answers.
// You are concerned with what the actual solutions are rather than say the most optimum value of some parameter. (if it were the latter it’s most likely DP or greedy).


// 78. Subsets  
// Approach: Backtracking — include/exclude each element recursively to generate all subsets (powerset)  
// Input: nums = [1,2,3]  
// Output: [[],[1],[1,2],[1,2,3],[1,3],[2],[2,3],[3]]  
// Time: O(2^n) — each element has two choices  
// Space: O(n) recursion depth + O(2^n) for storing result
class Solution {
public:
    // void backtrack(vector<vector<int>> &powerset, vector<int> &subset, vector<int>&nums, int start){
    //     powerset.push_back(subset);
    //     for(int i=start; i<nums.size(); i++){
    //         subset.push_back(nums[i]);
    //         backtrack(powerset, subset, nums, i+1);
    //         subset.pop_back();
    //     }
    // }
    void backtrack(vector<vector<int>> &powerset, vector<int> &subset, vector<int>&nums, int start){
        if(start==nums.size())powerset.push_back(subset);
        else{
            subset.push_back(nums[start]);
            backtrack(powerset, subset, nums, start+1);
            subset.pop_back();
            backtrack(powerset, subset, nums, start+1);
        }
        
    }
    vector<vector<int>> subsets(vector<int>& nums) {
       vector<vector<int>> powerset;
       vector<int> subset;
       backtrack(powerset, subset, nums, 0);
       return powerset; 
    }
};

// 90. Subsets II  
// Approach: Backtracking with pruning — sort and skip duplicates at the same recursion level  
// Input: nums = [1,2,2]  
// Output: [[],[1],[1,2],[1,2,2],[2],[2,2]]  
// Time: O(2^n)  
// Space: O(n) recursion + O(2^n) for storing result
class Solution {
public:
    void backtrack(vector<vector<int>> &powerset, vector<int> &subset, vector<int>&nums, int start){
        powerset.push_back(subset);
        for(int i=start; i<nums.size(); i++){
            if(i>start && nums[i-1]==nums[i])continue;   ///////
            subset.push_back(nums[i]);
            backtrack(powerset, subset, nums, i+1);
            subset.pop_back();
        }
    }
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
       vector<vector<int>> powerset;
       vector<int> subset;
       sort(nums.begin(), nums.end());     ///////
       backtrack(powerset, subset, nums, 0);
       return powerset;       
    }
};

// 39. Combination Sum  
// Approach: Backtracking — Try all combinations using current element multiple times (don't increment index after pick)  
// Input: candidates = [2,3,6,7], target = 7  
// Output: [[2,2,3],[7]]  
// Time: O(2^t) where t = target (worst-case combinations)  
// Space: O(t) recursion stack depth
class Solution {
public:
    void backtrack(vector<vector<int>> &powerset, vector<int> &subset, vector<int>&candidates, int start, int target){
        if(target==0)powerset.push_back(subset);
        else if(target<0)return;
        else{
            for(int i=start; i<candidates.size(); i++){
                subset.push_back(candidates[i]);
                backtrack(powerset, subset, candidates, i, target-candidates[i]);//since we want to reuse nums "i is not incremented" and since we added target to subset, "subtract target from subset"
                subset.pop_back();
            }
        }
    }
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
       vector<vector<int>> powerset;
       vector<int> subset;
       backtrack(powerset, subset, candidates, 0, target);
       return powerset;         
    }
};

// 40. Combination Sum II  
// Approach: Backtracking — sort and skip duplicates at same level; no element reuse (i+1)  
// Input: candidates = [10,1,2,7,6,1,5], target = 8  
// Output: [[1,1,6],[1,2,5],[1,7],[2,6]]  
// Time: O(2^n)  
// Space: O(target) recursion + output size
class Solution {
public:
    void backtrack(vector<vector<int>> &powerset, vector<int> &subset, vector<int>&candidates, int start, int target){
        if(target==0)powerset.push_back(subset);
        else if(target<0)return;
        else{
            for(int i=start; i<candidates.size(); i++){
                if(i>start && candidates[i-1]==candidates[i])continue; //help not to reapt the same subset in powerset but not to reapeat a element;
                subset.push_back(candidates[i]);
                backtrack(powerset, subset, candidates, i+1, target-candidates[i]);//since we want donot to reuse nums "i is incremented" and since we added target to subset, "subtract target from subset"
                subset.pop_back();
            }
        }
    }
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
       vector<vector<int>> powerset;
       vector<int> subset;
       sort(candidates.begin(), candidates.end());
       backtrack(powerset, subset, candidates, 0, target);
       return powerset;         
    }
};

// 51. N-Queens  
// Approach: Backtracking — place queens column by column and check diagonals + row on the left  
// Input: n = 4  
// Output: [[".Q..","...Q","Q...","..Q."],["..Q.","Q...","...Q",".Q.."]]  
// Time: O(n!) — placing n queens with backtracking  
// Space: O(n^2) for board and result storage
class Solution {
public:
    bool possiblespot(vector<string> &board, int row, int col){
        int n = board.size();
        for(int k = 1; k <= col; k++){
            if(row - k >= 0 && col - k >= 0 && board[row - k][col - k] == 'Q') return false;
            if(col - k >= 0 && board[row][col - k] == 'Q') return false;
            if(row + k < n && col - k >= 0 && board[row + k][col - k] == 'Q') return false;
        }
        return true;
    }
    void solveboard(vector<vector<string>> &solutions, vector<string> &board, int col, int n){
        if(col==n){solutions.push_back(board);return;}
        for(int row=0; row<n; row++){
            if(possiblespot(board, row, col)){
                board[row][col]='Q';
                solveboard(solutions, board, col+1, n);
                board[row][col]='.';
            }
        }
    }
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> solutions;
        vector<string> board(n, string(n, '.'));
        solveboard(solutions, board, 0, n);
        return solutions;
    }
};

