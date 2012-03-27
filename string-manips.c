#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

static char str[] = "STRING TO REVERSE";


void reverse(int pos);
void reverse2(char* buff, int start, int end);
void rev(char* l, char* r);
void rev_words(char* str);

char* rev_words2(char* strA, char* strB);

void remove_whitespace(char* string);
int str2int(char* string);
char* esc_percent(char* in, char* out);
int remove_duplicates(char* str);

int main() {
    printf("Using first method:\n");
    printf("Original string: [%s]\n", str);
    reverse(0);
    printf("Reversed string: [%s]\n", str);
    
    printf("\nUsing second method:\n");
    char buffer[] = "This is a test";
    printf("Original string: [%s]\n", buffer);
    reverse2(buffer, 0, strlen(buffer)-1);
    printf("Reversed string: [%s]\n", buffer);
    
    printf("\nNow we reverse WORDS in a string.\n");
    char str2[] = "the world will go on forever";
    printf("Original string: [%s]\n", str2);
    rev_words(str2);
    printf("Words reversed: [%s]\n", str2);

    printf("\nNow we remove whitespace from: [%s].\n", buffer);
    remove_whitespace(buffer);
    printf("Now we have: [%s].\n", buffer);
    
    char str3[] = "123";
    printf("\nConvert number string into int: [%s].\n", str3);
    int n = str2int(str3);
    printf("%d\n", n);
    
    char input[] = "This is % oh yea";
    printf("\nEscape percents: [%s].\n", input);
    int len = strlen(input);
    char output[len*2];
    esc_percent(input, output);
    printf("%s\n", output);

    char test[] = "AABADBABBCADCAB";
    remove_duplicates(test);
    return 0;
}

// a method to reverse string
void reverse(int pos) {
    if (pos >= strlen(str)/2) return;
    
    char ch;
    
    // swap str[pos] and str[strlen(str) - pos - 1]
    ch = str[pos];
    str[pos] = str[strlen(str)-pos-1];
    str[strlen(str)-pos-1] = ch;
    
    // now recurse
    reverse(pos+1);
}

// second method of reversing string
void reverse2(char* buff, int start, int end) {
    char tmp;
    if (start >= end) return;
    
    tmp = *(buff + start);
    *(buff + start) = *(buff + end);
    *(buff + end) = tmp;
    
    reverse2(buff, ++start, --end);
}

// function to reverse a string in place
void rev(char* l, char* r) {
    char t;
    while (l < r) {
        t = *l;
        *l++ = *r;
        *r-- = t;
    }
}

// function to reverse words in string in place
void rev_words(char* str) {
    char* end, * x, * y;
    // reverse the whole sentence first
    // move end pointer to end of string
    for (end=str; *end; end++);
    // now call the function that reverses string chars
    rev(str, end-1);
    // now swap each word within sentence
    x = str-1;
    y = str;
    while (x++ < end) {
        if (*x == '\0' || *x == ' ') {
            rev(y, x-1);
            y = x + 1;
        }
    }
}

// alternate way to reverse words in string with new array
// this doesn't work yet
char* rev_words2(char* strA, char* strB) {
    char* x, * y;
    // move x pointer to end of char array
    for (x=strA; *x; x++);
    x--;
    y = x;
    
    for (int i=0; i<strlen(strA); i++) {
        if (*x == ' ') {
            y = x;
            while (y++) {
                strB = strcat(strB, y);
            }
        }
    }
    
    return strB;
}

void remove_whitespace(char* string) {
    int current = 0;
    int ahead = 0;
    while (string[ahead] != '\0') {
        while (string[ahead] == ' ') ahead++;
        string[current] = string[ahead];
        current++;
        ahead++;
    }
    string[current] = '\0';
}

int str2int(char* string) {
    int i = 0;
    int num = 0;
    int is_negative = 0;
    int len = strlen(string);
    
    if (string[0] == '-') {
        is_negative = 1;
        i = 1;
    }
    while (i < len) {
        num *= 10;
        //character 0 is represented as a byte with the value 48
        num += (string[i++] - '0');
    }
    if (is_negative) {
        num *= -1;
    }
    
    return num;
}

char* esc_percent(char* in, char* out) {
    int len = strlen(in);

    while (*in) {
        if (*in == '%') {
            *out = '%';
            out++;
        }
        *out = *in;
        in++;
        out++;
    }
    *out = '\0';
    
    return out;
}

int remove_duplicates(char *str) {
    // this method doesn't use hash map
    int char_check=0;
    int i,j;
    char ch;

    char filterstr[256]; // new

    if(str == NULL)
     return 0;

    /* check from 1st character in the string */
    while(str[char_check]) {
  
      ch = str[char_check];
  
      i = j = char_check+1;

      filterstr[0] = str[0]; // added

      /* logic to remove the repeated character */
      while(str[i]) {
         if(str[i] != ch) {
             filterstr[j] = str[i]; //modifid
             j++; 
         }
         i++; 
      }
      filterstr[j]='\0'; //modified

      str = filterstr; //added

      char_check++;
    }
    printf("String after removing duplicates : %s\n",filterstr);
    return 1;
}