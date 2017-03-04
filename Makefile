TEST_PATH=./test/SocketBuffer
TARGETS=all test clean

.PHONY: $(TARGETS)

$(TARGETS):
	cd $(TEST_PATH) && $(MAKE) $@
