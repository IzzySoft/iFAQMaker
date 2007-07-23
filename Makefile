# Makefile for ifaqmaker
# $Id$

DESTDIR=
prefix=/usr/local
datarootdir=$(DESTDIR)$(prefix)/share
datadir=$(datarootdir)
INSTALL=

install: installdirs
	cp -pr * $(datarootdir)/ifaqmaker
	rm -f $(datarootdir)/ifaqmaker/Makefile

installdirs:
	mkdir -p $(datarootdir)/ifaqmaker

uninstall:
	rm -rf $(datarootdir)/ifaqmaker

