#include<iostream>
#include<cstring>
#include<cstdlib>
using namespace std;
int* getNextval(char *p);
int *searchfail(char*p);
int kmp(char*s, char*p);
int main()
{
	char s[100010];
	char p[100010];
	scanf("%s", s);
	scanf("%s", p);
	int p_length = strlen(p);
	int* fail = searchfail(p);
	for (int i = 0; i < p_length; i++) {
		cout << fail[i] << " ";
	}
	cout << endl;
	int position = kmp(s, p);
	cout << position << endl;
	return 0;
}
int* getNextval(char *p)
{
	int i = 0, j = -1, p_length;
	p_length = (int)strlen(p);
	int *next = new int[p_length];
	next[0] = -1;
	while (i < p_length - 1) {
		if (j == -1 || p[i] == p[j]) {
			i++;
			j++;
			if (p[i] != p[j]) {
				next[i] = j;
			}
			else {
				next[i] = next[j];
			}
		}
		else {
			j = next[j];
		}
	}
	return next;
}
int kmp(char*s, char*p) {
	int *next = getNextval(p);
	int i = 0, j = 0, p_length, s_length;
	p_length = (int)strlen(p);
	s_length = (int)strlen(s);
	while (i < s_length&&j < p_length) {
		if (j == -1 || s[i] == p[j]) {
			i++;
			j++;
		}
		else {
			j = next[j];
		}
	}
	if (j == p_length) {
		return i - j;
	}
	return -1;
}
int *searchfail(char*p) {
	int p_length, i, j;
	p_length = (int)strlen(p);
	int* f = new int[p_length];
	f[0] = -1;
	for (j = 1; j < p_length; j++) {
		i = f[j - 1];
		while (p[j] != p[i + 1] && i >= 0) {
			i = f[i];
		}
		if (p[j] == p[i + 1]) {
			f[j] = i + 1;
		}
		else { f[j] = -1; }
	}
	return f;
}
