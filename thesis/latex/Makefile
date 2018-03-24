# Sample Makefile
# $Id: Makefile 387 2012-11-12 15:11:48Z vlado $

THESIS_NAME=yaser_thesis

help:
	@echo make all

.PHONY: all

pdf: all clean

all:
	# latex -enable-write18 $(THESIS_NAME).tex
	# latex -enable-write18 $(THESIS_NAME).tex
	pdflatex -shell-escape -enable-write18 $(THESIS_NAME).tex

	bibtex $(THESIS_NAME)
	# latex -enable-write18 $(THESIS_NAME)
	# dvips -t letter $(THESIS_NAME).dvi -o $(THESIS_NAME).ps
	pdflatex -shell-escape -enable-write18 $(THESIS_NAME).tex
	pdflatex -shell-escape -enable-write18 $(THESIS_NAME).tex

body:
	latex $(THESIS_NAME).tex

glossary:
	latex $(THESIS_NAME).tex
	makeindex -s $(THESIS_NAME) -o $(THESIS_NAME).gls $(THESIS_NAME).glo

bibliography:
	latex $(THESIS_NAME).tex
	bibtex $(THESIS_NAME)

clean:
	-rm *.dvi *.aux *.bbl *.blg *.log *.toc *.lof *.lot *.glo *.gls *.ist *.ilg *.fls *.ps .DS_Store *.md5 *.dep *.dpth *.fdb_latexmk *.auxlock *.synctex.gz *.xdv

spotless: clean
	-rm *.pdf

