CC = emcc
SDK_PATH = $(abspath $(PWD)/../orbit-sdk-c)
EMCCFLAGS = -s WASM=1 -s ERROR_ON_UNDEFINED_SYMBOLS=0 -I$(SDK_PATH)

SRC = src/main.cpp
WASM_DEBUG = build/soralet.wasm
WASM_RELEASE = build/soralet-optimized.wasm

help:
	@echo "usage: make <\033[36mtargets\033[0m>"
	@echo
	@echo "available targets:"
	@grep -E '^[a-zA-Z._-]+:.*?## .*$$' Makefile | awk 'BEGIN {FS = ":.*?## "}; {printf "  \033[36m%-10s\033[0m %s\n", $$1, $$2}'

build: $(SRC) ## Build debug WASM
	$(CC) -O0 $(EMCCFLAGS) $(SDK_PATH)/soracom/orbit.c $(SRC) -o $(WASM_DEBUG)

release: $(SRC) ## Build release WASM
	$(CC) -Os $(EMCCFLAGS) $(SDK_PATH)/soracom/orbit.c $(SRC) -o $(WASM_RELEASE)

clean: ## Remove WASM(s) under build/
	rm -fr build/*.wasm

.PHONY: help build release clean