#include <mpi.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
   char idstr[32];
   char buff[128];
   char hostname[60];
   int numprocs;
   int myid;
   int i;
   MPI_Status stat;
   MPI_Init(&argc,&argv);
   MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
   MPI_Comm_rank(MPI_COMM_WORLD,&myid);
   if(myid == 0)
   {
    	gethostname(hostname, 50);
        printf("Tenim %d processadors, jo sóc el proces mestre :%d a la maquina:%s\n", numprocs,myid,hostname);
        for(i=1;i<numprocs;i++)
        {
          sprintf(buff, "¡Holaaa %d! ", i);
          MPI_Send(buff, 128, MPI_CHAR, i, 0, MPI_COMM_WORLD);
        }
        for(i=1;i<numprocs;i++)
        {       
          MPI_Recv(buff, 128, MPI_CHAR, i, 0, MPI_COMM_WORLD, &stat);
          printf("%s\n", buff);
        }
    }
    else
    {
        gethostname(hostname, 50);
        MPI_Recv(buff, 128, MPI_CHAR, 0, 0, MPI_COMM_WORLD, &stat);
        sprintf(idstr, "Processador %d de la maquina:%s ", myid,hostname);
        strcat(buff, idstr);
        strcat(buff, "report");
        MPI_Send(buff, 128, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
	}

	MPI_Finalize();
	return 0;
}
