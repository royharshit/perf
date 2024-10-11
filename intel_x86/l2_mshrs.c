#include <unistd.h>
#include <asm/unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include <sys/ioctl.h>
#include <sys/syscall.h>
#include <linux/perf_event.h>

#define ALL_DATA_RD_EVENT 0x60
#define ALL_DATA_RD_UMASK 0x08 


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

int setup_perf_event(int event_code, int event_type) {
    struct perf_event_attr pea;
    memset(&pea, 0, sizeof(pea));

    pea.type = event_type;  // Use raw type for custom events

    pea.config = event_code;	

    pea.size = sizeof(pea);
    pea.disabled = 1;
    pea.exclude_kernel = 1;   // Exclude kernel events
    pea.exclude_hv = 1;       // Exclude hypervisor events

    int fd = perf_event_open(&pea, 0, -1, -1, 0);
    if (fd == -1) {
        perror("perf_event_open");
        exit(1);
    }
    return fd;
}


void disable_performance_counters(int num_events, int *fds) {

    for (int i = 0; i < num_events; ++i) {
	ioctl(fds[i], PERF_EVENT_IOC_DISABLE, 0);
    }

}

void enable_performance_counters(int num_events, int *fds) {

    for (int i = 0; i < num_events; ++i) {
        ioctl(fds[i], PERF_EVENT_IOC_RESET, 0);
        ioctl(fds[i], PERF_EVENT_IOC_ENABLE, 0);
    }

}

void read_event(int num_events, int *fds, long long int (*pc)[20], int h) {

    for (int i = 0; i < num_events; ++i) { 
        read(fds[i], &pc[i][h], sizeof(pc[i][h]));
         
    }
    
}

void post_processing(int num_events, long long int (*pc)[20]) {

    for (uint32_t i = 0; i < 10; i++) {
	    printf("L2 Mshr Non-Prefetch) H%d = %f\n", i, (double)pc[1][i]/pc[0][i]);
    } 

    for (uint32_t i = 10; i < 20; i++) {
	    printf("L2 Mshr Prefetch) H%d = %f\n", i-10, (double)pc[1][i]/pc[0][i]);
    } 

}

void close_fds(int num_events, int *fds) {

    for (int i = 0; i < num_events; ++i) {
	    close(fds[i]);
    }

}    

int main() {

    uint32_t* data = (uint32_t*)malloc(memsize);
    uint32_t** data_pointer = (uint32_t**)malloc(elems*sizeof(uint32_t*));
    uint64_t sum1;

    for (uint32_t i = 0; i < elems; i++) {
    	data[i] = i;
	    data_pointer[i] = &data[i];
    }

    randomize(data_pointer, elems);

    long int event_codes[] = {PERF_COUNT_HW_CPU_CYCLES, ALL_DATA_RD_EVENT | ALL_DATA_RD_UMASK << 8}; 
    const char *event_names[] = {"Event 1", "Event 2"};
    long int event_types[] = {PERF_TYPE_HARDWARE, PERF_TYPE_RAW};

    // Number of events
    size_t num_events = sizeof(event_codes) / sizeof(event_codes[0]);

    // Array to hold file descriptors
    int fds[num_events];

    // Set up performance counters
    for (size_t i = 0; i < num_events; ++i) {
        fds[i] = setup_perf_event(event_codes[i], event_types[i]);
    }

    //Array to store pc
    long long int pc[num_events][20];

    int32_t N = 0;

        while (N < 10) { 
            if (N == 0) {
	            printf("Non-Prefetch H0\n");
		        enable_performance_counters(num_events, fds);
	            sum1 = time_nonprefetch_h0(data_pointer);
		        disable_performance_counters(num_events, fds);
		        read_event(num_events, fds, pc, 0);
            } else if (N == 1) {
	            printf("Non-Prefetch H1\n");
		        enable_performance_counters(num_events, fds);
	            sum1 = time_nonprefetch_h1(data_pointer);
		        disable_performance_counters(num_events, fds);
		        read_event(num_events, fds, pc, 1);
            } else if (N == 2) {
	            printf("Non-Prefetch H2\n");
		        enable_performance_counters(num_events, fds);
	            sum1 = time_nonprefetch_h2(data_pointer);
		        disable_performance_counters(num_events, fds);
		        read_event(num_events, fds, pc, 2);
            } else if (N == 3) {
	            printf("Non-Prefetch H3\n");
		        enable_performance_counters(num_events, fds);
	            sum1 = time_nonprefetch_h3(data_pointer);
		        disable_performance_counters(num_events, fds);
		        read_event(num_events, fds, pc, 3);
            } else if (N == 4) {
	            printf("Non-Prefetch H4\n");
		        enable_performance_counters(num_events, fds);
	            sum1 = time_nonprefetch_h4(data_pointer);
		        disable_performance_counters(num_events, fds);
		        read_event(num_events, fds, pc, 4);
            } else if (N == 5) {
	            printf("Non-Prefetch H5\n");
		        enable_performance_counters(num_events, fds);
	            sum1 = time_nonprefetch_h5(data_pointer);
		        disable_performance_counters(num_events, fds);
		        read_event(num_events, fds, pc, 5);
            } else if (N == 6) {
	            printf("Non-Prefetch H6\n");
		        enable_performance_counters(num_events, fds);
	            sum1 = time_nonprefetch_h6(data_pointer);
		        disable_performance_counters(num_events, fds);
		        read_event(num_events, fds, pc, 6);
            } else if (N == 7) {
	            printf("Non-Prefetch H7\n");
		        enable_performance_counters(num_events, fds);
	            sum1 = time_nonprefetch_h7(data_pointer);
		        disable_performance_counters(num_events, fds);
		        read_event(num_events, fds, pc, 7);
            } else if (N == 8) {
	            printf("Non-Prefetch H8 \n");
		        enable_performance_counters(num_events, fds);
	            sum1 = time_nonprefetch_h8(data_pointer);
		        disable_performance_counters(num_events, fds);
		        read_event(num_events, fds, pc, 8);
            } else if (N == 9) {
	            printf("Non-Prefetch H9\n");
		        enable_performance_counters(num_events, fds);
	            sum1 = time_nonprefetch_h9(data_pointer);
		        disable_performance_counters(num_events, fds);
		        read_event(num_events, fds, pc, 9);
            }

	        N++;

	}

	N = 0;
	while (N < 10) {
            if (N == 0) {
	            printf("Prefetch H0\n");
		        enable_performance_counters(num_events, fds);
	            sum1 = time_prefetch_h0(data_pointer);
		        disable_performance_counters(num_events, fds);
		        read_event(num_events, fds, pc, 10);
            } else if (N == 1) {
	            printf("Prefetch H1\n");
		        enable_performance_counters(num_events, fds);
	            sum1 = time_prefetch_h1(data_pointer);
		        disable_performance_counters(num_events, fds);
		        read_event(num_events, fds, pc, 11);
            } else if (N == 2) {
	            printf("Prefetch H2\n");
		        enable_performance_counters(num_events, fds);
	            sum1 = time_prefetch_h2(data_pointer);
		        disable_performance_counters(num_events, fds);
		        read_event(num_events, fds, pc, 12);
            } else if (N == 3) {
	            printf("Prefetch H3\n");
		        enable_performance_counters(num_events, fds);
	            sum1 = time_prefetch_h3(data_pointer);
		        disable_performance_counters(num_events, fds);
		        read_event(num_events, fds, pc, 13);
            } else if (N == 4) {
	            printf("Prefetch H4\n");
		        enable_performance_counters(num_events, fds);
	            sum1 = time_prefetch_h4(data_pointer);
        		disable_performance_counters(num_events, fds);
		        read_event(num_events, fds, pc, 14);
            } else if (N == 5) {
	            printf("Prefetch H5\n");
		        enable_performance_counters(num_events, fds);
	            sum1 = time_prefetch_h5(data_pointer);
		        disable_performance_counters(num_events, fds);
		        read_event(num_events, fds, pc, 15);
            } else if (N == 6) {
	            printf("Prefetch H6\n");
		        enable_performance_counters(num_events, fds);
	            sum1 = time_prefetch_h6(data_pointer);
		        disable_performance_counters(num_events, fds);
		        read_event(num_events, fds, pc, 16);
            } else if (N == 7) {
	            printf("Prefetch H7\n");
		        enable_performance_counters(num_events, fds);
	            sum1 = time_prefetch_h7(data_pointer);
		        disable_performance_counters(num_events, fds);
		        read_event(num_events, fds, pc, 17);
            } else if (N == 8) {
	            printf("Prefetch H8 \n");
		        enable_performance_counters(num_events, fds);
	            sum1 = time_prefetch_h8(data_pointer);
		        disable_performance_counters(num_events, fds);
		        read_event(num_events, fds, pc, 18);
            } else if (N == 9) {
	            printf("Prefetch H9\n");
		        enable_performance_counters(num_events, fds);
	            sum1 = time_prefetch_h9(data_pointer);
		        disable_performance_counters(num_events, fds);
	    	    read_event(num_events, fds, pc, 19);
            }
	   
    	    N++;

        }

	post_processing(num_events, pc);

}
