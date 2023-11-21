for (k = 0; k < z; k++) {
	printf("a[%d]=malloc(%d * sizeof(int*))\n",k,ql[top[k]]);
	for (i = 0; i < ql[top[k]]; i++) {
		printf("a[%d][%d] = malloc(%d * sizeof(int))\n",k,i,qc[top[k]]);
			for (j = 0; j < qc[top[k]]; j++){
					printf("a[%d][%d][%d] = %d\n",k,i,j,q[top[k]][i][j]);
			}
	}
}