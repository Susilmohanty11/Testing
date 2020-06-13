#include <igraph.h>
#include <stdio.h>
#include <time.h>
typedef struct num{
   igraph_integer_t vid;
   igraph_integer_t deg;
}array_list;

void sort(array_list *array, igraph_integer_t count)
{
      igraph_integer_t i,j,temp1,temp2;

   	for(i=0;i<count-1;i++)
         {
        //                  printf("vid,i: %d,%d,%d\n",array[i].vid,i,array[i].deg);
		for(j=i+1;j<count;j++)
		{
			if(array[i].deg<array[j].deg)
			{
				temp1=array[i].deg;
				temp2=array[i].vid;
				array[i].deg=array[j].deg;
				array[i].vid=array[j].vid;
                                
                                array[j].deg=temp1;			
                                array[j].vid=temp2;
        
			}
		}
//            printf("vid,i: %d,%d,%d\n",array[i].vid,i,array[i].deg);

           }

}
int main(int argc,char *argv[]){


    int num_nodes;
	
    igraph_t g;
    igraph_integer_t from,to,eid,vid,cap,eid1,result,track;
    igraph_vector_t res;
    igraph_vs_t vs;
    igraph_vit_t vit;
    FILE *fp=fopen(argv[2],"w");
    FILE *out=fopen(argv[3],"w");
    FILE *read;
    FILE *fp1=fopen(argv[4],"w");
    FILE *gtna=fopen(argv[5],"w");
    FILE *fp2=fopen(argv[6],"w");
    FILE *fp3=fopen(argv[7],"w");
    igraph_i_set_attribute_table(&igraph_cattribute_table);
    num_nodes=atoi(argv[1]);
    srand(time(NULL));
    igraph_t graph;	
   
    igraph_barabasi_game(&graph,num_nodes, /*power=*/ 1, 4, NULL, 1, /*A=*/ 1, IGRAPH_DIRECTED, IGRAPH_BARABASI_PSUMTREE, /*start_from=*/ NULL);
    //printf("%d\n",igraph_ecount(&graph));	
    
    int val=igraph_ecount(&graph);
    fprintf(fp2,"%s","# Graph Property Class\ntreeembedding.credit.CreditLinks\n# Key\nCREDIT_LINKS\n");
	
    for(eid=0;eid<val;eid++)
    {
	igraph_edge(&graph,eid,&from,&to);	
	
        if(eid%4==0) 
         cap=(rand() % 10) + 15; 
        else if(eid%5==0)
           cap=(rand() % 5) + 7;
        else if(eid%7==0)
           cap=(rand() % 10) + 6;
        else if(eid%3==0)
            cap=(rand() % 8) + 8;
        else
           cap=(rand() % 7) + 15;
         	fprintf(fp2,"%d %d -0.0 0.0 %d.0\n",to,from,cap);
          //     fprintf(fp2,"%d %d -0.0 %d.0 0.0\n",from,to,cap);
	igraph_add_edge(&graph,to,from);
       
        igraph_get_eid(&graph,&eid1,to,from,IGRAPH_DIRECTED,1);
	igraph_cattribute_EAN_set(&graph,"weight",eid,cap);
	igraph_cattribute_EAN_set(&graph,"weight",eid1,cap);
	igraph_cattribute_EAN_set(&graph,"flow",eid,cap);  
	igraph_cattribute_EAN_set(&graph,"flow",eid1,0);
    }
    fclose(fp2);
    igraph_write_graph_graphml(&graph,fp,0); 
    igraph_write_graph_edgelist(&graph, out);
    for(eid=0;eid<igraph_ecount(&graph);eid++)
    {
	igraph_edge(&graph,eid,&from,&to);
	igraph_get_eid(&graph,&eid1,from,to,IGRAPH_DIRECTED,1);
	//printf("%d %d %d %d\n",from,to,(igraph_integer_t)igraph_cattribute_EAN(&graph,"flow",eid1),(igraph_integer_t)igraph_cattribute_EAN(&graph,"weight",eid1));	

    }
   
    fclose(out);
    //igraph_destroy(&graph);
    read=fopen(argv[3],"r");
    igraph_read_graph_edgelist(&g,read,0,IGRAPH_DIRECTED);
 //   printf("%s %d",argv[3],igraph_ecount(&g));
    for(eid=0;eid<igraph_ecount(&g);eid++)
    {
	igraph_edge(&g,eid,&from,&to);
	igraph_get_eid(&graph,&eid1,from,to,IGRAPH_DIRECTED,1);
	fprintf(fp1,"%d %d\n",(igraph_integer_t)igraph_cattribute_EAN(&graph,"flow",eid1),(igraph_integer_t)igraph_cattribute_EAN(&graph,"weight",eid1));	

    }
    fprintf(gtna,"# Name of the Graph: \ncredit network basic \n# Number of Nodes:\n%d \n# Number of Edges: \n%d \n",igraph_vcount(&g),igraph_ecount(&g));
    array_list *list=(array_list*)malloc(igraph_vcount(&g)*sizeof(array_list));
    for(vid=0;vid<igraph_vcount(&g);vid++)
  {
	fprintf(gtna,"\n%d:",vid);
	igraph_vs_adj(&vs,vid,IGRAPH_OUT);
        igraph_vs_size(&g,&vs,&result);
        
	list[vid].vid=vid;
	list[vid].deg=result;
        igraph_vit_create(&g, vs, &vit);
        for (; !IGRAPH_VIT_END(vit); IGRAPH_VIT_NEXT(vit)) {
    		fprintf(gtna,"%li;", (long int) IGRAPH_VIT_GET(vit));
        }

	igraph_vs_destroy(&vs);	
         igraph_vit_destroy(&vit);

}   
      
    sort(list,igraph_vcount(&g));  
    track=list[0].deg;
    for(vid=0;vid<igraph_vcount(&g);vid++)
    {

        if(track!=list[vid].deg)
	{
	    fprintf(fp3,"%s","\n");	
            track=list[vid].deg;
        }
         fprintf(fp3,"%d ",list[vid].vid);
    }
    fclose(fp);
    fclose(fp1);
    
    return 0;

}
