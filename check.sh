i=1
rm -rf tests
mkdir tests
while [ $i -le 10000 ] ;
do
    ./factorization full $i | grep INCORRECT
    if [ $? -eq "0" ] ; then full echo $i ; fi
    ./factorization fermat $i | grep INCORRECT
    if [ $? -eq "0" ] ; then echo fermat $i ; fi
    ./factorization polflo $i | grep INCORRECT
    if [ $? -eq "0" ] ; then echo polflo $i ; fi
    ./factorization brent $i | grep INCORRECT
    if [ $? -eq "0" ] ; then echo polflo $i ; fi
    ./factorization pollard $i | grep INCORRECT
    if [ $? -eq "0" ] ; then echo polflo $i ; fi
    i=$((${i} + 1))
    echo $i
done
