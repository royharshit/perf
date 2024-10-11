CC = gcc
CXX = g++
RM = rm -f

SRCS = hw_cycles.c l2_mshrs.c 
OBJS = hw_cycles l2_mshrs 

# Target for building all executables
all: $(OBJS)

$(OBJS): % : %.c
	$(CC) -o $@ $<

# Target for running individual executables
run_hw_cycles: hw_cycles
	sudo ./hw_cycles > cycles.txt

run_l2: l2_mshrs
	sudo ./l2_mshrs > l2_mshrs.txt

# Target for running all executables
run_all: run_hw_cycles run_l2 

# Target for cleaning up
clean:
	$(RM) $(OBJS)

