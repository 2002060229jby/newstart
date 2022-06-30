int minSubArrayLen(int target, int* nums, int numsSize){
    int l = 0, r = -1, sum = 0, ans = numsSize + 1;
    while (1) {
        if (sum < target) {
            if (r + 1 == numsSize) break;
            r += 1;
            sum += nums[r];
        } else {
            sum -= nums[l];
            l += 1;
        }
        if (sum >= target && r - l + 1 < ans) ans = r - l + 1; 
    }
    if (ans == numsSize + 1) return 0;
    return ans;
}