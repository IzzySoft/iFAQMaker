# Makefile for ifaqmaker
# $Id$

DESTDIR=
prefix=/usr/local
datarootdir=$(DESTDIR)$(prefix)/share
datadir=$(datarootdir)/ifaqmaker
INSTALL=

WEBROOT=$(DESTDIR)/var/www
LINKTO=$(WEBROOT)/ifaqmaker

install: installdirs
	cp -pr * $(datadir)
	rm -f $(datadir)/Makefile
	if [ ! -e $(LINKTO) ]; then ln -s $(datadir) $(LINKTO); fi

installdirs:
	mkdir -p $(datadir)
	if [ ! -e $(WEBROOT) ]; then mkdir -p $(WEBROOT); fi

uninstall:
	rm -rf $(datadir)
	linkstat=`readlink $(LINKTO)`
	if [ "$linkstat" = "$(datadir)" ]; then rm -f $(LINKTO); fi

