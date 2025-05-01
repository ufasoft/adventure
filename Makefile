MACRO11=RT11 MACRO

OBJS=advent.OBJ io.OBJ traps.OBJ text.OBJ data.OBJ init.OBJ

advent.sav.bin: advent.sav
	cp $< $@

advent.sav: $(OBJS) defcfg.inc macros.inc text.inc rt11.mlb
	pclink11 /EXECUTE:$@ $(OBJS)

%.OBJ : %.mac macros.inc rt11.mlb
	$(MACRO11) /LIST:$(basename $<).lst $<+rt11.mlb/LIB

text.OBJ : text.mac text.inc rt11.mlb
	$(MACRO11) /LIST:$(basename $<).lst $<+rt11.mlb/LIB

rt11.mlb: rt11.cfg
	RT11 LIBRARY/MACRO/CREATE rt11 rt11.cfg

clean:
	-rm *.bin *.11m *.LST *.OBJ *.sav
