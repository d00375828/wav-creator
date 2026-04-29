all: build

build:
	make -C library-audiofiles install
	make -C library-envelope install
	make -C library-waveform install
	make -C library-instrument install	
	make -C library-score install
	make -C library-application install
	make -C library-score-io install
	make -C library-commands install
	make -C program-waveform-test all
	make -C program-wav-file-creator all
	make -C program-audio-track-creator all
	make -C program-hello all
	make -C program-questions3 all
	make -C program-envelope-test all
	make -C program-instrument-test all
	make -C program-instrument-designer all


clean:
	make -C library-audiofiles clean
	make -C library-envelope clean
	make -C library-waveform clean
	make -C library-instrument clean
	make -C library-score clean
	make -C library-application clean
	make -C library-score-io clean
	make -C library-commands clean
	make -C program-waveform-test clean 
	make -C program-wav-file-creator clean 
	make -C program-audio-track-creator clean
	make -C program-hello clean
	make -C program-questions3 clean
	make -C program-envelope-test clean 
	make -C program-instrument-test clean 
	make -C program-instrument-designer clean 
	-cd lib && rm -f *.a 
	-cd include && rm -f *.h
