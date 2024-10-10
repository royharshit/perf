#include <unistd.h>
#include <asm/unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <sys/ioctl.h>
#include <sys/syscall.h>
#include <linux/perf_event.h>


const size_t memsize = 1024*1024*1024;
const size_t elems = memsize / sizeof(uint32_t);
const int DISTANCE = 32;

static long perf_event_open(struct perf_event_attr *hw_event, pid_t pid, int cpu, int group_fd, unsigned long flags) {
    return syscall(__NR_perf_event_open, hw_event, pid, cpu, group_fd, flags);
}

uint32_t hash(uint32_t data) {
    return 9*data % 17;
}

uint32_t time_nonprefetch_h0(uint32_t** data) {
    uint32_t sum = 0;
    for (uint32_t i = 0; i < elems; i++) {
    	sum += *data[i];
    }
    return sum;
}

uint32_t time_prefetch_h0(uint32_t **data) {
    uint32_t sum = 0;
    for (int i = 0; i < elems - DISTANCE; i++) {
	__builtin_prefetch(data[i + DISTANCE]);
    	sum += *data[i];
    }
    for (int i = elems - DISTANCE; i < elems; i++) {
    	sum += *data[i];
    }
    return sum;
}

uint32_t time_nonprefetch_h1(uint32_t **data) {
    uint32_t sum = 0;
    for (int i = 0; i < elems; i++) {
    	sum += hash(*data[i]);
    }
    return sum;
}

uint32_t time_prefetch_h1(uint32_t **data) {
    uint32_t sum = 0;
    for (int i = 0; i < elems - DISTANCE; i++) {
	__builtin_prefetch(data[i + DISTANCE]);
    	sum += hash(*data[i]);
    }
    for (int i = elems - DISTANCE; i < elems; i++) {
    	sum += hash(*data[i]);
    }
    return sum;
}


uint32_t time_nonprefetch_h2(uint32_t **data) {
    uint32_t sum = 0; 
    for (int i = 0; i < elems; i++) {
    	sum += hash(hash(*data[i]));
    }
    return sum;
}


uint32_t time_prefetch_h2(uint32_t **data) {
    uint32_t sum = 0; 
    for (int i = 0; i < elems - DISTANCE; i++) {
	__builtin_prefetch(data[i + DISTANCE]);
    	sum += hash(hash(*data[i]));
    }
    for (int i = elems - DISTANCE; i < elems; i++) {
    	sum += hash(hash(*data[i]));
    }
    return sum;
}

uint32_t time_nonprefetch_h3(uint32_t **data) {
    uint32_t sum = 0; 
    for (int i = 0; i < elems; i++) {
    	sum += hash(hash(hash(*data[i])));
    }
    return sum;
}


uint32_t time_prefetch_h3(uint32_t **data) {
    uint32_t sum = 0; 
    for (int i = 0; i < elems - DISTANCE; i++) {
	__builtin_prefetch(data[i + DISTANCE]);
    	sum += hash(hash(hash(*data[i])));
    }
    for (int i = elems - DISTANCE; i < elems; i++) {
    	sum += hash(hash(hash(*data[i])));
    }
    return sum;
}


uint32_t time_nonprefetch_h4(uint32_t **data) {
    uint32_t sum = 0; 
    for (int i = 0; i < elems; i++) {
    	sum += hash(hash(hash(hash(*data[i]))));
    }
    return sum;
}


uint32_t time_prefetch_h4(uint32_t **data) {
    uint32_t sum = 0; 
    for (int i = 0; i < elems - DISTANCE; i++) {
	__builtin_prefetch(data[i + DISTANCE]);
    	sum += hash(hash(hash(hash(*data[i]))));
    }
    for (int i = elems - DISTANCE; i < elems; i++) {
    	sum += hash(hash(hash(hash(*data[i]))));
    }
    return sum;
}

uint32_t time_nonprefetch_h5(uint32_t **data) {
    uint32_t sum = 0; 
    for (int i = 0; i < elems; i++) {
    	sum += hash(hash(hash(hash(hash(*data[i])))));
    }
    return sum;
}


uint32_t time_prefetch_h5(uint32_t **data) {
    uint32_t sum = 0; 
    for (int i = 0; i < elems - DISTANCE; i++) {
	__builtin_prefetch(data[i + DISTANCE]);
    	sum += hash(hash(hash(hash(hash(*data[i])))));
    }
    for (int i = elems - DISTANCE; i < elems; i++) {
    	sum += hash(hash(hash(hash(hash(*data[i])))));
    }
    return sum;
}


uint32_t time_nonprefetch_h6(uint32_t **data) {
    uint32_t sum = 0; 
    for (int i = 0; i < elems; i++) {
    	sum += hash(hash(hash(hash(hash(hash(*data[i]))))));
    }
    return sum;
}


uint32_t time_prefetch_h6(uint32_t **data) {
    uint32_t sum = 0; 
    for (int i = 0; i < elems - DISTANCE; i++) {
	__builtin_prefetch(data[i + DISTANCE]);
    	sum += hash(hash(hash(hash(hash(hash(*data[i]))))));
    }
    for (int i = elems - DISTANCE; i < elems; i++) {
    	sum += hash(hash(hash(hash(hash(hash(*data[i]))))));
    }
    return sum;
}


uint32_t time_nonprefetch_h7(uint32_t **data) {
    uint32_t sum = 0; 
    for (int i = 0; i < elems; i++) {
    	sum += hash(hash(hash(hash(hash(hash(hash(*data[i])))))));
    }
    return sum;
}


uint32_t time_prefetch_h7(uint32_t **data) {
    uint32_t sum = 0; 
    for (int i = 0; i < elems - DISTANCE; i++) {
	__builtin_prefetch(data[i + DISTANCE]);
    	sum += hash(hash(hash(hash(hash(hash(hash(*data[i])))))));
    }
    for (int i = elems - DISTANCE; i < elems; i++) {
    	sum += hash(hash(hash(hash(hash(hash(hash(*data[i])))))));
    }
    return sum;
}

uint32_t time_nonprefetch_h8(uint32_t **data) {
    uint32_t sum = 0; 
    for (int i = 0; i < elems; i++) {
    	sum += hash(hash(hash(hash(hash(hash(hash(hash(*data[i]))))))));
    }
    return sum;
}


uint32_t time_prefetch_h8(uint32_t **data) {
    uint32_t sum = 0; 
    for (int i = 0; i < elems - DISTANCE; i++) {
	__builtin_prefetch(data[i + DISTANCE]);
    	sum += hash(hash(hash(hash(hash(hash(hash(hash(*data[i]))))))));
    }
    for (int i = elems - DISTANCE; i < elems; i++) {
    	sum += hash(hash(hash(hash(hash(hash(hash(hash(*data[i]))))))));
    }
    return sum;
}


uint32_t time_nonprefetch_h9(uint32_t **data) {
    uint32_t sum = 0; 
    for (int i = 0; i < elems; i++) {
    	sum += hash(hash(hash(hash(hash(hash(hash(hash(hash(*data[i])))))))));
    }
    return sum;
}


uint32_t time_prefetch_h9(uint32_t **data) {
    uint32_t sum = 0; 
    for (int i = 0; i < elems - DISTANCE; i++) {
	__builtin_prefetch(data[i + DISTANCE]);
    	sum += hash(hash(hash(hash(hash(hash(hash(hash(hash(*data[i])))))))));
    }
    for (int i = elems - DISTANCE; i < elems; i++) {
    	sum += hash(hash(hash(hash(hash(hash(hash(hash(hash(*data[i])))))))));
    }
    return sum;
}

void swap (uint32_t **a, uint32_t **b)
{
    uint32_t* temp = *a;
    *a = *b;
    *b = temp;
}

void randomize (uint32_t **arr, uint32_t n)
{
    srand (time(NULL));
    for (uint32_t i = n - 1; i > 0; i--)
    {
        uint32_t j = rand() % (i + 1);
        swap(&arr[i], &arr[j]);
    }
}

int main() {

    uint32_t* data = (uint32_t*)malloc(memsize);
    uint32_t** data_pointer = (uint32_t**)malloc(elems*sizeof(uint32_t*));
    uint64_t sum1, sum2;

    for (uint32_t i = 0; i < elems; i++) {
    	data[i] = i;
	data_pointer[i] = &data[i];
    }

    randomize(data_pointer, elems);

    struct perf_event_attr pe;
    long long count;
    int fd;

    memset(&pe, 0, sizeof(struct perf_event_attr));
    pe.type = PERF_TYPE_HARDWARE;
    pe.size = sizeof(struct perf_event_attr);
    pe.config = PERF_COUNT_HW_CPU_CYCLES; // Change this to your specific counter
    pe.disabled = 1;
    pe.exclude_kernel = 1;
    pe.exclude_hv = 1;

    fd = perf_event_open(&pe, 0, -1, -1, 0);
    if (fd == -1) {
        fprintf(stderr, "Error opening leader %llx\n", pe.config);
        exit(EXIT_FAILURE);
    }

    int32_t N = 0;

        while (N < 10) { 
            if (N == 0) {
	            printf("Non Prefetch H0\n");
	        	ioctl(fd, PERF_EVENT_IOC_RESET, 0);
            	ioctl(fd, PERF_EVENT_IOC_ENABLE, 0);
	            sum1 = time_nonprefetch_h0(data_pointer);
            	ioctl(fd, PERF_EVENT_IOC_DISABLE, 0);
    		    read(fd, &count, sizeof(long long));
    		    printf("Non Prefetch Counter value: %lld\n", count);
	            printf("Non Prefetch H0 sum %lu\n", sum1);
            }
            if (N == 1) {
	            printf("Non Prefetch H1\n");
	    	    ioctl(fd, PERF_EVENT_IOC_RESET, 0);
            	ioctl(fd, PERF_EVENT_IOC_ENABLE, 0);
                sum1 = time_nonprefetch_h1(data_pointer);
            	ioctl(fd, PERF_EVENT_IOC_DISABLE, 0);
        		read(fd, &count, sizeof(long long));
    	    	printf("Non Prefetch Counter value: %lld\n", count);
	            printf("Non Prefetch H1 sum %lu\n", sum1);
            }
            else if (N == 2) {
	            printf("Non Prefetch H2\n");
	    	    ioctl(fd, PERF_EVENT_IOC_RESET, 0);
            	ioctl(fd, PERF_EVENT_IOC_ENABLE, 0);
                sum1 = time_nonprefetch_h2(data_pointer);
            	ioctl(fd, PERF_EVENT_IOC_DISABLE, 0);
		        read(fd, &count, sizeof(long long));
    		    printf("Non Prefetch Counter value: %lld\n", count);
	            printf("Non Prefetch H2 sum %lu\n", sum1);
	        }
            else if (N == 3) {
	            printf("Non Prefetch H3\n");
	    	    ioctl(fd, PERF_EVENT_IOC_RESET, 0);
            	ioctl(fd, PERF_EVENT_IOC_ENABLE, 0);
                sum1 = time_nonprefetch_h3(data_pointer);
            	ioctl(fd, PERF_EVENT_IOC_DISABLE, 0);
		        read(fd, &count, sizeof(long long));
    		    printf("Non Prefetch Counter value: %lld\n", count);
	            printf("Non Prefetch H3 sum %lu\n", sum1);
    	    }
            else if (N == 4) {
	            printf("Non Prefetch H4\n");
	        	ioctl(fd, PERF_EVENT_IOC_RESET, 0);
            	ioctl(fd, PERF_EVENT_IOC_ENABLE, 0);
                sum1 = time_nonprefetch_h4(data_pointer);
            	ioctl(fd, PERF_EVENT_IOC_DISABLE, 0);
	        	read(fd, &count, sizeof(long long));
    		    printf("Non Prefetch Counter value: %lld\n", count);
	            printf("Non Prefetch H4 sum %lu\n", sum1);
	        }
            else if (N == 5) {
	            printf("Non Prefetch H5\n");
	    	    ioctl(fd, PERF_EVENT_IOC_RESET, 0);
            	ioctl(fd, PERF_EVENT_IOC_ENABLE, 0);
                sum1 = time_nonprefetch_h5(data_pointer);
            	ioctl(fd, PERF_EVENT_IOC_DISABLE, 0);
        		read(fd, &count, sizeof(long long));
    	    	printf("Non Prefetch Counter value: %lld\n", count);
	            printf("Non Prefetch H5 sum %lu\n", sum1);
	        }
            else if (N == 6) {
	            printf("Non Prefetch H6\n");
	    	    ioctl(fd, PERF_EVENT_IOC_RESET, 0);
            	ioctl(fd, PERF_EVENT_IOC_ENABLE, 0);
                sum1 = time_nonprefetch_h6(data_pointer);
            	ioctl(fd, PERF_EVENT_IOC_DISABLE, 0);
		        read(fd, &count, sizeof(long long));
    		    printf("Non Prefetch Counter value: %lld\n", count);
	            printf("Non Prefetch H6 sum %lu\n", sum1);
	        }
            if (N == 7) {
		        printf("Non Prefetch H7\n");
	    	    ioctl(fd, PERF_EVENT_IOC_RESET, 0);
            	ioctl(fd, PERF_EVENT_IOC_ENABLE, 0);
            	sum1 = time_nonprefetch_h7(data_pointer);
            	ioctl(fd, PERF_EVENT_IOC_DISABLE, 0);
		        read(fd, &count, sizeof(long long));
    		    printf("Non Prefetch Counter value: %lld\n", count);
        		printf("Non Prefetch H7 sum %lu\n", sum1);
	        }
            else if (N == 8) {
	            printf("Non Prefetch H8\n");
	    	    ioctl(fd, PERF_EVENT_IOC_RESET, 0);
            	ioctl(fd, PERF_EVENT_IOC_ENABLE, 0);
                sum1 = time_nonprefetch_h8(data_pointer);
            	ioctl(fd, PERF_EVENT_IOC_DISABLE, 0);
		        read(fd, &count, sizeof(long long));
    		    printf("Non Prefetch Counter value: %lld\n", count);
	            printf("Non Prefetch H8 sum %lu\n", sum1);
	        }
            else if (N == 9) {
	            printf("Non Prefetch H9\n");
	    	    ioctl(fd, PERF_EVENT_IOC_RESET, 0);
            	ioctl(fd, PERF_EVENT_IOC_ENABLE, 0);
                sum1 = time_nonprefetch_h9(data_pointer);
            	ioctl(fd, PERF_EVENT_IOC_DISABLE, 0);
	        	read(fd, &count, sizeof(long long));
    		    printf("Non Prefetch Counter value: %lld\n", count);
	            printf("Non Prefetch H9 sum %lu\n", sum1);
	        }
            if (N == 0) {
	            printf("Prefetch H0\n");
	    	    ioctl(fd, PERF_EVENT_IOC_RESET, 0);
            	ioctl(fd, PERF_EVENT_IOC_ENABLE, 0);
            	sum2 = time_prefetch_h0(data_pointer);
            	ioctl(fd, PERF_EVENT_IOC_DISABLE, 0);
		        read(fd, &count, sizeof(long long));
    		    printf("Prefetch Counter value: %lld\n", count);
	            printf("Prefetch H0 sum %lu\n", sum2);
	        }
            if (N == 1) {
	            printf("Prefetch H1\n");
	    	    ioctl(fd, PERF_EVENT_IOC_RESET, 0);
            	ioctl(fd, PERF_EVENT_IOC_ENABLE, 0);
            	sum2 = time_prefetch_h1(data_pointer);
            	ioctl(fd, PERF_EVENT_IOC_DISABLE, 0);
		        read(fd, &count, sizeof(long long));
    		    printf("Prefetch Counter value: %lld\n", count);
	            printf("Prefetch H1 sum %lu\n", sum2);
	        }
            else if (N == 2) {    
	            printf("Prefetch H2\n");
	    	    ioctl(fd, PERF_EVENT_IOC_RESET, 0);
            	ioctl(fd, PERF_EVENT_IOC_ENABLE, 0);
            	sum2 = time_prefetch_h2(data_pointer);
            	ioctl(fd, PERF_EVENT_IOC_DISABLE, 0);
		        read(fd, &count, sizeof(long long));
    		    printf("Prefetch Counter value: %lld\n", count);
	            printf("Prefetch H2 sum %lu\n", sum2);
	        }
            else if (N == 3) {
	            printf("Prefetch H3\n");
	    	    ioctl(fd, PERF_EVENT_IOC_RESET, 0);
            	ioctl(fd, PERF_EVENT_IOC_ENABLE, 0);
            	sum2 = time_prefetch_h3(data_pointer);
            	ioctl(fd, PERF_EVENT_IOC_DISABLE, 0);
		        read(fd, &count, sizeof(long long));
    		    printf("Prefetch Counter value: %lld\n", count);
	            printf("Prefetch H3 sum %lu\n", sum2);
	        }
            else if (N == 4) {
	            printf("Prefetch H4\n");
	    	    ioctl(fd, PERF_EVENT_IOC_RESET, 0);
            	ioctl(fd, PERF_EVENT_IOC_ENABLE, 0);
            	sum2 = time_prefetch_h4(data_pointer);
            	ioctl(fd, PERF_EVENT_IOC_DISABLE, 0);
		        read(fd, &count, sizeof(long long));
    		    printf("Prefetch Counter value: %lld\n", count);
	            printf("Prefetch H4 sum %lu\n", sum2);
	        }
            else if (N == 5) {
	            printf("Prefetch H5\n");
	    	    ioctl(fd, PERF_EVENT_IOC_RESET, 0);
            	ioctl(fd, PERF_EVENT_IOC_ENABLE, 0);
            	sum2 = time_prefetch_h5(data_pointer);
            	ioctl(fd, PERF_EVENT_IOC_DISABLE, 0);
		        read(fd, &count, sizeof(long long));
    		    printf("Prefetch Counter value: %lld\n", count);
	            printf("Prefetch H5 sum %lu\n", sum2);
	        }
            else if (N == 6) {
	            printf("Prefetch H6\n");
	    	    ioctl(fd, PERF_EVENT_IOC_RESET, 0);
            	ioctl(fd, PERF_EVENT_IOC_ENABLE, 0);
            	sum2 = time_prefetch_h6(data_pointer);
            	ioctl(fd, PERF_EVENT_IOC_DISABLE, 0);
	        	read(fd, &count, sizeof(long long));
    		    printf("Prefetch Counter value: %lld\n", count);
	            printf("Prefetch H6 sum %lu\n", sum2);
	        }
            else if (N == 7) {
	            printf("Prefetch H7\n");
	    	    ioctl(fd, PERF_EVENT_IOC_RESET, 0);
            	ioctl(fd, PERF_EVENT_IOC_ENABLE, 0);
            	sum2 = time_prefetch_h7(data_pointer);
            	ioctl(fd, PERF_EVENT_IOC_DISABLE, 0);
		        read(fd, &count, sizeof(long long));
    		    printf("Prefetch Counter value: %lld\n", count);
	            printf("Prefetch H7 sum %lu\n", sum2);
	        }
            else if (N == 8) {
	            printf("Prefetch H8\n");
	    	    ioctl(fd, PERF_EVENT_IOC_RESET, 0);
            	ioctl(fd, PERF_EVENT_IOC_ENABLE, 0);
            	sum2 = time_prefetch_h8(data_pointer);
            	ioctl(fd, PERF_EVENT_IOC_DISABLE, 0);
		        read(fd, &count, sizeof(long long));
    		    printf("Prefetch Counter value: %lld\n", count);
	            printf("Prefetch H8 sum %lu\n", sum2);
	        }
            else if (N == 9) {
	            printf("Prefetch H9\n");
	    	    ioctl(fd, PERF_EVENT_IOC_RESET, 0);
            	ioctl(fd, PERF_EVENT_IOC_ENABLE, 0);
            	sum2 = time_prefetch_h9(data_pointer);
            	ioctl(fd, PERF_EVENT_IOC_DISABLE, 0);
		        read(fd, &count, sizeof(long long));
    		    printf("Prefetch Counter value: %lld\n", count);
	            printf("Prefetch H9 sum %lu\n", sum2);
	        }

            N++;

        }

    	close(fd);
}
