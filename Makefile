SHELL := /bin/bash -O globstar

.PHONY: clean
clean:
	rm -rf build install
