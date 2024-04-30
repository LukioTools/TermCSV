
.PHONY: v3
v3:
	cman v3.cfg
	c++ -std=c++20 -Wall testv3.cpp v3/bin/v3core.a -o testv3