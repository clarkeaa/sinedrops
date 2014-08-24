if [ -e TAGS ]
then
    rm TAGS
fi
find ./src -name *cpp -or -name *hpp -exec etags -a {} \;
