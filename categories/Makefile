PDFS = categories.pdf categories-lab.pdf
PRGS = $(patsubst %.cc,%,$(wildcard *.cc))

all: $(PDFS) $(PRGS)

%.pdf: %.tex
	TEXINPUTS=.:..: pdflatex $<
	TEXINPUTS=.:..: pdflatex $<
