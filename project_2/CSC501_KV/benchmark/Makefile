all: benchmark validate

benchmark: benchmark.c
	$(CC) -g -O0 benchmark.c -o benchmark -lckv -lpthread
	$(CC) -g -O0 benchmark3.c -o benchmark3 -lckv -lpthread
validate: validate.c
	$(CC) -g -O0 validate.c -o validate -lckv
clean:
	rm -f benchmark validate
