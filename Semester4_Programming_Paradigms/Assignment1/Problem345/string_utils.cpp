#include "string_utils.h"

int length(char s[]) {
    int l = 0;
    while (s[l] != '\0')
        l++;
    return l;
}

int compareStrings(char s1[], char s2[], int index) {
    int l1 = length(s1);
    int l2 = length(s2);

    if (l1 < l2)
        return -1;
    else if (l1 > l2)
        return 1;
    else {
        if (s1[index] == '\0')
            return 0;
        else if (s1[index] == s2[index])
            return compareStrings(s1, s2, ++index);
        else if (s1[index] < s2[index])
            return -1;
        else if (s1[index] > s2[index])
            return 1;
    }
    return 0;
}

int checkPalindrome(char s[], int n, int i) {
    if (i == n / 2 + 1)
        return 1;
    if (s[i] == s[n - i - 1])
        return checkPalindrome(s, n, i + 1);
    else
        return false;
}

int replaceCharacter(char c1, char c2, char s[], int index) {
    int n = length(s);
    if (index == n)
        return 1;
    if (s[index] == c1) {
        s[index] = c2;
        return replaceCharacter(c1, c2, s, index + 1);
    } else
        return replaceCharacter(c1, c2, s, index + 1);
    return 0;
}

char lexicographicallySmallest(char s[], int n, char least) {
    if (n < 0)
        return least;
    if (least > s[n])
        return lexicographicallySmallest(s, n - 1, s[n]);
    else
        return lexicographicallySmallest(s, n - 1, least);
}
