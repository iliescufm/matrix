/*
matlab.c
v2.0

gcc matlab.c Validate.c Collection.c Matrix.c Radix.c PowerMatrix.c strassenMultiply.c MultiplicateMatrix.c -g -O0 -o matlab
valgrind --leak-check=yes -s ./matlab
*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Validate.h"
#include "Matrix.h"
#include "Collection.h"
#include "Radix.h"
#include "Exponent.h"
#include "PowerMatrix.h"
#include "strassenMultiply.h"
#include "MultiplicateMatrix.h"
# define D 1 // debug messages: 0 - no, 1 -yes 
# define P 1 // command prompt: 0 - no, 1 -yes
 
int main(void)
{
	int qz = 0; // nr de matrici adaugate in colectie
    int qk = 1; // capacitatea colectiei
	int *ql; // vectorul ce retine dimensiunile liniilor
	int *qc;
	int *sum = malloc(qk * sizeof(int)); // suma fiecarei matrici din colectie
	int *top = malloc(qk * sizeof(int));// clasament cu pozitia din colectie

    // folosim un resizable array pentru a reprezenta o colectie de matrici
    int ***q = malloc(qk * sizeof(int**));

	int **a;
    ql = malloc(qk * sizeof(int));
    qc = malloc(qk * sizeof(int));
	int l, c, k, k1, k2, p;


	char key = '\0';

 	while(1) {
		int ok = 0;
		if (key != '\n' && key != '\r') if (P) printf("> ");
			scanf("%c", &key);
		
		if (key == 'a') {
			ok = D;
			if (D) printf("q qz #%d qk /%d/ Address [%p]\n", qz, qk, (void *)q);
		}
 
		if (key == 'q') {
			ok = D;
			if (D){
				printf("q Vectors\n");
				infoVector("ql: ",ql,qz,0);
				infoVector("qc: ",qc,qz,0);
			}
		}

		if (key == 'p') {
			ok = D;
			if (D) {
				sum = realloc(sum, qz * sizeof(int));
				for (int i = 0; i < qz; i++) { sum[i] = sumMatrix(q[i], ql[i], qc[i]); }
				printCollectionandSum(q,qz,ql,qc,sum);
			}

			}

		if (key == 'L') {
			ok = 1;
			if (D) printf("Încărcarea în memorie a unei matrice\n");
			scanf("%d%d", &l, &c);
			a = readMatrixforKeyboard(l,c);
			if (qz == qk){
				qk = qk * 2;
		        q = (void *)realloc(q, qk * sizeof(int**));
				ql = realloc(ql, qk * sizeof(int));
				qc = realloc(qc, qk * sizeof(int));
			}

			addMatrixtoCube(q, &qz, ql, qc, a, l, c);	
			freeMatrix(a,l);

		}
		if (key == 'D') {
			ok = 1;
			if (D) printf("Determinarea dimensiunilor unei matrice\n");
			scanf("%d", &k);
			if (validateIndex(k, qz)) { printf("%d %d\n", ql[k], qc[k]); 	}
		}
		if (key == 'P') {
			ok = 1;
			if (D) printf("Afisarea unei matrice\n");
			scanf("%d", &k);
			if (validateIndex(k, qz)) { printMatrix(q[k], ql[k], qc[k]); }
		}
		if (key == 'C') {
			ok = 1;
			if (D) printf("Redimensionarea unei matrice\n");
			scanf("%d", &k);
			if (validateIndex(k, qz)) {
				int lx, cx;
				scanf("%d", &lx); // nr de linii
				int li[lx];
				for(int i = 0; i < lx; i++) { scanf("%d", &li[i]);	}
				scanf("%d", &cx); // nr de coloane
				int ci[cx];
				for(int i = 0; i < cx; i++) { scanf("%d", &ci[i]);	}
				q[k] = cutMatrix(q[k], &ql[k], &qc[k], lx, li, cx, ci);
 			}
		}
		if (key == 'M') {
			ok = 1;
			if (D) printf("Înmultirea a două matrice\n");
			scanf("%d%d", &k1, &k2);

			//validarea de mutat in functia 
			if (validateIndex(k1, qz) && validateIndex(k2, qz)) {
 					a = newMatrixMultiplicate(q[k1], ql[k1], qc[k1], q[k2], ql[k2], qc[k2]);
					l = ql[k1];
					c = qc[k2];

					if (a != NULL) {

						if (qz == qk) {
							qk = qk * 2;
							q = (void *)realloc(q, qk * sizeof(int**));
							ql = realloc(ql, qk * sizeof(int));
							qc = realloc(qc, qk * sizeof(int));
						}
						ql[qz] = l;
						qc[qz] = c;

					addMatrixtoCube(q, &qz, ql, qc, a, l, c);	
					freeMatrix(a,l);

					}
				}
			
		}
		if (key == 'O') {
			ok = 1;
			if (D) printf("Sortarea matricelor\n");
			sum = realloc(sum, qz * sizeof(int));
			top = realloc(top, qz * sizeof(int));
			for (int i = 0; i < qz; i++) { sum[i] = sumMatrix(q[i], ql[i], qc[i]); }
			sortVector(sum, qz, top);
			q = sortCube(q, qk, qz, ql, qc, top);
		}
		if (key == 'T') {
			ok = 1;
			if (D) printf("Transpunerea unei matrice\n");
			scanf("%d", &k);
			if (validateIndex(k, qz)) {
				q[k] = transposeMatrix(q[k], &ql[k], &qc[k]);
			}
		}
		if (key == 'R') {
			ok = 1;
			if (D) printf("Ridicarea unei matrice la o putere în timp logaritmic\n");
			scanf("%d%d", &k, &p);
			if (validateIndex(k, qz)) {
				powerMatrix(q[k], ql[k], ql[k], p);
			}
			// (!) nu face modulo
		}
		if (key == 'F') { ok = 1;
			if (D) printf("Eliberarea memoriei unei matrice\n");
			int ki;
			scanf("%d", &ki);
			if (validateIndex(ki, qz)) {

				int* qlo = malloc(qz * sizeof(int));
				int* qco = malloc(qz * sizeof(int));

				for (int i = 0; i < qz; i ++){

					qlo[i]=ql[i];
					qco[i]=ql[i];
				}
				int ***w;
				//w = deleteMatrixfromCollection(q, &qz, ql, qc, k);
				int nz = qz - 0;
				if (nz == 0) {
					if (D) printf("Empty collection. Really!?\n");
				}
				else {
					int ka = 0;
					w = malloc((qk) * sizeof(int**));

					for (k = 0; k < qz; k++) {
						if (k != ki) { 
							ql[ka] = ql[k];
							qc[ka] = qc[k];
							w[ka]=malloc(ql[k] * sizeof(int*));
							for (int i = 0; i < ql[k]; i++) {
								w[ka][i] = malloc(qc[k] * sizeof(int));
								for (int j = 0; j < qc[k]; j++)
									w[ka][i][j] = q[k][i][j];
								}
						ka++;
						}
						}
					qz = qz - 1;
					freeCube(q,qz+1,qlo,qco);
					free(q);
					free(qlo);
					free(qco);
					q = w;

				}

			}
		}
		if (key == 'Q') {	ok = 1; 
			if (D) printf("Eliberarea tuturor resurselor\n");

			freeCollection(q, qz, ql, qc);
			free(sum);
			free(top);
			free(ql);
			free(qc);
 
			break;
		}
		if (key == 'S') { ok = 1;
			if (D) printf("Înmultirea matricelor folosind algoritmul lui Strassen\n");
			scanf("%d%d", &k1, &k2);
			if (validateIndex(k1, qz) && validateIndex(k2, qz)) {
				if (validateSizeOfMatrix(k1, k2, ql, qc) != 0) {
					l = ql[k2];
					a = initAllocMatrix(l,l,-1);
					strassenMultiply(q[k1], q[k2], a, l);
					
					if (qz == qk) {
						qk = qk * 2;
						q = (void *)realloc(q, qk * sizeof(int**));
						ql = realloc(ql, qk * sizeof(int));
						qc = realloc(qc, qk * sizeof(int));
					}
					ql[qz] = l;
					qc[qz] = l;

					addMatrixtoCube(q, &qz, ql, qc, a, l, l);	
					freeMatrix(a,l);
				}

				// int **mp = strassen(q[k1],ql[k1],qc[k1],q[k2],ql[k2],qc[k2]);
				// if (D) printMatrix(mp,ql[k1],qc[k1]);
				// if (qz == qk){
				// 	ql = realloc(ql, 2 * qk * sizeof(int));
				// 	qc = realloc(qc, 2 * qk * sizeof(int));
				// 	}
				// addMatrixtoCube(q, &qz, ql, qc, mp,ql[k1],qc[k1]);
			}
		}
		if (ok == 0) if (key != '\n' && key != '\r') printf("Unrecognized command\n");
	}

	return 0;
}