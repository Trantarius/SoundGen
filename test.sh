 
COMP="g++ -w -std=c++17 $(find src -name "*.cpp") -I. -o exe"
echo $COMP
$COMP
echo
echo compiled
echo
./exe
rm exe
