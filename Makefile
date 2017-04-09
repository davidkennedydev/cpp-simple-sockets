TEST_PATH=./test
TARGETS=all test clean coverage

.PHONY: $(TARGETS)

$(TARGETS):
	cd $(TEST_PATH) && $(MAKE) $@
