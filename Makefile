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
	conan create . shynur/dev
	conan upload --parallel -c --force --all -r my QuickJS/\*@shynur/dev

.PHONY: clean
clean:
	cd test_package; $(MAKE) clean
	rm -rf tmp
	rm -rf build install
	rm -f ./**/?*~ ./**/.?*~ ./**/#?*# ./**/.#?*#

%/:
	mkdir -p $@
	-chmod -R a+rwx $@
