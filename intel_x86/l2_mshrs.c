#include <unistd.h>
#include <asm/unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <inttypes.h>
#include <sys/ioctl.h>
#include <linux/perf_event.h>

#define ALL_DATA_RD_EVENT 0x60
#define ALL_DATA_RD_UMASK 0x08 

#define CYCLES_WITH_DATA_RD_EVENT 0x60
#define CYCLES_WITH_DATA_RD_UMASK 0x08
#define CYCLES_WITH_DATA_RD_CMASK 0x01

struct read_format {
  uint64_t nr;
  struct {
    uint64_t value;
    uint64_t id;
  } values[];
};

const size_t memsize = 128 * 1024 * 1024;
const size_t elems = memsize / sizeof(uint32_t);
const int DISTANCE = 1;

int hash(int data) {
    return 10*data % 5;
}

uint32_t time_nonprefetch_h1(uint32_t *data, int fd, struct read_format *rf) {
    uint32_t sum = 0;
    struct read_format *rfi = rf;
    for (int i = 0; i < elems; i++) {
    	sum += hash(data[i]);
	if (i%1048576 == 0) {
	    read(fd, rfi, 4096);
	    rfi = (struct read_format*)((char*)rfi + 4096);
    	}
    }
    return sum;
}

uint32_t time_prefetch_h1(uint32_t *data, int fd, struct read_format *rf) {
    uint32_t sum = 0;
    struct read_format *rfi = rf;
    for (int i = 0; i < elems; i++) {
        __builtin_prefetch(&data[i + DISTANCE]);
    	sum += hash(data[i]);
	if (i%1048576 == 0) {
	    read(fd, rfi, 4096);
	    rfi = (struct read_format*)((char*)rfi + 4096);
	}
    }
    return sum;
}


uint32_t time_nonprefetch_h2(uint32_t *data, int fd, struct read_format *rf) {
    uint32_t sum = 0; 
    struct read_format *rfi = rf;
    for (int i = 0; i < elems; i++) {
    	sum += hash(hash(data[i]));
	if (i%1048576 == 0) {
	    read(fd, rfi, 4096);
	    rfi = (struct read_format*)((char*)rfi + 4096);
	}
    }
    return sum;
}


uint32_t time_prefetch_h2(uint32_t *data, int fd, struct read_format *rf) {
    uint32_t sum = 0; 
    struct read_format *rfi = rf;
    for (int i = 0; i < elems; i++) {
        __builtin_prefetch(&data[i + DISTANCE]);
    	sum += hash(hash(data[i]));
	if (i%1048576 == 0) {
	    read(fd, rfi, 4096);
	    rfi = (struct read_format*)((char*)rfi + 4096);
	}
    }
    return sum;
}

uint32_t time_nonprefetch_h3(uint32_t *data, int fd, struct read_format *rf) {
    uint32_t sum = 0; 
    struct read_format *rfi = rf;
    for (int i = 0; i < elems; i++) {
    	sum += hash(hash(hash(data[i])));
	if (i%1048576 == 0) {
	    read(fd, rfi, 4096);
	    rfi = (struct read_format*)((char*)rfi + 4096);
	}
    }
    return sum;
}


uint32_t time_prefetch_h3(uint32_t *data, int fd, struct read_format *rf) {
    uint32_t sum = 0; 
    struct read_format *rfi = rf;
    for (int i = 0; i < elems; i++) {
        __builtin_prefetch(&data[i + DISTANCE]);
    	sum += hash(hash(hash(data[i])));
	if (i%1048576 == 0) {
	    read(fd, rfi, 4096);
	    rfi = (struct read_format*)((char*)rfi + 4096);
	}
    }
    return sum;
}


uint32_t time_nonprefetch_h4(uint32_t *data, int fd, struct read_format *rf) {
    uint32_t sum = 0; 
    struct read_format *rfi = rf;
    for (int i = 0; i < elems; i++) {
    	sum += hash(hash(hash(hash(data[i]))));
	if (i%1048576 == 0) {
	    read(fd, rfi, 4096);
	    rfi = (struct read_format*)((char*)rfi + 4096);
	}
    }
    return sum;
}


uint32_t time_prefetch_h4(uint32_t *data, int fd, struct read_format *rf) {
    uint32_t sum = 0; 
    struct read_format *rfi = rf;
    for (int i = 0; i < elems; i++) {
        __builtin_prefetch(&data[i + DISTANCE]);
    	sum += hash(hash(hash(hash(data[i]))));
	if (i%1048576 == 0) {
	    read(fd, rfi, 4096);
	    rfi = (struct read_format*)((char*)rfi + 4096);
	}
    }
    return sum;
}

uint32_t time_nonprefetch_h5(uint32_t *data, int fd, struct read_format *rf) {
    uint32_t sum = 0; 
    struct read_format *rfi = rf;
    for (int i = 0; i < elems; i++) {
    	sum += hash(hash(hash(hash(hash(data[i])))));
	if (i%1048576 == 0) {
	    read(fd, rfi, 4096);
	    rfi = (struct read_format*)((char*)rfi + 4096);
	}
    }
    return sum;
}


uint32_t time_prefetch_h5(uint32_t *data, int fd, struct read_format *rf) {
    uint32_t sum = 0; 
    struct read_format *rfi = rf;
    for (int i = 0; i < elems; i++) {
        __builtin_prefetch(&data[i + DISTANCE]);
    	sum += hash(hash(hash(hash(hash(data[i])))));
	if (i%1048576 == 0) {
	    read(fd, rfi, 4096);
	    rfi = (struct read_format*)((char*)rfi + 4096);
	}
    }
    return sum;
}


uint32_t time_nonprefetch_h6(uint32_t *data, int fd, struct read_format *rf) {
    uint32_t sum = 0; 
    struct read_format *rfi = rf;
    for (int i = 0; i < elems; i++) {
    	sum += hash(hash(hash(hash(hash(hash(data[i]))))));
	if (i%1048576 == 0) {
	    read(fd, rfi, 4096);
	    rfi = (struct read_format*)((char*)rfi + 4096);
	}
    }
    return sum;
}


uint32_t time_prefetch_h6(uint32_t *data, int fd, struct read_format *rf) {
    uint32_t sum = 0; 
    struct read_format *rfi = rf;
    for (int i = 0; i < elems; i++) {
        __builtin_prefetch(&data[i + DISTANCE]);
    	sum += hash(hash(hash(hash(hash(hash(data[i]))))));
	if (i%1048576 == 0) {
	    read(fd, rfi, 4096);
	    rfi = (struct read_format*)((char*)rfi + 4096);
	}
    }
    return sum;
}


uint32_t time_nonprefetch_h7(uint32_t *data, int fd, struct read_format *rf) {
    uint32_t sum = 0; 
    struct read_format *rfi = rf;
    for (int i = 0; i < elems; i++) {
    	sum += hash(hash(hash(hash(hash(hash(hash(data[i])))))));
	if (i%1048576 == 0) {
	    read(fd, rfi, 4096);
	    rfi = (struct read_format*)((char*)rfi + 4096);
	}
    }
    return sum;
}


uint32_t time_prefetch_h7(uint32_t *data, int fd, struct read_format *rf) {
    uint32_t sum = 0; 
    struct read_format *rfi = rf;
    for (int i = 0; i < elems; i++) {
        __builtin_prefetch(&data[i + DISTANCE]);
    	sum += hash(hash(hash(hash(hash(hash(hash(data[i])))))));
	if (i%1048576 == 0) {
	    read(fd, rfi, 4096);
	    rfi = (struct read_format*)((char*)rfi + 4096);
	}
    }
    return sum;
}

uint32_t time_nonprefetch_h8(uint32_t *data, int fd, struct read_format *rf) {
    uint32_t sum = 0; 
    struct read_format *rfi = rf;
    for (int i = 0; i < elems; i++) {
    	sum += hash(hash(hash(hash(hash(hash(hash(hash(data[i]))))))));
	if (i%1048576 == 0) {
	    read(fd, rfi, 4096);
	    rfi = (struct read_format*)((char*)rfi + 4096);
	}
    }
    return sum;
}


uint32_t time_prefetch_h8(uint32_t *data, int fd, struct read_format *rf) {
    uint32_t sum = 0; 
    struct read_format *rfi = rf;
    for (int i = 0; i < elems; i++) {
        __builtin_prefetch(&data[i + DISTANCE]);
    	sum += hash(hash(hash(hash(hash(hash(hash(hash(data[i]))))))));
	if (i%1048576 == 0) {
	    read(fd, rfi, 4096);
	    rfi = (struct read_format*)((char*)rfi + 4096);
	}
    }
    return sum;
}


uint32_t time_nonprefetch_h9(uint32_t *data, int fd, struct read_format *rf) {
    uint32_t sum = 0; 
    struct read_format *rfi = rf;
    for (int i = 0; i < elems; i++) {
    	sum += hash(hash(hash(hash(hash(hash(hash(hash(hash(data[i])))))))));
	if (i%1048576 == 0) {
	    read(fd, rfi, 4096);
	    rfi = (struct read_format*)((char*)rfi + 4096);
	}
    }
    return sum;
}


uint32_t time_prefetch_h9(uint32_t *data, int fd, struct read_format *rf) {
    uint32_t sum = 0; 
    struct read_format *rfi = rf;
    for (int i = 0; i < elems; i++) {
        __builtin_prefetch(&data[i + DISTANCE]);
    	sum += hash(hash(hash(hash(hash(hash(hash(hash(hash(data[i])))))))));
	if (i%1048576 == 0) {
	    read(fd, rfi, 4096);
	    rfi = (struct read_format*)((char*)rfi + 4096);
	}
    }
    return sum;
}


void interpret_data(struct read_format* rf, uint64_t id1, uint64_t id2) {
	for(int i = 0; i<32; i++) {
		struct read_format* rfi = (struct read_format*)((char*)rf + i*4096);
		printf("NR %" PRIu64 "\n", rfi->nr);
		for (int j = 0; j < rfi->nr; j++) {
			if(rfi->values[j].id == id1)
				printf("ALL_DATA_RD %" PRIu64 "\n", rfi->values[j].value);
			else if(rfi->values[j].id == id2)
				printf("CYCLES WITH DATA RD %" PRIu64 "\n", rfi->values[j].value);
		}
		uint64_t mshr = rfi->values[0].value / rfi->values[1].value;
		printf("L2 MSHRs %" PRIu64 "\n", mshr);
	}
}

int main() {

    struct perf_event_attr pe;
    int fd1, fd2;
    uint64_t id1, id2;
    uint64_t val1, val2;
    
    memset(&pe, 0, sizeof(struct perf_event_attr));
    pe.type = PERF_TYPE_RAW;
    pe.size = sizeof(struct perf_event_attr);
    pe.config = ALL_DATA_RD_EVENT | (ALL_DATA_RD_UMASK<<8); 
    pe.disabled = 1; 
    pe.exclude_kernel = 1;
    pe.exclude_hv = 1;
    pe.read_format = PERF_FORMAT_GROUP | PERF_FORMAT_ID;
    fd1 = syscall(__NR_perf_event_open, &pe, 0, -1, -1, 0);
    if (fd1 == -1) {
        fprintf(stderr, "Error opening leader fd1 %llx\\n", pe.config);
        exit(EXIT_FAILURE);
    }
    ioctl(fd1, PERF_EVENT_IOC_ID, &id1);

	    
    memset(&pe, 0, sizeof(struct perf_event_attr));
    pe.type = PERF_TYPE_RAW;
    pe.size = sizeof(struct perf_event_attr);
    pe.config = CYCLES_WITH_DATA_RD_EVENT | (CYCLES_WITH_DATA_RD_UMASK << 8) | (CYCLES_WITH_DATA_RD_CMASK << 24); 
    pe.disabled = 1; 
    pe.exclude_kernel = 1;
    pe.exclude_hv = 1;
    pe.read_format = PERF_FORMAT_GROUP | PERF_FORMAT_ID;
    fd2 = syscall(__NR_perf_event_open, &pe, 0, -1, fd1, 0);
    if (fd2 == -1) {
        fprintf(stderr, "Error opening leader fd2 %llx\\n", pe.config);
        exit(EXIT_FAILURE);
    }
    ioctl(fd2, PERF_EVENT_IOC_ID, &id2);
           

    uint32_t* data = (uint32_t*)malloc(memsize);
    int32_t sum1, sum2;
    struct read_format* rf = (struct read_format*)malloc(4096*32);

    for (uint32_t i = 0; i < elems; i++) {
    	data[i] = i;
    }

    int32_t N = 1;

        while (N < 10) { 
            if (N == 1) {
		printf("Non Prefetch H1\n");
		ioctl(fd1, PERF_EVENT_IOC_RESET, PERF_IOC_FLAG_GROUP);
                ioctl(fd1, PERF_EVENT_IOC_ENABLE, PERF_IOC_FLAG_GROUP);
                sum1 = time_nonprefetch_h1(data, fd1, rf);
                ioctl(fd1, PERF_EVENT_IOC_DISABLE, PERF_IOC_FLAG_GROUP);
                interpret_data(rf, id1, id2);
            }
            else if (N == 2) {
		printf("Non Prefetch H2\n");
		ioctl(fd1, PERF_EVENT_IOC_RESET, PERF_IOC_FLAG_GROUP);
                ioctl(fd1, PERF_EVENT_IOC_ENABLE, PERF_IOC_FLAG_GROUP);
                sum1 = time_nonprefetch_h2(data, fd1, rf);
                ioctl(fd1, PERF_EVENT_IOC_DISABLE, PERF_IOC_FLAG_GROUP);
                interpret_data(rf, id1, id2);
	    }
            else if (N == 3) {
		printf("Non Prefetch H3\n");
		ioctl(fd1, PERF_EVENT_IOC_RESET, PERF_IOC_FLAG_GROUP);
                ioctl(fd1, PERF_EVENT_IOC_ENABLE, PERF_IOC_FLAG_GROUP);
                sum1 = time_nonprefetch_h3(data, fd1, rf);
                ioctl(fd1, PERF_EVENT_IOC_DISABLE, PERF_IOC_FLAG_GROUP);
                interpret_data(rf, id1, id2);
	    }
            else if (N == 4) {
		printf("Non Prefetch H4\n");
		ioctl(fd1, PERF_EVENT_IOC_RESET, PERF_IOC_FLAG_GROUP);
                ioctl(fd1, PERF_EVENT_IOC_ENABLE, PERF_IOC_FLAG_GROUP);
                sum1 = time_nonprefetch_h4(data, fd1, rf);
                ioctl(fd1, PERF_EVENT_IOC_DISABLE, PERF_IOC_FLAG_GROUP);
                interpret_data(rf, id1, id2);
	    }
            else if (N == 5) {
		printf("Non Prefetch H5\n");
		ioctl(fd1, PERF_EVENT_IOC_RESET, PERF_IOC_FLAG_GROUP);
                ioctl(fd1, PERF_EVENT_IOC_ENABLE, PERF_IOC_FLAG_GROUP);
                sum1 = time_nonprefetch_h5(data, fd1, rf);
                ioctl(fd1, PERF_EVENT_IOC_DISABLE, PERF_IOC_FLAG_GROUP);
                interpret_data(rf, id1, id2);
	    }
            else if (N == 6) {
		printf("Non Prefetch H6\n");
		ioctl(fd1, PERF_EVENT_IOC_RESET, PERF_IOC_FLAG_GROUP);
                ioctl(fd1, PERF_EVENT_IOC_ENABLE, PERF_IOC_FLAG_GROUP);
                sum1 = time_nonprefetch_h6(data, fd1, rf);
                ioctl(fd1, PERF_EVENT_IOC_DISABLE, PERF_IOC_FLAG_GROUP);
                interpret_data(rf, id1, id2);
	    }
            else if (N == 7) {
		printf("Non Prefetch H7\n");
		ioctl(fd1, PERF_EVENT_IOC_RESET, PERF_IOC_FLAG_GROUP);
                ioctl(fd1, PERF_EVENT_IOC_ENABLE, PERF_IOC_FLAG_GROUP);
                sum1 = time_nonprefetch_h7(data, fd1, rf);
                ioctl(fd1, PERF_EVENT_IOC_DISABLE, PERF_IOC_FLAG_GROUP);
                interpret_data(rf, id1, id2);
	    }
            else if (N == 8) {
		printf("Non Prefetch H8\n");
		ioctl(fd1, PERF_EVENT_IOC_RESET, PERF_IOC_FLAG_GROUP);
                ioctl(fd1, PERF_EVENT_IOC_ENABLE, PERF_IOC_FLAG_GROUP);
                sum1 = time_nonprefetch_h8(data, fd1, rf);
                ioctl(fd1, PERF_EVENT_IOC_DISABLE, PERF_IOC_FLAG_GROUP);
                interpret_data(rf, id1, id2);
	    }
            else if (N == 9) {
		printf("Non Prefetch H9\n");
		ioctl(fd1, PERF_EVENT_IOC_RESET, PERF_IOC_FLAG_GROUP);
                ioctl(fd1, PERF_EVENT_IOC_ENABLE, PERF_IOC_FLAG_GROUP);
                sum1 = time_nonprefetch_h9(data, fd1, rf);
                ioctl(fd1, PERF_EVENT_IOC_DISABLE, PERF_IOC_FLAG_GROUP);
                interpret_data(rf, id1, id2);
	    }
            if (N == 1) {
		printf("Prefetch H1\n");
		ioctl(fd1, PERF_EVENT_IOC_RESET, PERF_IOC_FLAG_GROUP);
                ioctl(fd1, PERF_EVENT_IOC_ENABLE, PERF_IOC_FLAG_GROUP);
            	sum2 = time_prefetch_h1(data, fd1, rf);
                ioctl(fd1, PERF_EVENT_IOC_DISABLE, PERF_IOC_FLAG_GROUP);
                interpret_data(rf, id1, id2);
	    }
            else if (N == 2) {    
		printf("Prefetch H2\n");
		ioctl(fd1, PERF_EVENT_IOC_RESET, PERF_IOC_FLAG_GROUP);
                ioctl(fd1, PERF_EVENT_IOC_ENABLE, PERF_IOC_FLAG_GROUP);
            	sum2 = time_prefetch_h2(data, fd1, rf);
                ioctl(fd1, PERF_EVENT_IOC_DISABLE, PERF_IOC_FLAG_GROUP);
                interpret_data(rf, id1, id2);
	    }
            else if (N == 3) {
		printf("Prefetch H3\n");
		ioctl(fd1, PERF_EVENT_IOC_RESET, PERF_IOC_FLAG_GROUP);
                ioctl(fd1, PERF_EVENT_IOC_ENABLE, PERF_IOC_FLAG_GROUP);
            	sum2 = time_prefetch_h3(data, fd1, rf);
                ioctl(fd1, PERF_EVENT_IOC_DISABLE, PERF_IOC_FLAG_GROUP);
                interpret_data(rf, id1, id2);
	    }
            else if (N == 4) {
		printf("Prefetch H4\n");
		ioctl(fd1, PERF_EVENT_IOC_RESET, PERF_IOC_FLAG_GROUP);
                ioctl(fd1, PERF_EVENT_IOC_ENABLE, PERF_IOC_FLAG_GROUP);
            	sum2 = time_prefetch_h4(data, fd1, rf);
                ioctl(fd1, PERF_EVENT_IOC_DISABLE, PERF_IOC_FLAG_GROUP);
                interpret_data(rf, id1, id2);
	    }
            else if (N == 5) {
		printf("Prefetch H5\n");
		ioctl(fd1, PERF_EVENT_IOC_RESET, PERF_IOC_FLAG_GROUP);
                ioctl(fd1, PERF_EVENT_IOC_ENABLE, PERF_IOC_FLAG_GROUP);
            	sum2 = time_prefetch_h5(data, fd1, rf);
                ioctl(fd1, PERF_EVENT_IOC_DISABLE, PERF_IOC_FLAG_GROUP);
                interpret_data(rf, id1, id2);
	    }
            else if (N == 6) {
		printf("Prefetch H6\n");
		ioctl(fd1, PERF_EVENT_IOC_RESET, PERF_IOC_FLAG_GROUP);
                ioctl(fd1, PERF_EVENT_IOC_ENABLE, PERF_IOC_FLAG_GROUP);
            	sum2 = time_prefetch_h6(data, fd1, rf);
                ioctl(fd1, PERF_EVENT_IOC_DISABLE, PERF_IOC_FLAG_GROUP);
                interpret_data(rf, id1, id2);
	    }
            else if (N == 7) {
		printf("Prefetch H7\n");
		ioctl(fd1, PERF_EVENT_IOC_RESET, PERF_IOC_FLAG_GROUP);
                ioctl(fd1, PERF_EVENT_IOC_ENABLE, PERF_IOC_FLAG_GROUP);
            	sum2 = time_prefetch_h7(data, fd1, rf);
                ioctl(fd1, PERF_EVENT_IOC_DISABLE, PERF_IOC_FLAG_GROUP);
                interpret_data(rf, id1, id2);
	    }
            else if (N == 8) {
		printf("Prefetch H8\n");
		ioctl(fd1, PERF_EVENT_IOC_RESET, PERF_IOC_FLAG_GROUP);
                ioctl(fd1, PERF_EVENT_IOC_ENABLE, PERF_IOC_FLAG_GROUP);
            	sum2 = time_prefetch_h8(data, fd1, rf);
                ioctl(fd1, PERF_EVENT_IOC_DISABLE, PERF_IOC_FLAG_GROUP);
                interpret_data(rf, id1, id2);
	    }
            else if (N == 9) {
		printf("Prefetch H9\n");
		ioctl(fd1, PERF_EVENT_IOC_RESET, PERF_IOC_FLAG_GROUP);
                ioctl(fd1, PERF_EVENT_IOC_ENABLE, PERF_IOC_FLAG_GROUP);
            	sum2 = time_prefetch_h9(data, fd1, rf);
                ioctl(fd1, PERF_EVENT_IOC_DISABLE, PERF_IOC_FLAG_GROUP);
                interpret_data(rf, id1, id2);
	    }
            N++;

        }
  
    ioctl(fd1, PERF_EVENT_IOC_DISABLE, 0);
    close(fd1);
}
