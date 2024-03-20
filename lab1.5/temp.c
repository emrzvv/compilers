#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int getCodeEnd(char *str, int len) {
    if (str[0] != '#') return -1;
    for (int i = 1; i < len; ++i) {
        if (str[i] < '0' || str[i] > '9') {
            if (i == 1) return -1;
            else return i;
        }
    }
    return len;
}

void translate(char *str, int len) {
    char *temp = (char*)malloc(sizeof(char) * len);
    int j = 0;
    for (int i = 0; i < len; ++i) {
        if (str[i] == '\'') {
            if (i + 1 < len && str[i + 1] == '\'') {
                temp[j] = '\'';
                j++;
                i++;
            } // else skip
        } else if (str[i] == '#') {
            int codeEnd = getCodeEnd(str + i, len - i);
            if (codeEnd != -1) {
                char codeStr[codeEnd];
                strncpy(codeStr, &str[i + 1], codeEnd - 1);
                codeStr[codeEnd - 1] = '\0';

                int code = atoi(codeStr);

                if (code >= 0 && code <= 255) { 
                    temp[j] = (char)code; 
                    j++;
                    i += codeEnd; 
                } else {
                    temp[j] = str[i]; 
                    j++;
                }
            } else {
                temp[j] = str[i];
                j++;
            }
        } else {
            temp[j] = str[i];
            j++;
        }
    }
    temp[j] = '\0';
    strcpy(str, temp);
    free(temp);
}


int main() {
    char str[] = "#123'hello ''world'''#125";
    int length = strlen(str);
    
    printf("Original string: %s\n", str);
    translate(str, length);
    printf("Processed string: %s\n", str);

    return 0;
}
