#!/usr/bin/env runc
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Prototype Declaration */
double expand_matrix(double mat[][256], int n, int i, int j);
int read_matrix(char *file, char key[], int mat[][256]);
int split_char(char *line, char array[]);
int split_int(char *line, int array[]);
void chomp(char *s);
void print_double(double array[], int n);
void print_mat(double mat[][256], int n);
/* Prototype Declaration End */

int main(void) {
    
    char key[256];
    int score[256][256];
    double mat[256][256];
    int sum[256];
    int n = read_matrix("example/score", key, score);
    int i, j;
    for (j=0; j<n; j++) {
        for (i=0; i<n; i++) {
            sum[j] += score[i][j];
        }
    }

    for (i=0; i<n; i++) {
        for (j=0; j<n; j++) {
            mat[i][j] = (double)score[i][j]/sum[j];
        }
    }
    print_mat(mat, n);

    double mult[256][256];
    for (i=0; i<n; i++) {
        for (j=0; j<n; j++) {
            mult[i][j] = expand_matrix(mat, n, i, j);
        }
    }
    printf("\n");
    print_mat(mult, n);

    return 0;
}

double expand_matrix(double mat[][256], int n, int i, int j)
{
    double ret = 0;

    int k;
    for (k=0; k<n; k++) {
        ret += mat[i][k] * mat[k][j];
    }

    return ret;
}

int read_matrix(char *file, char key[], int mat[][256])
{
    FILE *fp;
    if ((fp = fopen(file, "r")) == NULL) {
	fprintf(stderr, "can't open %s\n", file);
	exit(2);
    }
    
    char buf[BUFSIZ] = "";
    int array[BUFSIZ];
    
    int n;
    int i = 0;
    while (fgets(buf, BUFSIZ, fp)) {
	chomp(buf);
        n = split_int(buf, mat[i]);
        i++;
    }
    
    return i;
}

int split_char(char *line, char array[])
{
    char *str = strtok(line, " ");
    int i = 0;
    while (str != NULL) {
        array[i++] = str[0];
        str = strtok(NULL, " ");
    }
    return i;
}

int split_int(char *line, int array[])
{
    char *str = strtok(line, " ");
    int i = 0;
    while (str != NULL) {
        array[i++] = atoi(str);
        str = strtok(NULL, " ");
    }
    return i;
}

void chomp(char *s)
{
    int n = strlen(s);
    if (s[n-1] == '\n') {
	s[n-1] = '\0';
    }
}

void print_double(double array[], int n)
{
    int i;
    printf("%f", array[0]);
    for(i=1; i<n; i++){
	printf(" %f", array[i]);
    }
    printf("\n");
}

void print_mat(double mat[][256], int n)
{
    int i;
    for(i=0; i<n; i++){
	print_double(mat[i], n);
    }
}
