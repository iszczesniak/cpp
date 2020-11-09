PDFS = containers.pdf containers-lab.pdf
PRGS = extract range
OBJS =

CXXFLAGS = -std=c++17

all: $(PDFS) $(PRGS) $(OBJS)

%.pdf: %.tex
	TEXINPUTS=.:..: pdflatex $<
	TEXINPUTS=.:..: pdflatex $<
