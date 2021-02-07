##
# Searching Program
#
# @file
# @version 0.1
#
# Use Tabs not Spaces
# https://opensource.com/article/18/8/what-how-makefile
# https://www.gnu.org/software/make/manual/html_node/How-Make-Works.html
#
# If a very large DTM is used, it is necessary to use ~-mcmodel=medium~.
make_c: ./search_score.c
	gcc search_score.c -Wall -Og -o search_score -lm                         
run: ./search_score
	./search_score ./README.org
# end

