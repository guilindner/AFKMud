for i in `ls *.txt`
do
    echo "Editing $i ..."
    git mv $i ${i%.*}.md
done
