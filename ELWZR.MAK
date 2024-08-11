###############################################################################
#####                 This makefile generates ELWZR.DLL                   #####
###############################################################################
!include $(WGDEV)\src\gcrules.mak

VIRDIR = .\GCVIRDAT

DLLLIB = $(DLLLIB) wgserver.lib galgsbl.lib
PRODLL =
DEFILE = 
PARSEOPTS = $(PARSEOPTS) -I. -DIS30 

VIRFILES = \
     GCVIRDAT\elwzr.vir

OBJFILES = \
     ${TEMPDIR}\elwzr.obj 

start:              \
     $(GCBUILD)     \
     elwzr.dll

elwzr.dll:         \
     $(OBJFILES)    \
     $(DLLLIB)      \
     $(DEFILE)      \
     $(VIRFILES)
     $(LINK) $(LIBCMD) @&&|
$(PRODLL) $(OBJFILES)
$(RUNDIR)\$&
$(RUNDIR)\$&
$(DLLLIB) $(LINKDLL)
$(DEFILE)
|
