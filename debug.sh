echo "<-> Cleaning up..."

rm ./bin/Debug/*
rm ./obj/Debug/*
rm Chlorophyll.make
rm Makefile

echo "<-> Making headers..."
for file in $(find ./src/ -name "*.[ch]")
do
  makeheaders $file
  echo "<!> Headers for" $file "made"
done

echo "<-> Running premake..."
premake5 gmake2
echo "<-> Running make..."
make
echo "<-> Starting program..."
./bin/Debug/Chlorophyll
echo "<-> Done!"
