#include <stdio.h>
#include <string.h>

#include "set.h"


int my_strcmp(const char *s1, const char *s2) {
    if (strcmp(s1, s2) == 0)
        return 1;
    return 0;
}


int main() {
    Set set1, set2, setu, seti, setd;
    ListElmt *member;

    set_init(&set1, (int (*)(const void *, const void *)) my_strcmp, free);
    char str1[] = "A";
    char str2[] = "B";
    char str3[] = "C";
    set_insert(&set1, str1);
    set_insert(&set1, str2);
    set_insert(&set1, str3);

    set_init(&set2, (int (*)(const void *, const void *)) my_strcmp, free);
    char str4[] = "A";
    char str5[] = "D";
    set_insert(&set2, str4);
    set_insert(&set2, str5);

    set_union(&setu, &set1, &set2);
    set_intersection(&seti, &set1, &set2);
    set_difference(&setd, &set1, &set2);

    printf("set union\n");
    for (member = list_head(&setu); member != NULL; member = list_next(member)) {
        printf("%s\n", (char *) member->data);
    }

    printf("\nset intersection\n");
    for (member = list_head(&seti); member != NULL; member = list_next(member)) {
        printf("%s\n", (char *) member->data);
    }

    printf("\nset difference\n");
    for (member = list_head(&setd); member != NULL; member = list_next(member)) {
        printf("%s\n", (char *)member->data);
    }

    return 0;
}

