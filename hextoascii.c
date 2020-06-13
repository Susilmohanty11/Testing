#include <stdio.h>
#include <string.h>

int hex_to_int(char c){
        int first = c / 16 - 3;
        int second = c % 16;
        int result = first*10 + second;
        if(result > 9) result--;
        return result;
}

int hex_to_ascii(char c, char d){
        int high = hex_to_int(c) * 16;
        int low = hex_to_int(d);
        return high+low;
}

char *main_ascii(char *st){
        //const char* st = "48656C6C6F3B";
        int length = strlen(st);
	printf("ll%d\n",length);
        int i,j=0;
        char buf = 0;
        char *string_print;
	string_print=(char *)malloc(100*sizeof(char));
        for(i = 0; i < length; i++){
                if(i % 2 != 0){
                        //printf("%c", hex_to_ascii(buf, st[i]));
			string_print[j]=hex_to_ascii(buf, st[i]);
                        j++;
                }else{
                        buf = st[i];
                }
        }
	printf("%d",j);
	string_print[j]='\0';
	//printf("\n%s,%d\n",string_print,(int)strlen(string_print));
	return string_print;
}
