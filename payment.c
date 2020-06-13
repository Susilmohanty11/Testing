#include "header.h"
void payment(igraph_t *g, int *height, igraph_integer_t source, igraph_integer_t sink, unsigned long int *totalBytes)
{    
    unsigned char **buffer;
    int *bfs_edge_marker;
	//unsigned long int totalBytes = 0;	
    int size_text = 32;
	int vid;
    buffer = (unsigned char**)malloc(igraph_vcount(g)*sizeof(unsigned char*));
	bfs_edge_marker = (int*)calloc(igraph_ecount(g), sizeof(int));

    for(vid = 0; vid < igraph_vcount(g); vid++)
	{
        buffer[vid] = (char*)malloc(40*sizeof(char));
		if(height[vid] > 0)
		{
        	gcry_randomize(buffer[vid], size_text, GCRY_VERY_STRONG_RANDOM);  // libgcrypto library
			*totalBytes += strlen(buffer[vid]);       
			//secret : 32 bytes
        	// printf("secret = %s,vid = %d\n", buffer[vid], vid);
			// sprintf(strip,"./mp p \"%s\" outp.txt", buffer[vid]);
			// system(strip);					 
		}
	}
          
	/*buffer[sink]=(unsigned char*)malloc(size_text*sizeof(unsigned char));
	*totalBytes+=sizeof(buffer[sink]);		
	gcry_randomize(buffer[sink],32,GCRY_VERY_STRONG_RANDOM);         
    buffer[source]=(unsigned char*)malloc(size_text*sizeof(unsigned char));
	*totalBytes+=sizeof(buffer[source]);		
	gcry_randomize(buffer[source],32,GCRY_VERY_STRONG_RANDOM);         
	//secret : 32 bytes*/
        
    bfs_mark(g, bfs_edge_marker, height, source, sink, buffer, totalBytes);
}

