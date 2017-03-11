TEST_PATH=./test/SocketBuffer
TARGETS=all test clean coverage

.PHONY: $(TARGETS)

$(TARGETS):
	cd $(TEST_PATH) && $(MAKE) $@
