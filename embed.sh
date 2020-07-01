#!/bin/sh
for file in $*
do
    if [ -d "${file}" ]; then
        continue
    fi
    #objcopy -I binary --rename-section .data=.const [...]  $file ../src/gui/res/$(basename $file).o
	name=$(basename $file)
    h_name=$(echo $name | sed 's/\./_/g');
    cd $(dirname $file)
	xxd -i $name		> ../src/gui/res/$name.h
    cd ..
	identify -format "\nunsigned int ${h_name}_w = %[fx:w];\nunsigned int ${h_name}_h = %[fx:h];\nunsigned int ${h_name}_pitch = %[p];\nunsigned int ${h_name}_depth = %[depth];" $file >> src/gui/res/$name.h
done
