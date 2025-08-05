DEVLIBS = -lglfw -lGL -lm -ldl -lfreetype -lcglm -lportaudio -lsndfile
FORM = ../FormNetwork/
TITLE = DreamCoffin

game: 
	$(MAKE) libFormGlfw.a -C $(FORM)
	$(MAKE) DreamCoffin 

$(TITLE): main.c $(FORM)FormNetwork.h $(FORM)libFormGlfw.a $(FORM)glad.o oneiro.c oneiro.h coffin.c coffin.h
	cp $(FORM)FormNetwork.h .
	cp $(FORM)libFormGlfw.a .
	cp $(FORM)glad.o .
	gcc -g -o $(TITLE) main.c glad.o libFormGlfw.a $(DEVLIBS)

$(FORM)FormNetwork.h:
	$(MAKE) FormNetwork.h -C $(FORM)

$(FORM)libFormGlfw.a:
	$(MAKE) libFormGlfw.a -C $(FORM)

$(FORM)glad.o:
	$(MAKE) glad.o -C $(FORM)

clean:
	rm -f $(TITLE) 
	rm -f vgcore*
	$(MAKE) clean -C $(FORM)

fclean:
	$(MAKE) fclean -C $(FORM)
	rm -f vgcore*
	rm -f $(TITLE) 

log:
	valgrind --leak-check=full ./$(TITLE) > poo 2>&1
