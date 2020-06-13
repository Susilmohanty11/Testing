#gcc -I/home/abriti/workbench/openssl/src  -fopenmp -o mp MPC_SHA256.c -lcrypto

#gcc push_test.c func.c lift.c min.c preflow.c approve_push.c bfs.c payment.c create_puzzle.c solve.c -I/home/abriti/Desktop/Payment_Channels/igraph-0.7.1/include -I/home/abriti/Desktop/gocode/Code_Push_relabel/libgcrypt-1.8.4/src -I/home/abriti/workbench/openssl/src -L/usr/local/lib -fopenmp -ligraph -lgcrypt -lcrypt -o push_relabel 

#./push_relabel test_input.txt test_weight.txt output_file.txt 0 4 node_10/sampleTr-0.txt 
gcc push_test.c func.c lift.c min.c preflow.c approve_push.c bfs.c payment.c create_puzzle.c solve.c -I/home/cssc/Desktop/igraph-0.7.1/include -I/home/cssc/Desktop/openssl-1.0.2o/ -I/home/cssc/Desktop/libgcrypt-1.8.4/src -I/home/abriti/workbench/openssl/src -L/usr/local/lib -fopenmp -ligraph -lgcrypt -lcrypto -o push_relabel 




for((i=10000;i<=40000;i*=2))
do
 # count=0;
  #flag=0;
  for((j=0;flag==0 && j<i;j++))
  do
    for((k=0;flag==0 && k<i; k++)) 
    do
    if(($k<=$j))
     then
       continue
    fi
  
     
    ./push_relabel node_$i/read_graph_edge_$i.txt node_$i/read_graph_weight_$i.txt output_new.txt $j $k node_$i/sampleTr-0.txt
    
     #echo $val.00 $j $k >> output_file.txt
     count=$(($count+1));
     if(($count==20))
      then
         flag=1;
         break;
     fi
    done
  done
  flag=0;
  count=0;
  echo "\n" >> output_new.txt
done
