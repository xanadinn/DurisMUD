for i in *.obj; do
  echo $i
  ./anticonv2.pl < $i > $i.new
  mv $i.new $i
done
