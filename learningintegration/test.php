<?php
use Doctrine\Common\Cache\ArrayCache;
use Mediawiki\Api\MediawikiApi;
use PPP\Wikidata\Cache\WikibaseEntityCache;
use ValueFormatters\ValueFormatter;
use Wikibase\Api\WikibaseFactory;
use Wikibase\DataModel\Entity\ItemId;

require_once(__DIR__ . '/vendor/autoload.php');

function getLabelForItemID($itemId) {
	$itemId = new ItemId($itemId);
	$wikibaseFactory = new WikibaseFactory(new MediawikiApi('http://www.wikidata.org/w/api.php'));
	$entityProvider = new \PPP\Wikidata\WikibaseEntityProvider(
		$wikibaseFactory->newRevisionGetter(),
		new WikibaseEntityCache(new ArrayCache()) //TODO use an other cache if needed
	);

	$fingerprint = $entityProvider->getItem($itemId)->getFingerprint();
	try {
		return $fingerprint->getLabel('en')->getText();
	} catch(OutOfBoundsException $e) {
		return '';
	}
}

function proceed()
{
	$in = fopen("instance.txt", 'r');
	$out = fopen("word", 'w');

	$line=fgets($in);

	while($line=fgets($in))
	{
		preg_match_all("#Q[0-9]+#",$line,$matches);
		fputs($out,"\"".getLabelForItemID($matches[0][0])."\" \"".getLabelForItemID($matches[0][1])."\"\n");
	}
}

proceed();
?>
