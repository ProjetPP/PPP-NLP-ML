<?php
$in = fopen("wikidata-instances.nt", 'r');

$i=0;
while($line=fgets($in))$i++;

print($i);

fclose($in);
?>
