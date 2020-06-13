#include "header.h"
int main(int argc, char *argv[]) {
  
 	igraph_t g;
	int *height;	
	clock_t t,e; 
    printf("Push Relabel"); 
 	 igraph_integer_t eid,from,to,value,vid,eid1,flow,source,sink;
 	 igraph_i_set_attribute_table(&igraph_cattribute_table);
	 FILE *fp6;
 	 FILE *fp=fopen(argv[1],"r"); 
 	 if(!fp)
 	 {
	
		perror("file does not exist\n");
		exit(1);
 	 }
	 //printf("Good");
 	 igraph_read_graph_edgelist(&g, fp, 0, IGRAPH_DIRECTED);
 	 fclose(fp);
	 height=(int*)calloc(igraph_vcount(&g),sizeof(int));
 	 fp=fopen(argv[2],"r");
 	 if(!fp)
 	 {
		perror("file does not exist\n");
		exit(1);

 	 }
	  
	 sscanf(argv[3],"%d",&source);
	 sscanf(argv[4],"%d",&sink);
	 //printf("Good");
	 for(vid=0;vid<igraph_vcount(&g);vid++)
	 {
	      igraph_cattribute_VAS_set(&g,"type",vid,"normal");
	       height[vid]=0;
	 }
         igraph_cattribute_VAS_set(&g,"type",source,"source");
	 igraph_cattribute_VAS_set(&g,"type",sink,"sink");

	 height[source]=igraph_vcount(&g);
	
         
	 
	 

 	 for(eid=0;eid<igraph_ecount(&g);eid++)
 	 {
	
		fscanf(fp,"%d %d",&flow,&value);
 	        igraph_edge(&g, eid, &from, &to);
	//	printf("eid=%d, %d, %d\n",eid,from,to);
 	 	igraph_cattribute_EAN_set(&g,"weight",eid,value);
	//	printf("val=%d\n",(int)igraph_cattribute_EAN(&g, "weight",eid));

				
	    	
	        igraph_cattribute_EAN_set(&g,"flow",eid,flow);            
		

 	 }
 	     
	 for(vid=0;vid<igraph_vcount(&g);vid++)
	 {
		
		igraph_cattribute_VAN_set(&g,"excess",vid,0);
		
		
		
	 }
	 sscanf(argv[5],"%d",&value);   
	 igraph_cattribute_VAN_set(&g,"excess",source,value);     	  	       
	// printf("excess=%d\t",(igraph_integer_t)igraph_cattribute_VAN(&g,"excess",source));    
/*	for(vid=0;vid<igraph_vcount(&g);vid++)
		printf("%d,%d\t",height[vid],(igraph_integer_t)igraph_cattribute_VAN(&g,"excess",vid));*/
        t = clock();    
 	main_func(&g,height,source,sink);
	e=clock();
	double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds 
	fp6=fopen(argv[6],"a");  
        fprintf(fp6,"%d %d %d %d %s %f ",source,sink,igraph_vcount(&g),igraph_ecount(&g),argv[5],time_taken); 
	if(igraph_cattribute_VAN(&g,"excess",sink)==atoi(argv[5]))
	    fprintf(fp6," %s\n","success!!!!\n");
        else
	    fprintf(fp6," %s\n","failure");
/*	 for(eid=0;eid<igraph_ecount(&g);eid++)
         {
            igraph_edge(&g,eid,&from,&to);
	    printf("flow=%d %d %d\n",from,to,(igraph_integer_t)igraph_cattribute_EAN(&g,"flow",eid));
         }
	 for(vid=0;vid<igraph_vcount(&g);vid++)
		printf("%d,%d\t",height[vid],(igraph_integer_t)igraph_cattribute_VAN(&g,"excess",vid));*/
	 fclose(fp6);
 	 return 0;
}
