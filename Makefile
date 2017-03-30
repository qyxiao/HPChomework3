CC=mpicc 

EXECS= ring arr_ring

all: ${EXECS}

ring: int_ring.c
	${CC}  $^ -o int_ring


arr_ring: arr_ring.c
	${CC}  $^ -o arr_ring


clean:
	rm -f ${EXECS}