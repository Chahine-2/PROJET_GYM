## Process this file with automake to produce Makefile.in

INCLUDES = \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\" \
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	@PACKAGE_CFLAGS@

bin_PROGRAMS = gym

gym_SOURCES = \
	main.c \
	support.c support.h \
	interface.c interface.h \
	callbacks.c callbacks.h\
	callbacks1.c callbacks1.h\
	callbacks2.c callbacks2.h \
	callbacks3.c callbacks3.h \
	callbacks4.c callbacks4.h \
	callbacks5.c callbacks5.h \
	member.c member.h \
	coach.c coach.h \
	centre.c centre.h \
	user.c user.h \
	display.c display.h\
	evenement.c evenement.h\
	equipement.c equipement.h\
	courssportifs.c courssportifs.h

gym_LDADD = @PACKAGE_LIBS@ $(INTLLIBS)

