<?php
//use PPP\Wikidata\ValueFormatters;

//$vp=new WikibaseValueFormatter();

//$vp->format

$in = fopen("wikidata-instances.nt", 'r');
$out = fopen("instance.txt", 'w');

$line=fgets($in);

while($line=fgets($in))
{
	if(preg_match("#^<http://www\.wikidata\.org/entity/Q[0-9]+> <http://www\.w3\.org/1999/02/22-rdf-syntax-ns\#type> <http://www\.wikidata\.org/entity/Q[0-9]+> \.#", $line))
	{
		preg_match_all("#Q[0-9]+#",$line,$matches);
		fputs($out,$matches[0][0]." ".$matches[0][1]."\n");
	}
}

fclose($in);
fclose($out);

?>
