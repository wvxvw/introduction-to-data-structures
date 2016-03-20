ASSIGNMENTS := $(wildcard ./assignment*/)
ARCHIVES := $(ASSIGNMENTS:/=.tar.gz)

%.tar.gz: %/
	git archive -o ./exports/$@ HEAD $<"/*"

package: $(ARCHIVES)
