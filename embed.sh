#!/bin/sh
for file in $*
do
    if [ -d "${file}" ]; then
        continue
    fi
    echo $file
	name=$(basename $file)
    h_name=$(echo $name | sed 's/\.\|-/_/g');
    cd $(dirname $file)
    printf "#include \"EmbedData.h\"\n" > ../src/gui/res/$name.h
	xxd -i $name		>> ../src/gui/res/$name.h
    printf "EmbedData ${h_name}_data = { ${h_name}, ${h_name}_len };\n" >> ../src/gui/res/$name.h
    cd ..
	#identify -format "\nunsigned int ${h_name}_w = %[fx:w];\nunsigned int ${h_name}_h = %[fx:h];\nunsigned int ${h_name}_pitch = %[p];\nunsigned int ${h_name}_depth = %[depth];" $file >> src/gui/res/$name.h
done
