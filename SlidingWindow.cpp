// Template 1: Sliding Window (Shrinkable)
// The best template I've found so far:

int i = 0, j = 0, ans = 0;
for (; j < N; ++j) {
    // CODE: use A[j] to update state which might make the window invalid
    for (; invalid(); ++i) { // when invalid, keep shrinking the left edge until it's valid again
        // CODE: update state using A[i]
    }
    ans = max(ans, j - i + 1); // the window [i, j] is the maximum window we've found thus far
}
return ans;
// Essentially, we want to keep the window valid at the end of each outer for loop.

// Template 2: Sliding Window (Non-shrinkable)
int i = 0, j = 0;
for (; j < N; ++j) {
    // CODE: use A[j] to update state which might make the window invalid
    if (invalid()) { // Increment the left edge ONLY when the window is invalid. In this way, the window GROWs when it's valid, and SHIFTs when it's invalid
        // CODE: update state using A[i]
        ++i;
    }
    // after `++j` in the for loop, this window `[i, j)` of length `j - i` MIGHT be valid.
}
return j - i; // There must be a maximum window of size `j - i`.
// Essentially, we GROW the window when it's valid, and SHIFT the window when it's invalid.

// Note that there is only a SINGLE for loop now!


// 1838. Frequency of the Most Frequent Element  
// Approach: Sliding window on sorted array; check if all elements in window can be made equal to nums[r] using ≤k operations  
// Input: nums = [1,2,4], k = 5  
// Output: 3  
// Time: O(n log n) (due to sorting)  
// Space: O(1) (ignoring sort space)  
class Solution {
public:
    int maxFrequency(vector<int>& nums, int k) {
        int l=0, r=0, maxfreq=0;
        long long sum=0;
        sort(nums.begin(), nums.end()); //***
        while(r<nums.size()){
            sum+=nums[r];
            while(l<=r && ((long long)nums[r]*(r-l+1))-sum>k){//by chcking this we assume that the elements left to r are sorted so we have sort first 
                sum-=nums[l];
                l++;
            }
            maxfreq=max(maxfreq, r-l+1);
            r++;
        }
    return maxfreq;    
    }
}; Better explanation :
// What should we use as the state? It should be the sum of numbers in the window
// How to determine invalid? The window is invalid if (j - i + 1) * A[j] - sum > k.
// // OJ: https://leetcode.com/problems/frequency-of-the-most-frequent-element/
// // Author: github.com/lzl124631x
// // Time: O(NlogN)
// // Space: O(1)
// class Solution {
// public:
//     int maxFrequency(vector<int>& A, int k) {
//         sort(begin(A), end(A));
//         long i = 0, N = A.size(), ans = 1, sum = 0;
//         for (int j = 0; j < N; ++j) {
//             sum += A[j];
//             while ((j - i + 1) * A[j] - sum > k) sum -= A[i++];
//             ans = max(ans, j - i + 1);
//         }
//         return ans;
//     }
// };
// FAQ:

// Why is the time complexity O(NlogN)?
// The sorting takes O(NlogN). The two pointer part only takes O(N) because both the pointers i and j traverse the array ONLY ONCE.

// Why is (j - i + 1) * A[j] - sum <= k valid?
// (j - i + 1) is the length of the window [i, j]. We want to increase all the numbers in the window to equal A[j], the number of operations needed is (j - i + 1) * A[j] - sum which should be <= k. For example, assume the window is [1,2,3], increasing all the numbers to 3 will take 3 * 3 - (1 + 2 + 3) operations.

// OJ: https://leetcode.com/problems/frequency-of-the-most-frequent-element/
// Author: github.com/lzl124631x
// Time: O(NlogN)
// Space: O(1)
class Solution {
public:
    int maxFrequency(vector<int>& A, int k) {
        sort(begin(A), end(A));
        long i = 0, j = 0, N = A.size(), sum = 0;
        for (; j < N; ++j) {
            sum += A[j];
            if ((j - i + 1) * A[j] - sum > k) sum -= A[i++];
        }
        return j - i;
    }
};


// 3.Longest Substring without Repeating characters
// Input: s = "abcabcbb"
// Output: 3
// Explanation: The answer is "abc", with the length of 3.
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

// Variation: Longest Substring with At Most K Distinct Characters  
// Approach: Sliding window; track character count with ASCII map, shrink window if distinct > k  
// Input: s = "eceba", k = 2  
// Output: "ece"  
// Time: O(n)  
// Space: O(1) (ASCII map size)
// 159. Longest Substring with At Most Two Distinct Characters is a specific case of this (k=2)
string LongestSubstringWithAtMostKDistinctCharacters(string s, int k){
    vector<int> mpp(128, 0);
    int l=0, r=0, maxlen=0, head=0, distinct=0;
    while(r<s.size()){
        if(mpp[s[r]]==0)distinct++;
        mpp[s[r]]++;
        r++;
        while(distinct>k){
            mpp[s[l]]--;
            if(mpp[s[l]]==0)distinct--;
            l++;
        }
        if(maxlen<r-l){maxlen= r-l; head=l;}
    }
    return maxlen==0 ? ""  : s.substr(head, maxlen);
}

// 424. Longest Repeating Character Replacement  
// Approach: Sliding window; track count of most frequent character, shrink window if replacements needed > k  
// Input: s = "AABABBA", k = 1  
// Output: 4  
// Time: O(n)  
// Space: O(1) (26-size array for uppercase A–Z)
class Solution {
public:
    int characterReplacement(string s, int k) {
        int l=0, r=0, maxlen=0, maxcnt=0;
        vector<int> mpp(26,0);
        //state: no.of elements other than maxelement in the current window
        while(r<s.size()){
            mpp[s[r]-'A']++;
            maxcnt=max(maxcnt, mpp[s[r]-'A']);  
            if(r-l+1-maxcnt>k){
                mpp[s[l]-'A']--;
                l++;}                  //r-l+1-maxcnt=state=no.of distinct elements other than maxcnt element in that window
            maxlen = max(r-l+1, maxlen);
            r++;
        }
    return maxlen;    
    }
};

// 487. Max Consecutive Ones II  
// Approach: Sliding window with at most one zero allowed in window  
// Input: nums = [1,0,1,1,0]  
// Output: 4  
// Time: O(n)  
// Space: O(1)
int MaxConsecutiveOnesII(vector<int>nums){
    int l=0, r=0, zeroes=0, maxlen=0;
    while(r<nums.size()){
        if(nums[r]==0)zeroes++;
        while(zeroes>1){
            if(nums[l]==0)zeroes--;
            l++;
        }
        maxlen= max(maxlen, r-l+1);
        r++;
    }
    return maxlen;
}


// 1004. Max Consecutive Ones III  
// Approach: Sliding window; keep count of 0s and shrink window when zeroes > k  
// Input: nums = [1,1,1,0,0,0,1,1,1,1,0], k = 2  
// Output: 6  
// Time: O(n)  
// Space: O(1)
class Solution {
public:
    int longestOnes(vector<int>& nums, int k) {
        int l=0, r=0, maxlen=0, zeroes=0;
        while(r<nums.size()){
            if(nums[r]==0)zeroes++;
            while(zeroes>k){
                if(nums[l]==0)zeroes--;
                l++;
            }
            maxlen= max(maxlen, r-l+1);
            r++;
        }
        return maxlen;
    }
};


// 713. Subarray Product Less Than K  
// Approach: Sliding window keeping product < k; count subarrays ending at r as (r - l + 1)  
// Input: nums = [10, 5, 2, 6], k = 100  
// Output: 8  
// Time: O(n)  
// Space: O(1)
class Solution {
public:
    int numSubarrayProductLessThanK(vector<int>& nums, int k) {
        int l=0, r=0, cnt=0, pro=1;
        while(r<nums.size()){
            pro*=nums[r];
            while(l<=r && pro>=k){
                pro/=nums[l];
                l++;
            }
            cnt+=r-l+1; //All subarrays ending at r: [r], [r-1, r], [r-2, ..., r], ..., [l, ..., r] are valid. There are (r - l + 1) of them.

            r++;
        }
        return cnt;
    }
};

// 1208. Get Equal Substrings Within Budget  
// Approach: Sliding window; track cost to convert s[i] to t[i], shrink when cost > maxCost  
// Input: s = "abcd", t = "bcdf", maxCost = 3  
// Output: 3  
// Time: O(n)  
// Space: O(1)
class Solution {
public:
    int equalSubstring(string s, string t, int maxCost) {
        int l=0, r=0, cost=0, maxlen=0;
        while(r<s.size()){
            cost+=abs(s[r]-t[r]);
            while(cost>maxCost){
                cost-=abs(s[l]-t[l]);
                l++;
            }
            maxlen=max(maxlen, r-l+1);
            r++;
        }
        return maxlen;
    }
};

// 1493. Longest Subarray of 1's After Deleting One Element  
// Approach: Sliding window; allow at most one zero in the window, track longest length excluding one zero  
// Input: nums = [1,1,0,1]  
// Output: 3  
// Time: O(n)  
// Space: O(1)
class Solution {
public:
    int longestSubarray(vector<int>& nums) {
        int l=0, r=0, zerocnt=0, maxlen=0;
        while(r<nums.size()){
            if(nums[r]==0)zerocnt++;
            while(zerocnt>1){
                if(nums[l]==0)zerocnt--;
                l++;
            }
            maxlen=max(maxlen, r-l); //not r-l+1; as we will delete one 0 and length decrases by 1
            r++;
        }
        return zerocnt==0 ? nums.size()-1 : maxlen;       
    }
};

// 1695. Maximum Erasure Value  
// Approach: Sliding window with set to track unique elements; adjust window to maintain uniqueness  
// Input: nums = [4,2,4,5,6]  
// Output: 17  
// Time: O(n)  
// Space: O(n)
class Solution {
public:
    int maximumUniqueSubarray(vector<int>& nums) {
        int l=0, r=0, maxscore=0, score=0;
        // unordered_map<int, int> mpp;
        unordered_set<int> s;
        while(r<nums.size()){
            score+=nums[r];
            // while(mpp[nums[r]]>0){
            //     mpp[nums[l]]--;
            //     score-=nums[l];
            //     l++;
            // }/
            while(s.count(nums[r])){
                s.erase(nums[l]);
                score-=nums[l];
                l++;
            }
            // mpp[nums[r]]++;
            s.insert(nums[r]);
            maxscore=max(score, maxscore);
            r++;
        }
        return maxscore;
    }
};

// 2009. Minimum Number of Operations to Make Array Continuous  
// Approach: Sort and remove duplicates, then sliding window to find max # of unique elements within [x, x + n - 1]  
// Input: nums = [4,2,5,3], Output: 0  
// Time: O(n log n) (due to sort + unique + sliding window)  
// Space: O(n) (for unique array in-place)
class Solution {
public:
    int minOperations(vector<int>& nums) {
        // set<int> s(nums.begin(), nums.end());
        // vector<int> a(s.begin(), s.end());
        sort(nums.begin(), nums.end());
        int n=nums.size();
        nums.erase(unique(nums.begin(), nums.end()), nums.end());
        // or use sort + A.erase(unique(begin(A), end(A)), end(A));, unique(begin(A), end(A)) return the pointer to the element next to the last unique element after keeping all the unique elements at the start.         
        int m=nums.size();
        int l=0, r=0, maxlen=0;
        //we have to find maxlen of window with more no.of elements <a[r]+N in a;
        
        while(r<m){ 
            // int num=a[l]+n;   created to compare if a[r]>=num but a[l]+n exceeding int limit.      
            while(nums[r]-nums[l]>=n)l++;
            maxlen=max(r-l+1, maxlen);
            r++;
        }
        return n-maxlen;
    }
};

// 2024. Maximize the Confusion of an Exam  
// Approach: Sliding window; keep track of count of T and F, and shrink when min(T, F) > k  
// Input: answerKey = "TTFF", k = 2  
// Output: 4  
// Time: O(n)  
// Space: O(1)
class Solution {
public:
    int maxConsecutiveAnswers(string answerKey, int k) {
        int l=0, r=0, t=0, f=0, mini=0, maxlen=0;
        while(r<answerKey.size()){
            if(answerKey[r]=='T')t++;
            else{f++;}
            mini=min(t, f);
            while(mini>k){
                if(answerKey[l]=='T')t--;
                else{f--;}
                mini=min(t, f);
                l++;
            }
            maxlen=max(maxlen, r-l+1);
            r++;
        }
    return maxlen;   
    }
};

# The following problems are also solvable using the shrinkable template with the "At Most to Equal" trick
// 930. Binary Subarrays With Sum  
// Approach: Sliding window count of subarrays with sum ≤ goal and sum ≤ goal-1, take the difference  
// Input: nums = [1,0,1,0,1], goal = 2  
// Output: 4 
// [1,0,1,0,1]
// [1,0,1,0,1]
// [1,0,1,0,1]
// [1,0,1,0,1]
// Time: O(n)  
// Space: O(1)
class Solution {
public:
    int numSubarraysWithSumLessthanEqual(vector<int>& nums, int goal) {
        // sum=k == sum<=k -sum<k-1;
        int l=0, r=0, cnt=0, sum=0;
        while(r<nums.size()){
            sum+=nums[r];
            while(l<=r && sum>goal){
                sum-=nums[l];
                l++;
            }
            cnt+=r-l+1;
            r++;
        }
        return cnt;
    }
    int numSubarraysWithSum(vector<int>& nums, int goal) {
        return numSubarraysWithSumLessthanEqual(nums, goal)-numSubarraysWithSumLessthanEqual(nums, goal-1);
    }
};

// 992. Subarrays with K Different Integers  
// Approach: Count subarrays with ≤k distinct - subarrays with ≤k-1 distinct  
// Input: nums = [1,2,1,2,3], k = 2  
// Output: 7  
// Time: O(n)  
// Space: O(n) (for frequency map; array used for optimization)
class Solution {
public:
    int subarraysWithLessthanEqualKDistinct(vector<int>& nums, int k) {
        // map<int, int> mpp;
        int mpp[20001]={0}; //optimisation
        int l=0, r=0, cnt=0, distinct=0;
        while(r<nums.size()){
            if(mpp[nums[r]]==0)distinct++;
            mpp[nums[r]]++;
            while(distinct>k){
                mpp[nums[l]]--;
                if(mpp[nums[l]]==0)distinct--;
                l++;
            }
            cnt+=r-l+1;
            r++;
        }
        return cnt;
    }
    int subarraysWithKDistinct(vector<int>& nums, int k) {
        return subarraysWithLessthanEqualKDistinct(nums, k)-subarraysWithLessthanEqualKDistinct(nums, k-1);
    }
};

// 1248. Count Number of Nice Subarrays  
// Approach: Count subarrays with ≤k odd numbers - subarrays with ≤k-1 odds  
// Input: nums = [1,1,2,1,1], k = 3  
// Output: 2  
// Time: O(n)  
// Space: O(1)
class Solution {
public:
    int numberOfSubarraysWithLesskOdds(vector<int>& nums, int k) {
        int l=0, r=0, cnt=0, odds=0;
        while(r<nums.size()){
            if(nums[r]&1)odds++;
            while(odds>k){
                if(nums[l]&1)odds--;
                l++;
            }
            cnt+=r-l+1;
            r++;
        }
        return cnt;
    }
    int numberOfSubarrays(vector<int>& nums, int k) {
       return numberOfSubarraysWithLesskOdds(nums, k)-numberOfSubarraysWithLesskOdds(nums, k-1); 
    }
};

// 2062. Count Vowel Substrings of a String  
// Approach: Sliding window; count substrings with exactly 5 vowels = atMost(5) - atMost(4); reset window if non-vowel found  
// Input: word = "aeiouu"  
// Output: 2  
// Time: O(n)  
// Space: O(1) (26-size array)
class Solution {
public:
    bool isVowel(char c){
        if(c=='a'||c=='e'||c=='i'||c=='o'||c=='u')return true;
        return false;
    }
    int countVowelLessthan5Substrings(string word, int k) {
        int l=0, r=0, cnt=0, distinct=0;
        vector<int> mpp(26, 0);
        while(r<word.size()){
            if(!isVowel(word[r])){
                fill(mpp.begin(), mpp.end(), 0);
                distinct=0;
                r++;
                l=r;
                continue;
                }

            if(isVowel(word[r])&& mpp[word[r]-'a']==0)distinct++;
            mpp[word[r]-'a']++;
            while(distinct>k){
                mpp[word[l]-'a']--;
                if(isVowel(word[l])&& mpp[word[l]-'a']==0)distinct--;
                l++;
            }           
            cnt+=r-l+1;
            r++;
        }
        return cnt;
    }
    int countVowelSubstrings(string word){
        return countVowelLessthan5Substrings(word,5)-countVowelLessthan5Substrings(word, 4);

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


