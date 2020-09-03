fileName=proj3

pdf:
	latex ${fileName}.tex	
	dvips -t a4 ${fileName}.dvi
	ps2pdf -sPAPERSIZE=a4 ${fileName}.ps

clean:
	rm ${fileName}.dvi
	rm ${fileName}.ps
	rm ${fileName}.pdf
	rm ${fileName}.log
	rm ${fileName}.aux
	rm ${fileName}.out