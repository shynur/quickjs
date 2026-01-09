SHELL := /bin/bash -O globstar

.PHONY: dev
dev:
	$(MAKE) clean
	cmake -S src --preset $@
	cmake --build build --parallel
	cmake --install build --prefix install
	LD_LIBRARY_PATH=$$LD_LIBRARY_PATH$${LD_LIBRARY_PATH+:}`pwd`/install/lib ./install/bin/qjs -e 'console.log("Hello, world!")'

.PHONY: upload
upload:
	rm -rf ~/.conan/data/QuickJS/*/shynur/dev
	cd src; conan create . shynur/dev
	# ^^^^^ It have to be written this way otherwise (conan create src) conan can't find 'version.txt'.
	conan upload --parallel -c --force --all -r my QuickJS/\*@shynur/dev

.PHONY: doc
doc:
	cd doc/info; $(MAKE)

.PHONY: clean
clean:
	cd src/test_package; $(MAKE) clean
	cd doc/info; $(MAKE) clean
	rm -rf tmp
	rm -rf build install
	rm -f ./**/?*~ ./**/.?*~ ./**/#?*# ./**/.#?*#

%/:
	mkdir -p $@
	-chmod -R a+rwx $@
