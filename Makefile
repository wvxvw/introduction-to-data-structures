ASSIGNMENTS := $(wildcard ./assignment*/)
TGZ_ARCHIVES := $(ASSIGNMENTS:/=.tar.gz)
ZIP_ARCHIVES := $(ASSIGNMENTS:/=.zip)
DOXYGEN := doxygen

%.tar.gz: %/
	git archive -o ./exports/$@ HEAD $<"/*"

%.zip: %/
	git archive -o ./exports/$@ HEAD $<"/*"

package: $(TGZ_ARCHIVES) $(ZIP_ARCHIVES) lib.tar.gz lib.zip doc.zip doc.tar.gz

lib:
	$(MAKE) -C ./lib

doc:
	$(DOXYGEN)

$(ASSIGNMENTS):
	$(MAKE) -C $@

default: lib $(ASSIGNMENTS) doc package
