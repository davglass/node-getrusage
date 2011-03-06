all:
	node-waf configure build

clean:
	rm -r ./build
	rm -r .lock-wscript

