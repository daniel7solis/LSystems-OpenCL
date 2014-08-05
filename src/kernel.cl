__kernel void kernel1(__global const char *sym,__global char *P,__global int *cantP,__global int *result){
	int gid = get_global_id(0);
	
	//printf("\ngid: %i",gid);
	result[gid]=-1;
	for(int i=0; i<cantP[0]; i++){
		//printf("\n%c y el sym es: %c",P[i],sym[gid]);
		if(sym[gid]==P[i]){
			result[gid]=i;
			//printf("se encontro el simbolo");
			//printf("%i",i);
		}
	}
}
