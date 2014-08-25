if [ -e TAGS ]
then
    rm TAGS
fi
find ./src -name "*cpp" -exec etags -a {} \;
find ./src -name "*hpp" -exec etags -a {} \;
