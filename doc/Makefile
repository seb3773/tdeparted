APPNAME ?= tdeparted
LANGS ?= en fr
PREFIX ?= /usr
DOCDIR ?= $(PREFIX)/share/doc/tde/HTML
XMLTO ?= xmlto
XMLLINT ?= xmllint
XSLTPROC ?= xsltproc
DOCBOOK_XSL ?= /usr/share/xml/docbook/stylesheet/docbook-xsl/html/docbook.xsl

.PHONY: all validate html install clean

all: validate

validate:
	@set -e; \
	for lang in $(LANGS); do \
		if [ -f "$$lang/index.docbook" ]; then \
			echo "Validating $$lang/index.docbook"; \
			$(XMLLINT) --noout "$$lang/index.docbook"; \
		fi; \
	done

html:
	@set -e; \
	for lang in $(LANGS); do \
		if [ -f "$$lang/index.docbook" ]; then \
			echo "Building HTML for $$lang"; \
			mkdir -p "build/$$lang"; \
			if command -v $(XMLTO) >/dev/null 2>&1; then \
				( cd "build/$$lang" && $(XMLTO) html-nochunks "../../$$lang/index.docbook" ); \
			else \
				echo "xmlto not found, using xsltproc fallback"; \
				$(XSLTPROC) -o "build/$$lang/index.html" "$(DOCBOOK_XSL)" "$$lang/index.docbook"; \
			fi; \
		fi; \
	done

install:
	@set -e; \
	for lang in $(LANGS); do \
		if [ -f "$$lang/index.docbook" ]; then \
			dest="$(DESTDIR)$(DOCDIR)/$$lang/$(APPNAME)"; \
			echo "Installing $$lang manual to $$dest"; \
			install -d "$$dest"; \
			install -m 0644 "$$lang/index.docbook" "$$dest/index.docbook"; \
			if [ -d "$$lang/figures" ]; then \
				install -d "$$dest/figures"; \
				cp -a "$$lang/figures/." "$$dest/figures/"; \
			fi; \
		fi; \
	done

clean:
	rm -rf build
