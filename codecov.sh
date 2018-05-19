#!/bin/bash
#!/
for filename in `find . | grep -r -i --include \*.h --include \*.cpp`;
do
    gcov-5 -n -o . $filename > /dev/null;
done
