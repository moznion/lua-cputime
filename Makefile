.PHONY: build test

build:
	luarocks build

test: build
	LUA_CPATH=./?.so lua test/test.lua

