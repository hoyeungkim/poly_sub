#include <stdio.h>
#define MAX(a,b) (((a)>(b))?(a):(b))
#define MAX_DEGREE 101
#define MAX_TERMS 101
typedef struct {
	float coef;
	int expon;
} polynomial2;
polynomial2 terms[MAX_TERMS] = { { 8,3 },{ 7,1 },{ 1,0 },{ 10,3 },{ 3,2 },{ 1,0 } };
int avail = 6;

typedef struct { 
	int degree;
	float coef[MAX_DEGREE];
} polynomial;

//다항식 1

polynomial poly_add1(polynomial A, polynomial B)
{
	polynomial C;
	int Apos = 0, Bpos = 0, Cpos = 0;
	int degree_a = A.degree;
	int degree_b = B.degree;
	C.degree = MAX(A.degree, B.degree); 
	while (Apos <= A.degree && Bpos <= B.degree) {
		if (degree_a > degree_b) { 
			C.coef[Cpos++] = A.coef[Apos++];
			degree_a--;
		}
		else if (degree_a == degree_b) {
			C.coef[Cpos++] = A.coef[Apos++] + B.coef[Bpos++];
			degree_a--;
			degree_b--;
		}
		else {
			C.coef[Cpos++] = B.coef[Bpos++];
			degree_b--;
		}
	}
	return C;
}

polynomial poly_sub1(polynomial A, polynomial B)
{
	polynomial C;
	int Apos = 0, Bpos = 0, Cpos = 0;
	int degree_a = A.degree;
	int degree_b = B.degree;
	C.degree = MAX(A.degree, B.degree);
	while (Apos <= A.degree && Bpos <= B.degree) {
		if (degree_a > degree_b) {
			C.coef[Cpos++] = A.coef[Apos++];
			degree_a--;
		}
		else if (degree_a == degree_b) {
			C.coef[Cpos++] = A.coef[Apos++] - B.coef[Bpos++];
			degree_a--;
			degree_b--;
		}
		else {
			C.coef[Cpos++] = B.coef[Bpos++];
			degree_b--;
		}
	}
	return C;
}

void printad_poly(polynomial p)
{
	for (int i = p.degree; i > 0; i--)
		printf("%3.1fx^%d + ", p.coef[p.degree - i], i);
	printf("%3.1f \n", p.coef[p.degree]);
}

void printsb_poly(polynomial p)
{
	for (int i = p.degree; i > 0; i--) {
		printf("%3.1fx^%d ", p.coef[p.degree - i], i);
		if (p.coef[p.degree - i + 1] >= 0)
			printf(" + ");
	}

	printf("%3.1f \n", p.coef[p.degree]);
}

//다항식 2

char compare(int a, int b)
{
	if (a > b) return '>';
	else if (a == b) return '=';
	else return '<';
}

void attach(float coef, int expon)
{
	if (avail > MAX_TERMS) {
		fprintf(stderr, "항의 개수가 너무 많음\n");
		exit(1);
	}
	terms[avail].coef = coef;
	terms[avail].expon = expon;
	avail++;
}

void poly_add2(int Astart, int Aend, int Bstart, int Bend, int* Cstart, int* Cend) {
	float tempcoef;
	*Cstart = avail;
	while (Astart <= Aend && Bstart <= Bend) {
		switch (compare(terms[Astart].expon, terms[Bstart].expon)) {
		case '>': // A의 차수 > B의 차수
			attach(terms[Astart].coef, terms[Astart].expon);
			Astart++;
			break;
		case '=': // A의 차수 == B의 차수
			tempcoef = terms[Astart].coef + terms[Bstart].coef;
			if (tempcoef)
				attach(tempcoef, terms[Astart].expon);
			Astart++;
			Bstart++;
			break;
		case '<': // A의 차수 < B의 차수
			attach(terms[Bstart].coef, terms[Bstart].expon);
			Bstart++;
			break;
		}
	}
		for (; Astart <= Aend; Astart++)
			attach(terms[Astart].coef, terms[Astart].expon);
		for (; Bstart <= Bend; Bstart++)
			attach(terms[Bstart].coef, terms[Bstart].expon);
		*Cend = avail - 1;
}

void poly_sub2(int Astart, int Aend, int Bstart, int Bend, int* Cstart, int* Cend) {
	float tempcoef;
	*Cstart = avail;
	while (Astart <= Aend && Bstart <= Bend) {
		switch (compare(terms[Astart].expon, terms[Bstart].expon)) {
		case '>': // A의 차수 > B의 차수
			attach(terms[Astart].coef, terms[Astart].expon);
			Astart++;
			break;
		case '=': // A의 차수 == B의 차수
			tempcoef = terms[Astart].coef - terms[Bstart].coef;
			if (tempcoef)
				attach(tempcoef, terms[Astart].expon);
			Astart++;
			Bstart++;
			break;
		case '<': // A의 차수 < B의 차수
			attach(-terms[Bstart].coef, terms[Bstart].expon);
			Bstart++;
			break;
		}
	}
	for (; Astart <= Aend; Astart++)
		attach(terms[Astart].coef, terms[Astart].expon);
	for (; Bstart <= Bend; Bstart++)
		attach(terms[Bstart].coef, terms[Bstart].expon);
	*Cend = avail - 1;
}

void print_poly2(int start, int end)
{
	for (int i = start; i < end; i++)
		printf("%3.1fx^%d + ", terms[i].coef, terms[i].expon);
	printf("%3.1fx^%d\n", terms[end].coef, terms[end].expon);
}

void print_sbpoly2(int start, int end)
{
	for (int i = start; i < end; i++) {
		printf("%3.1fx^%d ", terms[i].coef, terms[i].expon);
		if (terms[i+1].coef >= 0)
			printf("+ ");
	}
	printf("%3.1fx^%d\n", terms[end].coef, terms[end].expon);
}

int main(void) {
	int Astart = 0, Aend = 2, Bstart = 3, Bend = 5, Cstart, Cend;
	poly_sub2(Astart, Aend, Bstart, Bend, &Cstart, &Cend);
	print_sbpoly2(Astart, Aend);
	print_sbpoly2(Bstart, Bend);
	printf("-----------------------------------------------------------------------------\n");
	print_sbpoly2(Cstart, Cend);
	return 0;
}