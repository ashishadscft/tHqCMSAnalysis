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
	rm -rf *.gz
	rm -rf *.snm*
	rm -rf *.nlo
	rm -rf *.nls
	rm -rf presentacion-tesis.pdf
	rm -rf $presentacion-tesis.ps
	rm -rf $presentacion-tesis.dvi
	rm -rf *#*
	rm -f ./*/*.aux
	echo "Cleaning complete!"
	exit
else
	echo "Shell script for compiling the PhD Thesis"
	echo "Usage: sh ./compile-presentacion-tesis.sh [OPTIONS] [presentacion-tesis]"
	echo "[option]  compile: Compiles the PhD Thesis"
	echo "[option]  clean: removes temporary files no presentacion-tesis required"
	exit
fi
fi

presentacion-tesis=$2;

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
	rm -rf *.snm
	rm -rf *.gz
	rm -rf *.nav*
	rm -rf *.out*
	rm -rf *.nlo
	rm -rf *.nls
	rm -rf presentacion-tesis.pdf
	rm -rf $presentacion-tesis.ps
	rm -rf $presentacion-tesis.dvi
	rm -rf *#*
	rm -f ./*/*.aux
	echo "Cleaning complete!"
	exit
elif [ $1 = $compile ]; then
	echo "Compiling your PhD Thesis...please wait...!"
	pdflatex -interaction=nonstopmode $presentacion-tesis.tex
	bibtex $presentacion-tesis.aux 	
	makeindex $presentacion-tesis.aux
	makeindex $presentacion-tesis.idx
	makeindex $presentacion-tesis.nlo -s nomencl.ist -o $presentacion-tesis.nls
	pdflatex -interaction=nonstopmode $presentacion-tesis.tex
	makeindex $presentacion-tesis.nlo -s nomencl.ist -o $presentacion-tesis.nls
	pdflatex -interaction=nonstopmode $presentacion-tesis.tex
	echo "Success!"
	exit
fi


if test -z "$3"
then
	exit
fi
