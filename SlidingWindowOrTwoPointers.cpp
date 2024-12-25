3.Longest Substring without Repeating characters
Input: s = "abcabcbb"
Output: 3
Explanation: The answer is "abc", with the length of 3.
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        vector<int> hash(256, -1); // Hash table for ASCII characters
        int l = 0, r = 0, maxlen = 0; // Left and right pointers, and max length
        
        while (r < s.size()) {
            // If the character was seen before and is within the current window
            if (hash[s[r]] >= l) {
                l = hash[s[r]] + 1; // Move the left pointer
            }
            hash[s[r]] = r; // Update the last seen index of the current character
            maxlen = max(maxlen, r - l + 1); // Update max length
            r++; // Move the right pointer
        }
        
        return maxlen;
    }
};

// 1004.Max Consecutive Ones III
// Input: nums = [1,1,1,0,0,0,1,1,1,1,0], k = 2
// Output: 6
// Explanation: [1,1,1,0,0,1,1,1,1,1,1]
// Bolded numbers were flipped from 0 to 1. The longest subarray is underlined.
//***we donot have to flip but instead understand that 2 nums which are not 1 are also allowed in maxlen
class Solution {
public:
    int longestOnes(vector<int>& nums, int k) {
        int l=0, r=0, zeroes=0, maxlen=0;
        while(r<nums.size()){
            if(nums[r]==0){zeroes++;}
            if(zeroes>k){
                if(nums[l]==0){
                    zeroes--;
                }
                l++;
            }
            
            if (zeroes<=k){maxlen=max(maxlen, r-l+1);}
            r++;
        }
    return maxlen;   
    }
};

	
// 424.longest repeating character replacement
// Input: s = "AABABBA", k = 1
// Output: 4
// Explanation: Replace the one 'A' in the middle with 'B' and form "AABBBBA".
// The substring "BBBB" has the longest repeating letters, which is 4.
// There may exists other ways to achieve this answer too.
class Solution {
public:
    int characterReplacement(string s, int k) {
        int l=0, r=0, maxlen=0, mfreq=0;
        unordered_map<char, int> mpp;
        while(r<s.size()){
            mpp[s[r]]++;
            mfreq=max(mfreq, mpp[s[r]]);
            
            if(r-l+1-mfreq>k){
                mpp[s[l]]--;
                
                if(mpp[s[l]==0]){mpp.erase(s[l]);}
                l++;
            }
            if(r-l+1-mfreq<=k){maxlen=max(maxlen, r-l+1);}
            r++;

        }
    return maxlen; 
    }
};

	
// 930.Binary subarray with sum
// Input: nums = [1,0,1,0,1], goal = 2
// Output: 4
// Explanation: The 4 subarrays are bolded and underlined below:
// [1,0,1,0,1]
// [1,0,1,0,1]
// [1,0,1,0,1]
// [1,0,1,0,1]
class Solution {
public:
    int numSubarraysWithLessSum(vector<int>& nums, int goal) {
        int l=0, r=0;
        long long sum=0, c=0;
        if(goal<0){return 0;} // imp to remember this line since when the test case [0,0,0,0,0] and goal=0; this condition works ie incase goal-1<0 it returns 0;
        while(r<nums.size()){
            sum+=nums[r];
            while(sum>goal){
                sum-=nums[l];
                l++;
            }
            c+=r-l+1; //no.of subarrays of sum <= goal
            r++;
        }
        return c;
    }

    int numSubarraysWithSum(vector<int>& nums, int goal) {
        return numSubarraysWithLessSum(nums, goal)-numSubarraysWithLessSum(nums, goal-1);
    }
    
};

// 1248.Count number of nice subarrays
// Given an array of integers nums and an integer k. A continuous subarray is called nice if there are k odd numbers on it.
// Return the number of nice sub-arrays.
// Input: nums = [1,1,2,1,1], k = 3
// Output: 2
// Explanation: The only sub-arrays with 3 odd numbers are [1,1,2,1] and [1,2,1,1].
class Solution {
public:
    int numberOfSubarraysWithAtmostOdd(vector<int> &nums, int k){
        int l=0, r=0, odd=0, c=0;
        while(r<nums.size()){
            if(nums[r]%2){odd++;}
            while(odd>k){
                if(nums[l]%2){odd--;}
                l++;
            }
            c+=r-l+1;
            r++;
        }
        return c;
    }
    int numberOfSubarrays(vector<int>& nums, int k) {
        return numberOfSubarraysWithAtmostOdd(nums, k)-numberOfSubarraysWithAtmostOdd(nums, k-1);
    }
};

// 1358.Number of substring containing all three characters
// Input: s = "abcabc"
// Output: 10
// Explanation: The substrings containing at least one occurrence of the characters a, b and c are "abc", "abca", "abcab", "abcabc", "bca", "bcab", "bcabc", "cab", "cabc" and "abc" (again). 
class Solution {
public:
    int numberOfSubstrings(string s) {
        int r=0, c=0;
        vector<int> hash(3, -1);
        while(r<s.size()){
            hash[s[r]-'a']=r;
            c+=1+min({hash[0], hash[1], hash[2]}); //Remenber the usage of {} in min operator 
            r++;
        }
    return c; 
      
    }
};

// 1423.Maximum point you can obtain from cards
// Input: cardPoints = [1,2,3,4,5,6,1], k = 3
// Output: 12
// Explanation: After the first step, your score will always be 1. However, choosing the rightmost card first will maximize your total score. The optimal strategy is to take the three cards on the right, giving a final score of 1 + 6 + 5 = 12.
class Solution {
public:
    int maxScore(vector<int>& cardPoints, int k) {
        int lsum=0, rsum=0, maxsum=0;
        for(int i=0; i<k; i++){lsum+=cardPoints[i];};
        maxsum=lsum;
        int rindex=cardPoints.size()-1;
        for(int j=k-1; j>=0; j--){
            lsum=lsum-cardPoints[j];
            rsum=rsum+cardPoints[rindex];
            rindex--;
            maxsum=max(maxsum, lsum+rsum);
        }
        
    return maxsum;
    }
};


