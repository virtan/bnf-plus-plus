SUBDIRS = src doc
EXTRA_DIST = bnf++.bnf++ templates

install-exec-hook:
	$(INSTALL) -d $(datadir)/bnf++/templates
	$(INSTALL) templates/base.tpl $(datadir)/bnf++/templates/base.tpl
	$(INSTALL) templates/base_uv.tpl $(datadir)/bnf++/templates/base_uv.tpl
	$(INSTALL) templates/template.tpl $(datadir)/bnf++/templates/template.tpl
	$(INSTALL) templates/template_uv.tpl $(datadir)/bnf++/templates/template_uv.tpl
