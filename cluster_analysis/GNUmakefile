PROGNAME = cluster_analysis
SOURCEFILES = main.cc Cluster.cc DataManager.cc
OBJS    = $(patsubst %.cc, %.o, $(SOURCEFILES))

ROOTCFLAGS   := $(shell root-config --cflags)
ROOTLIBS     := $(shell root-config --libs)
ROOTGLIBS    := $(shell root-config --glibs)

LDFLAGS       = -O
LIBS         += $(ROOTLIBS)
CFLAGS       += $(ROOTCFLAGS) -std=c++0x

#  Not sure why Minuit isn't being included -- put in by hand
#  #
LIBS         += -lMinuit -L /opt/root/lib \
   			        -lCore -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lTree -lRint -lPostscript -lMatrix \
	   		        -lPhysics -lMathCore -lThread -pthread -lm -ldl -rdynamic \
				        -lSpectrum -lboost_system -lboost_filesystem -lboost_program_options

%.o: %.cc
	        g++ ${CFLAGS} -c  -g -o $@ $<

$(PROGNAME):    $(OBJS)
	        g++ -o $@ $(OBJS) $(LDFLAGS) $(LIBS)

test:
	        @echo $(ROOTCFLAGS)

clean:  
	        -rm -f ${PROGNAME} ${OBJS}
