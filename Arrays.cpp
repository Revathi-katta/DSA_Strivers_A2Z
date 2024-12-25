// 1752. Check if Array Is Sorted and Rotated
// Input: nums = [3,4,5,1,2]
// Output: true
// Explanation: [1,2,3,4,5] is the original sorted array.
// You can rotate the array by x = 3 positions to begin on the the element of value 3: [3,4,5,1,2].
class Solution {
public:
    bool check(vector<int>& nums) {
        int c=0;
        for(int i=0; i<nums.size()-1; i++){
            if(nums[i]>nums[i+1]){
                c++;
                }    
        }
        if(nums[0]<nums[nums.size()-1]){c++;} //tried smtg like if(c>1 || nums[0]<nums[nums.size()-1])return false, but the best approach is this.
        if(c>1){return false;}
        return true;
    }
};

// 26. Remove Duplicates from Sorted Array
// Input: nums = [1,1,2]
// Output: 2, nums = [1,2,_]
// Explanation: Your function should return k = 2, with the first two elements of nums being 1 and 2 respectively.
// It does not matter what you leave beyond the returned k (hence they are underscores).
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int j=0;
        for(int i=0; i<nums.size(); i++){
            if(nums[i]!=nums[j]){
                j++;
                nums[j]=nums[i];  
            }
        }
    return j+1;
    }
};

// 189. Rotate array
// Given an integer array nums, rotate the array to the right by k steps, where k is non-negative.
// **check if the rotation is right or left (in this q its right, which also implies n-right  left rotations can be done)
// Input: nums = [1,2,3,4,5,6,7], k = 3
// Output: [5,6,7,1,2,3,4]
// Explanation:
// rotate 1 steps to the right: [7,1,2,3,4,5,6]
// rotate 2 steps to the right: [6,7,1,2,3,4,5]
// rotate 3 steps to the right: [5,6,7,1,2,3,4]
class Solution {
public:
    //writing reverse func in case it is not allowed to use stl
    // void reverse(vector<int> &nums, int start, int end){
    //     while(start<end){
    //         int temp=nums[start];
    //         nums[start]=nums[end];
    //         nums[end]=temp;
    //         start++;
    //         end--;
    //     }
    // }
    void rotate(vector<int>& nums, int k) {
        k=k%nums.size();
        reverse(nums.begin(), nums.end()-k); 
        // using reverse from stl make sure to #include<bits/stdc++.h> using namespace std; if it didnt work.
        // if not using stl, reverse(nums, 0, n-k-1)
        reverse(nums.end()-k, nums.end()); //reverse(nums, n-k, n-1)
        reverse(nums.begin(), nums.end()); //reverse(nums, 0, n-1)
        //return nums; not req since its void type
    }
    
};

// 283.Move Zeroes
// Input: nums = [0,1,0,3,12]
// Output: [1,3,12,0,0]
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int j=0;
        int n=nums.size();
        while(nums[j]!=0){j++;}  
        // make sure you place j pointer at the first zero and iterate i from next index after 'j'
        for(int i=j+1; i<n; i++){
            if(nums[i]!=0){
                nums[j]=nums[i];
                nums[i]=0;
                j++;
            }
        }
        
    }
};

// 268. Missing Number
// Input: nums = [3,0,1]
// Output: 2
// Explanation: n = 3 since there are 3 numbers, so all numbers are in the range [0,3]. 2 is the missing number in the range since it does not appear in nums.
for(auto it : nums){
            //instead of auto u can also for(vector<int> :: iterator it=nums.begin(); it=nums.end(); i++)
            ans=ans^it;
        }
for(int i=0; i<nums.size()+1; i++){
            ans=ans^i;
        }
return ans;


// 485.Max Consecutive Ones
// Input: nums = [1,1,0,1,1,1]
// Output: 3
// Explanation: The first two digits or the last three digits are consecutive 1s. The maximum number of consecutive 1s is 3.
class Solution {
public:
    int findMaxConsecutiveOnes(vector<int>& nums) {
        int l=0, r=0, maxlen=0;
        while(r<nums.size()){
            if(nums[r]==0){
                l=r+1;
            }
            else{maxlen=max(r-l+1, maxlen);}
            r++;
        }
        return maxlen;
        
    }
};

// 1.Two Sum
// Input: nums = [2,7,11,15], target = 9
// Output: [0,1]
// Explanation: Because nums[0] + nums[1] == 9, we return [0, 1].
// You may assume that each input would have exactly one solution, and you may not use the same element twice.
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> ans;
        map<long long, int> mpp;
        for(int i=0; i<nums.size(); i++){
            if(mpp.find(target-nums[i])!=mpp.end()){
                ans.push_back(i); ///imp to write i instead of map[nums[i]] since nums[i] is add after if statement!!
                ans.push_back(mpp[target-nums[i]]);
                return ans;
            }
            mpp[nums[i]]=i; //added after if check because we dont want it to connsider itself for ex in this case {3, 2, 4}, target=6, if we add 3 first then checking if 3 is present leads to {0,0} since it takes 3+3=6 !!  
            //so when ever we write if statement which uses *find* in it better to add the update after all the checks.
        }
        return {-1, -1};
    }
};

//Union of two arrays in sorted form
class Solution {
  public:
    // a,b : the arrays
    // Function to return a list containing the union of the two arrays.
    vector<int> findUnion(vector<int> &a, vector<int> &b) {
        int i=0, j=0;
        vector<int> ans;
        while(i<a.size() && j<b.size()){
            if(a[i]<b[j]){
                if(ans.empty()|| ans.back()!=a[i]){ans.push_back(a[i]);}
                i++;
            }
            
            else if(a[i]>b[j]){
                if(ans.empty() || ans.back()!=b[j]){ans.push_back(b[j]);}
                j++;
            }
            else{
                if(ans.empty() || ans.back() != a[i])ans.push_back(a[i]);
                i++;
                j++;
            }
        }
        while(i<a.size()){
                if(ans.empty() || ans.back() != a[i])ans.push_back(a[i]);
                i++;
            }
        while(j<b.size()){
            if(ans.empty() || ans.back()!=b[j])ans.push_back(b[j]);
            j++;
        }
        return ans;
    }
}

//Longest Sub-Array with Sum (contains both positive and negative numbers)
class Solution {
  public:
    int lenOfLongestSubarr(vector<int>& arr, int k) {
        int r=0, maxlen=0; // no left pointer is needed
        map<long long, int> mpp;
        long long sum=0;
        while(r<arr.size()){
            sum+=arr[r];
            if(mpp.find(sum)==mpp.end()){mpp[sum]=r;}
            if(sum==k){maxlen=max(maxlen, r+1);} //r+1
            if(mpp.find(sum-k)!=mpp.end()){maxlen=max(maxlen, r-(mpp[sum-k]));} //r-(mpp[sum-k]
            r++;
        }
        return maxlen;
        // code here
    }
};

