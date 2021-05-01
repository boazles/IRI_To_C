CC = gcc # Flag for implicit rules 
FC = gfortran
FCFLAGS = -O3  
# Flag for implicit rules. Turn on debug info
CFLAGS = -O3  
LIBS =
INCLUDES =
TARGET = run
SRCS = cira.for igrf.for iridreg.for iriflip.for irifun.for irirtam.for irisub.for iritec.for  wrapper.c

LDFLAGS = -lgfortran -lm

OBJS = $(addsuffix .o,$(basename $(SRCS)))

$(TARGET) : $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)
%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<
%.o: %.for 
	$(FC) $(FCFLAGS) -o $@ -c $<

.PHONY : clean
clean:
	rm -f *.o