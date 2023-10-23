// The MIT License (MIT)

// Copyright (c) 2023 Robin Kristiansen

//  Permission is hereby granted, free of charge, to any person obtaining a
//  copy of this software and associated documentation files (the "Software"),
//  to deal in the Software without restriction, including without limitation
//  the rights to use, copy, modify, merge, publish, distribute, sublicense,
//  and/or sell copies of the Software, and to permit persons to whom the
//  Software is furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
//  OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
//  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
//  DEALINGS IN THE SOFTWARE.

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

static int minimum(int a, int b, int c) {
    int min = (a < b ? a : b);
    min = (min < c ? min : c);
    return min;
}

static void print_matrix(int **mat, size_t m, size_t n) {
    for (size_t i = 0; i < m; ++i) {
        for (size_t j = 0; j < n; ++j) {
            printf("%2d ", mat[i][j]);
        }
        printf("\n");
    }
    printf("--------------------\n");
}

static int LevenshteinDistance(const char *__restrict__ s, const char *__restrict__ t)
{
    size_t m = strlen(s);
    size_t n = strlen(t);

    int **d = calloc(m+1, sizeof(int *));
    for (int r = 0; r < m+1; r++) {
        d[r] = calloc(n+1, sizeof(int));
    }

    for (size_t i = 0; i < m+1; i++) {
        d[i][0] = i;
    }
    for (size_t j = 0; j < n+1; j++) {
        d[0][j] = j;
    }
    
    print_matrix(d, m+1, n+1);

    for (size_t j = 1; j < n+1; j++) {
        for (size_t i = 1; i < m+1; i++) {
            //int substitutionCost = 0;
            if (s[i-1] == t[j-1]) {
                d[i][j] = d[i-1][j-1];
                //substitutionCost = 0;
            } else {
                //substitutionCost = 1;
                d[i][j] = 1 + minimum(d[i - 1][j],
                                      d[i][j - 1],
                                      d[i - 1][j - 1]);
            }
        }
    }

    print_matrix(d, m+1, n+1);

    int answer = d[m][n];

    for (int i = 0; i < n+1; i++) {
        free(d[i]);
    }
    free(d);

    return answer;
}

int main(int argc, char **argv) {
    // TODO: accept strings from commandline
    
    char *a, *b;
    if (argc == 3) {
        a = argv[1];
        b = argv[2];
    } else {
        a = "Hello";
        b = "henlo";
    }

    printf("LevenshteinDistance(%s, %s) = %d\n", a, b, LevenshteinDistance(a, b));
    return 0;
}
