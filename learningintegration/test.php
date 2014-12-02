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
		return $fingerprint->getLabel($this->getOption(ValueFormatter::OPT_LANG))->getText();
	} catch(OutOfBoundsException $e) {
		return '';
	}
}
