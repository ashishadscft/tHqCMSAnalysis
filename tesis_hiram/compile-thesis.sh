#!/bin/bash
# A script to compile the PhD Thesis - Krishna Kumar 
# Distributed under GPLv2.0 License

compile="compile";
clean="clean";

if test -z "$2"
then
if [ $1 = $clean ]; then
	echo "Cleaning please wait ..."
	rm -f *~
	rm -rf *.aux
	rm -rf *.bbl
	rm -rf *.blg
	rm -rf *.d
	rm -rf *.fls
	rm -rf *.ilg
	rm -rf *.ind
	rm -rf *.toc*
	rm -rf *.lot*
	rm -rf *.lof*
	rm -rf *.log
	rm -rf *.idx
	rm -rf *.out*
	rm -rf *.nlo
	rm -rf *.nls
	rm -rf $thesis.pdf
	rm -rf $thesis.ps
	rm -rf $thesis.dvi
	rm -rf *#* 
	echo "Cleaning complete!"
	exit
else
	echo "Shell script for compiling the PhD Thesis"
	echo "Usage: sh ./compile-thesis.sh [OPTIONS] [thesis]"
	echo "[option]  compile: Compiles the PhD Thesis"
	echo "[option]  clean: removes temporary files no thesis required"
	exit
fi
fi

thesis=$2;

if [ $1 = $clean ]; then
	echo "Cleaning please wait ..."
	rm -f *~
	rm -rf *.aux
	rm -rf *.bbl
	rm -rf *.blg
	rm -rf *.d
	rm -rf *.fls
	rm -rf *.ilg
	rm -rf *.ind
	rm -rf *.toc*
	rm -rf *.lot*
	rm -rf *.lof*
	rm -rf *.log
	rm -rf *.idx
	rm -rf *.out*
	rm -rf *.nlo
	rm -rf *.nls
	rm -rf $thesis.pdf
	rm -rf $thesis.ps
	rm -rf $thesis.dvi
	rm -rf *#* 
	echo "Cleaning complete!"
	exit
elif [ $1 = $compile ]; then
	echo "Compiling your PhD Thesis...please wait...!"
	pdflatex -interaction=nonstopmode $thesis.tex
	bibtex $thesis.aux 	
	makeindex $thesis.aux
	makeindex $thesis.idx
	makeindex $thesis.nlo -s nomencl.ist -o $thesis.nls
	pdflatex -interaction=nonstopmode $thesis.tex
	makeindex $thesis.nlo -s nomencl.ist -o $thesis.nls
	pdflatex -interaction=nonstopmode $thesis.tex
	echo "Success!"
	exit
fi


if test -z "$3"
then
	exit
fi
