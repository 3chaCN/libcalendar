target:
	gcc -fpic -shared event.c -o libcalendar.so

clean:
	rm *.so *.o
