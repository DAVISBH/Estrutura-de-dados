#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "utils.h"
#include <unistd.h>

alg_t algvet[]={
  {ALGINSERTION,"i"},
  {ALGSELECTION,"s"},
  {ALGQSORT,"q"},
  {ALGQSORT3,"q3"},
  {ALGQSORTINS,"qi"},
  {ALGQSORT3INS,"q3i"},
  {ALGSHELLSORT,"h"},
  {ALGRECSEL,"rs"},
  {0,0}
};


int name2num(char * name){
  int i=0;
  while (algvet[i].num){
    if (!strcmp(algvet[i].name,name)) return algvet[i].num;
    i++;
  }
  return 0;
}

char * num2name(int num){
  int i=0;
  while (algvet[i].num){
    if (algvet[i].num==num) return algvet[i].name;
    i++;
  }
  return 0;
}

void resetcounter(sortperf_t *s) {
    s->cmp = 0;
    s->move = 0;
    s->calls = 0;
}

void inccmp(sortperf_t *s, int num) {
    s->cmp += num;
}

void incmove(sortperf_t *s, int num) {
    s->move += num;
}

void inccalls(sortperf_t *s, int num) {
    s->calls += num;
}

char *printsortperf(sortperf_t *s, char *str, char *pref) {
    sprintf(str, "%s cmp %d move %d calls %d", pref, s->cmp, s->move, s->calls);
    return str;
}

void initVector(int *vet, int size) {
    for (int i = 0; i < size; i++) {
        vet[i] = (int)(drand48() * size);
    }
}

void printVector(int *vet, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", vet[i]);
    }
    printf("\n");
}

void uso() {
    fprintf(stderr, "sortperf\n");
    fprintf(stderr, "\t-z <int>\t(vector size)\n");
    fprintf(stderr, "\t-s <int>\t(initialization seed)\n");
    fprintf(stderr, "\t-a <s|i|q|q3|qi|q3i|h|rs>\t(algorithm)\n");
    fprintf(stderr, "\t    s\tselection\n");
    fprintf(stderr, "\t    i\tinsertion\n");
    fprintf(stderr, "\t    q\tquicksort\n");
    fprintf(stderr, "\t    q3\tquicksort+median3\n");
    fprintf(stderr, "\t    qi\tquicksort+insertion\n");
    fprintf(stderr, "\t    q3i\tquicksort+median3+insertion\n");
    fprintf(stderr, "\t    h\theapsort\n");
    fprintf(stderr, "\t    rs\trecursive selection\n");
}

void parse_args(int argc, char **argv, opt_t *opt) {
    extern char *optarg;
    extern int optind;
    int c;

    opt->seed = 1;
    opt->size = 10;
    opt->alg = 1;

    while ((c = getopt(argc, argv, "z:s:a:h")) != EOF) {
        switch (c) {
            case 'z':
                opt->size = atoi(optarg);
                break;
            case 's':
                opt->seed = atoi(optarg);
                break;
            case 'a':
                opt->alg = name2num(optarg);
                break;
            case 'h':
            default:
                uso();
                exit(1);
        }
    }
    if (!opt->alg) {
        uso();
        exit(1);
    }
}

void clkDiff(struct timespec t1, struct timespec t2, struct timespec *res) {
    if (t2.tv_nsec < t1.tv_nsec) {
        res->tv_nsec = 1000000000 + t2.tv_nsec - t1.tv_nsec;
        res->tv_sec = t2.tv_sec - t1.tv_sec - 1;
    } else {
        res->tv_nsec = t2.tv_nsec - t1.tv_nsec;
        res->tv_sec = t2.tv_sec - t1.tv_sec;
    }
}
