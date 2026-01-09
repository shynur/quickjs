SHELL := /bin/bash -O globstar

.PHONY: all
all: quickjs.pdf quickjs.html

version.texi: ../../src/version.txt
	@echo "@set VERSION `cat $<`" > $@

%.pdf: %.texi version.texi
	texi2pdf --clean -o $@ -q $<

%.html.pre: %.texi version.texi
	makeinfo --html --no-headers --no-split --number-sections -o $@ $<

%.html: %.html.pre
	sed -e 's|</style>|</style>\n<meta name="viewport" content="width=device-width, initial-scale=1.0">|' < $< > $@

.PHONY: clean
clean:
	rm -f ./?*.html ./?*.pdf
	rm -f version.texi
