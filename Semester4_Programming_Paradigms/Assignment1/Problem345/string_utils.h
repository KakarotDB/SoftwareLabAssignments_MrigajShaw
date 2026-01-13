#ifndef STRING_UTILS_H
#define STRING_UTILS_H

int length(char s[]);
int compareStrings(char s1[], char s2[], int index);
int checkPalindrome(char s1[], int n, int i);
int replaceCharacter(char c1, char c2, char s1[], int index);
char lexicographicallySmallest(char s1[], int n, char least);

#endif
