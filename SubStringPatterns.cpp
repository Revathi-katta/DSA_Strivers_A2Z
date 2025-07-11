// 76. Minimum Window Substring
// Approach: Sliding window + ASCII char frequency map to track needed chars in current window.
// Input: s = "ADOBECODEBANC", t = "ABC"
// Output: "BANC"
// Time: O(n)
// Space: O(1) (constant 128 for ASCII)
class Solution {
public:
    string minWindow(string s, string t) {
        vector<int> map(128, 0);
        for(auto it: t){map[it]++;}
        int l=0, r=0, head=0, minLen=INT_MAX, counter=t.size();
        while(r<s.size()){
            if(map[s[r]]>0)counter--;
            map[s[r]]--;
            r++;
            while(counter==0){
                if((r-l)<minLen){minLen=r-l; head=l;}
                map[s[l]]++;  //first remove
                if(map[s[l]]>0)counter++;  //then check and increment
                // if(map['B'] == 0) counter++; // ❌ FALSE (it's 1), here we check '==0' which is not correct we should check 
                // map['B']++; // map['B'] = 2

                l++;
                  
            }
        }
        return minLen==INT_MAX ? "" : s.substr(head, minLen);
        
    }
};


// 159. Longest Substring with At Most Two Distinct Characters
// Approach: Sliding window maintaining a frequency map and a 'distinct' count.
// Input: s = "eceba"
// Output: "ece"
// Time: O(n)
// Space: O(1) (ASCII map)
string longestSubstring(string s){
    int l=0, r=0, head=0, distinct=0, maxlen=0;
    vector<int> mpp(128, 0);
    while(r<s.size()){
        //check if its distinct and increment if yes
        if(mpp[s[r]]==0){distinct++;}
        mpp[s[r]]++;
        r++;
        while(distinct>2){
            mpp[s[l]]--;
            //after removing if it becomes 0 that means we have just removed a distinct character and we have to decrement the distinct
            if(mpp[s[l]]==0){distinct--;}
            l++;
        }
        if((r-l)>maxlen){maxlen=r-l; head=l;}
    }
    return maxlen==0 ? "" : s.substr(head, maxlen);
}


// 3. Longest Substring Without Repeating Characters
// Approach: Sliding window shrinking on repeat; ASCII frequency map to track presence
// Input: s = "abcabcbb"
// Output: "abc"
// Time: O(n)
// Space: O(1)
string longestSubstringWithoutRepeatingCharacters(string s){
    int l=0, r=0, head=0, maxlen=0;
    vector<int> mpp(128, 0);
    while(r<s.size()){
        while(mpp[s[r]]==1){
            mpp[s[l]]--;
            l++;
        }
        mpp[s[r]]++;
        r++; 
        if((r-l)>maxlen){maxlen=r-l; head=l;}              
    }
    return maxlen==0 ? "" : s.substr(head, maxlen);
}
