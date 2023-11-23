//gcc matlab.c Radix.c PowerMatrix.c Strassen.c Matrix.c MultiplicateMatrix.c Collection.c Validate.c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Validate.h"
#include "Matrix.h"
#include "Collection.h"
#include "Radix.h"
#include "Exponent.h"
#include "PowerMatrix.h"
#include "Strassen.h"
#include "MultiplicateMatrix.h"
# define D 1 // debug messages: 0 - no, 1 -yes 
# define P 1 // command prompt: 0 - no, 1 -yes
 
int main(void)
{
	int size = 0; // nr de matrici adaugate in colectie
    int capa = 1; // capacitatea colectiei
	int *ql; // vectorul ce retine dimensiunile liniilor
	int *qc;
	int *sum = malloc(20 * sizeof(int)); // suma fiecarei matrici din colectie
	int *top = malloc(20 * sizeof(int));// clasament cu pozitia din colectie
    // folosim un resizable array pentru a reprezenta o colectie de matrici
    int ***collection = malloc(capa * sizeof(int**));
    int **matrix; // matricile din colectie
	int **b;
    ql = malloc(capa * sizeof(int));
    qc = malloc(capa * sizeof(int));
	int nl, nc, k, k1, k2, p;
 
 	while(1) {
		int ok = 0;
		char c;
		if (c != '\n' && c != '\r') if (P) printf("> ");
			scanf("%c", &c);
		
		if (c == 'a') {
			ok = D;
			if (D) printf("Collection Size #%d Capacity /%d/ Address [%p]\n", size, capa, (void *)collection);
		}
 
		if (c == 'q') {
			ok = D;
			if (D){
				printf("Collection Vectors\n");
				infoVector("ql: ",ql,size,0);
				infoVector("qc: ",qc,size,0);
			}
		}

		if (c == 'p') {
			ok = D;
			if (D) printCollection(collection,size,ql,qc);
		}

		if (c == 'L') {
			ok = 1;
			if (D) printf("Încărcarea în memorie a unei matrice\n");
			scanf("%d%d", &ql[size], &qc[size]);
			b = readMatrixforKeyboard(ql[size],qc[size]);
			if (size == capa){
				ql = realloc(ql, 2 * capa * sizeof(int));
				qc = realloc(qc, 2 * capa * sizeof(int));
			}

			collection = appendMatrixtoCollection(collection, &size, &capa, ql, qc, b, ql[size], qc[size]);	
		}
		if (c == 'D') {
			ok = 1;
			if (D) printf("Determinarea dimensiunilor unei matrice\n");
			scanf("%d", &k);
			if (validateIndex(k, size)) { printf("%d %d\n", ql[k], qc[k]); 	}
		}
		if (c == 'P') {
			ok = 1;
			if (D) printf("Afisarea unei matrice\n");
			scanf("%d", &k);
			if (validateIndex(k, size)) { printMatrix(collection[k], ql[k], qc[k]); }
		}
		if (c == 'C') {
			ok = 1;
			if (D) printf("Redimensionarea unei matrice\n");
			scanf("%d", &k);
			if (validateIndex(k, size)) {
				int lx, cx;
				scanf("%d", &lx); // nr de linii
				int li[lx];
				for(int i = 0; i < lx; i++) { scanf("%d", &li[i]);	}
				scanf("%d", &cx); // nr de coloane
				int ci[cx];
				for(int i = 0; i < cx; i++) { scanf("%d", &ci[i]);	}
				collection[k] = cutMatrix(collection[k], &ql[k], &qc[k], lx, li, cx, ci);
 			}
		}
		if (c == 'M') {
			ok = 1;
			if (D) printf("Înmultirea a două matrice\n");
			scanf("%d%d", &k1, &k2);

			//validarea de mutat in functia 
			if (validateIndex(k1, size) && validateIndex(k2, size)) {
 				if(multiplicateMatrix(collection[k1], ql[k1], qc[k1], collection[k2], ql[k2], qc[k2]) != 0) {
 					matrix = multiplicateMatrix(collection[k1], ql[k1], qc[k1], collection[k2], ql[k2], qc[k2]);
					nl = ql[k1];
					nc = qc[k2];

					//TODO
					//nu mai este necesar, appendMatrixtoCollection dubleaza capacitatea daca nu mai e loc
					if (size == capa) {
						ql = resizeVector(ql, capa, capa * 2);
						qc = resizeVector(qc, capa, capa * 2);
						collection = resizeCollectionCapacity(collection, capa, capa * 2, ql, qc);
						capa = capa * 2;
					}
					ql[size] = nl;
					qc[size] = nc;
					
					//TODO
					//de folosit noua functie de mai jos pentru adaugarea in colectie
					//collection = appendMatrixtoCollection(collection, &size, &capa, ql, qc, mp,ql[k1],qc[k1]);

					collection = addMatrixtoCollection(collection, &size, ql, qc, matrix, ql[size], qc[size]);	
					freeMatrix(matrix, ql[size - 1]);
				}
			}
		}
		if (c == 'O') {
			ok = 1;
			if (D) printf("Sortarea matricelor\n");
			for(int i = 0; i < size; i++) { sum[i] = sumMatrix(collection[i], ql[i], qc[i]); }
			top = sortVector(sum, size);
			collection = sortCollection(collection, size, ql, qc, top);
		}
		if (c == 'T') {
			ok = 1;
			if (D) printf("Transpunerea unei matrice\n");
			scanf("%d", &k);
			if (validateIndex(k, size)) {
				collection[k] = transposeMatrix(collection[k], &ql[k], &qc[k]);
			}
		}
		if (c == 'R') {
			ok = 1;
			if (D) printf("Ridicarea unei matrice la o putere în timp logaritmic\n");
			scanf("%d%d", &k, &p);
			if (validateIndex(k, size)) {
					powerMatrix(collection[k], ql[k], p);
				}
		}
		if (c == 'F') { ok = 1;
			if (D) printf("Eliberarea memoriei unei matrice\n");
			scanf("%d", &k);
			if (validateIndex(k, size)) {
				collection = deleteMatrixfromCollection(collection, &size, ql, qc, k);
			}
		}
		if (c == 'Q') {	ok = 1; 
			if (D) printf("Eliberarea tuturor resurselor\n");
			// freeCollection(collection, size, ql, qc);
			break;
		}
		if (c == 'S') { ok = 1;
			if (D) printf("Înmultirea matricelor folosind algoritmul lui Strassen\n");
			scanf("%d%d", &k1, &k2);
			if (validateIndex(k1, size) && validateIndex(k2, size)) {
				int **mp = strassen(collection[k1],ql[k1],qc[k1],collection[k2],ql[k2],qc[k2]);
				if (D) printMatrix(mp,ql[k1],qc[k1]);
				if (size == capa){
					ql = realloc(ql, 2 * capa * sizeof(int));
					qc = realloc(qc, 2 * capa * sizeof(int));
					}
				collection = appendMatrixtoCollection(collection, &size, &capa, ql, qc, mp,ql[k1],qc[k1]);
			}
		}
		if (ok == 0) if (c != '\n' && c != '\r') printf("Unrecognized command\n");
	}
	printCollection(collection, size, ql, qc); 
	freeCollection(collection, size, ql, qc);
 
	return 0;
}