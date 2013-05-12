info_TEXINFOS = bnf++.texi
bnf___TEXINFOS = gpl.texi

man_MANS = bnf++.1
bnf____MANS = inman
HELP2MAN = help2man
noinst_SCRIPTS = $(HELP2MAN)
EXTRA_DIST = $(noinst_SCRIPTS) $(HELP2MAN) $(bnf____MANS)

bnf++.1: ../src/bnf++ $(HELP2MAN) $(bnf____MANS)
	$(PERL) $(HELP2MAN) --name="C++ langugage parser generator for BNF syntax" --include=inman ../src/bnf++ >$@

MAINTAINERCLEANFILES = $(man_MANS) bnf++.info
