#!/bin/bash
# first arg is dir
# second arg is query
IFS=$'\t\n'   # Split on newlines and tabs (but not on spaces)


cd ~/Notes/
# for file in $(fd -I -e md -e org); do
file="$(fzf)"
contents="$(cat $file | tr -d '\n')"
echo -e "Finished Vars, staring search \n\n"
search_score "${file}" "${contents}"
   # sed 's/^.*\t//' |\
   # sed 's/^/\//' 


# sk -i --ansi -m -c 'search_score_loop.bash ~/Notes/Org/  "{}"'  
