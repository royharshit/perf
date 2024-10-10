CC = gcc
CXX = g++
RM = rm -f

SRCS = hw_cycles.c
OBJS = hw_cycles

SRCS_L2 = l2_mshrs.c
OBJS_L2 = l2_mshrs

# Target for building the main executable
$(OBJS): $(SRCS)
	$(CC) -o $(OBJS) $(SRCS)

# Target for building the L2 executable
$(OBJS_L2): $(SRCS_L2)
	$(CC) -o $(OBJS_L2) $(SRCS_L2)

# Target for running the main executable
run: $(OBJS)
	./$(OBJS)

# Target for running the L2 executable
run_l2: $(OBJS_L2)
	./$(OBJS_L2)

# Target for cleaning up
clean:
	$(RM) $(OBJS) $(OBJS_L2)

