#!/bin/bash
# first arg is dir
# second arg is query
IFS=$'\t\n'   # Split on newlines and tabs (but not on spaces)


cd "${1}"
for file in $(fd -I -e md -e org); do
    search_score $(realpath $file) "${2}"
    echo -e "\t${file}"
done |\
   sort -rn #|\
   # sed 's/^.*\t//' |\
   # sed 's/^/\//' 


# sk -i --ansi -m -c 'search_score_loop.bash ~/Notes/Org/  "{}"'  
