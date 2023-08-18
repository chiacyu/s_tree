all:s_tree.c
	gcc s_tree.c -o s_tree.out
clean:
	rm -f s_tree.out