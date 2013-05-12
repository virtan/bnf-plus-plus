EXTRA_DIST = *.h *.cc

AM_CPPFLAGS=-DTEMPLATES_DIR=\"$(datadir)/bnf++/templates\"

bin_PROGRAMS = bnf++
bnf___SOURCES = bnf++gen.cc bnf++main.cc
bnf___DEPENDENCIES = bnf++parser.h bnf++parser.cc bnf++gen.h bnf++help.h bnf++version.h
