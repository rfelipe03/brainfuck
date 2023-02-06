#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#define MAX 16384

void mov(int *pos, int dir) {
	if (*pos == 0 && dir == -1) {
		*pos = MAX-1;
	} else if (*pos == MAX-1 && dir == 1) {
		*pos = 0;
	}
	*pos+=dir;
}

int gotoAndFind(char *c, int pos, char dir, int len) {
	int i, s=0;
	for (i = pos+dir; i > 0 && i < len; i+= dir) {
		if (c[i]==(dir==1?'[':']')) {
			s++;
		} else if (c[i]==(dir==1?']':'[')) {
			if (s==0) return i;
			else s--;
		}
	}
	return -1;
}

int main(int argc, char **argv) {
	char *c;
	unsigned int strip[MAX]={0}, pt=0;
	int r, initmem=10, i=0, j;
	FILE *src;
	struct termios old, new;
	tcgetattr(0,&old);
	new = old;
	new.c_lflag &= ~ECHO;
	new.c_lflag &= ~ICANON;
	if (argc<2) {
		fprintf(stderr,"Please provide a script to run.\n");
		return 1;
	} else if (argc > 2) {
		fprintf(stderr,"Can only run one script at once.\n");
		return 1;
	}
	src = fopen(argv[1],"r");
	if (!src) {
		fprintf(stderr,"Could not open file.\n");
		return 1;
	}
	c = malloc(initmem);
	while ((r = fgetc(src))!=EOF) {
		c[i] = (char)r;
		i++;
		if (i>=initmem) {
			c = realloc(c,initmem+=10);
		}
	}
	c[i]=0;
	fclose(src);
	tcsetattr(0,TCSANOW,&new);
	for (j = 0; j < i; j++) {
		switch(c[j]) {
			case '+':
				strip[pt]++;
				break;
			case '-':
				strip[pt]--;
				break;
			case '>':
				mov(&pt,1);
				break;
			case '<':
				mov(&pt,-1);
				break;
			case ',':
				strip[pt] = getchar();
				break;
			case '.':
				putchar(strip[pt]);
				break;
			case '[':
				if (strip[pt]==0) {
					int p;
					p = gotoAndFind(c,j,1,i);
					if (p>0) {
						j=p;
					} else {
						fprintf(stderr,"Syntax error. Could not find matching `]`.\n");
					}
				}
				break;
			case ']':
				if (strip[pt]!=0) {
					int p;
					p = gotoAndFind(c,j,-1,i);
					if (p>0) {
						j=p;
					} else {
						fprintf(stderr,"Syntax error. Could not find matching `[`.\n");
					}

				}
				break;
		}
	}
	free(c);
	tcsetattr(0,TCSANOW,&old);
	return 0;
}
