<?php
use cache\InMemoryCache;
use cache\MemcacheCache;
use cache\StackCache;
use cache\FileCache;

class CacheClassTesting extends PHPUnit_Framework_TestCase {
	public function testInMemoryCache() {
		global $sourceValue;
		$sourceValue = 'value';
		$sourceKey = '_unit_test_key_';
		$cache = new InMemoryCache();
		$cacheValue = $cache->get($sourceKey,function() {
			global $sourceValue;
			return $sourceValue;
		});
		$this->assertEquals($cacheValue,$sourceValue);
		$this->assertEquals($cache->haveValue($sourceKey),true);
		$cache->delete($sourceKey);
		$this->assertEquals($cache->haveValue($sourceKey),false);
		$cache->setValue($sourceKey,$sourceValue);
		$this->assertEquals($cache->haveValue($sourceKey),true);
		$cache->delete($sourceKey);
		$this->assertEquals($cache->haveValue($sourceKey),false);
		$cache->setValue($sourceKey,$sourceValue);
		unset($cache); //clear
		$cache = new InMemoryCache();
		$this->assertEquals($cache->haveValue($sourceKey),false);
		$cache->delete($sourceKey);
    }
	
	public function testMemcacheCache() {
		$mem = new Memcache();
		$mem->addServer('localhost',11211);
		global $sourceValue;
		$sourceValue = 'value';
		$sourceKey = '_unit_test_key_';
		$cache = new MemcacheCache($mem);
		$cacheValue = $cache->get($sourceKey,function() {
			global $sourceValue;
			return $sourceValue;
		});
		$this->assertEquals($cacheValue,$sourceValue);
		$this->assertEquals($cache->haveValue($sourceKey),true);
		$cache->delete($sourceKey);
		$this->assertEquals($cache->haveValue($sourceKey),false);
		$cache->setValue($sourceKey,$sourceValue);
		$this->assertEquals($cache->haveValue($sourceKey),true);
		$cache->delete($sourceKey);
		$this->assertEquals($cache->haveValue($sourceKey),false);
		$cache->setValue($sourceKey,$sourceValue);
		unset($cache); //clear
		$cache = new MemcacheCache($mem);
		$this->assertEquals($cache->haveValue($sourceKey),true);
		$cache->delete($sourceKey);
	}
	
	public function testStackCache() {
		if ( ! is_dir('/tmp/filecache_test') ) {
			mkdir("/tmp/filecache_test");
		}
		$mem = new Memcache();
		$mem->addServer('localhost',11211);
		$imc = new InMemoryCache();
		$mcc = new MemcacheCache($mem);
		$fc = new FileCache("/tmp/filecache_test");
		global $sourceValue;
		$sourceValue = 'value';
		$sourceKey = '_unit_test_key_';
		$cache = new StackCache(array(
			$imc,
			$mcc,
			$fc
		));
		$cacheValue = $cache->get($sourceKey,function() {
			global $sourceValue;
			return $sourceValue;
		});
		$this->assertEquals($cacheValue,$sourceValue);
		$this->assertEquals($cache->haveValue($sourceKey),true);
		$cache->delete($sourceKey);
		$this->assertEquals($cache->haveValue($sourceKey),false);
		$cache->setValue($sourceKey,$sourceValue);
		$this->assertEquals($cache->haveValue($sourceKey),true);
		$cache->delete($sourceKey);
		$this->assertEquals($cache->haveValue($sourceKey),false);
		$cache->setValue($sourceKey,$sourceValue);
		unset($imc);unset($mcc);unset($cache);unset($fc);
		$imc = new InMemoryCache();
		$mcc = new MemcacheCache($mem);
		$fc = new FileCache("/tmp/filecache_test");
		$cache = new StackCache(array(
			$imc,
			$mcc,
			$fc
		));
		$this->assertEquals($imc->haveValue($sourceKey),false);
		$this->assertEquals($mcc->haveValue($sourceKey),true);
		$this->assertEquals($fc->haveValue($sourceKey),true);
		$this->assertEquals($cache->haveValue($sourceKey),true);
		$cache->delete($sourceKey);
		$this->assertEquals($imc->haveValue($sourceKey),false);
		$this->assertEquals($mcc->haveValue($sourceKey),false);
		$this->assertEquals($fc->haveValue($sourceKey),false);
		
	}
	
	public function testFileCache() {
		global $sourceValue;
		$sourceValue = 'value';
		$sourceKey = '_unit_test_key_';
		if ( ! is_dir('/tmp/filecache_test') ) {
			mkdir("/tmp/filecache_test");
		}
		$cache = new FileCache("/tmp/filecache_test");
		$cacheValue = $cache->get($sourceKey,function() {
			global $sourceValue;
			return $sourceValue;
		});
		$this->assertEquals($cacheValue,$sourceValue);
		$this->assertEquals($cache->haveValue($sourceKey),true);
		$cache->delete($sourceKey);
		$this->assertEquals($cache->haveValue($sourceKey),false);
		$cache->setValue($sourceKey,$sourceValue);
		$this->assertEquals($cache->haveValue($sourceKey),true);
		$cache->delete($sourceKey);
		$this->assertEquals($cache->haveValue($sourceKey),false);
		$cache->setValue($sourceKey,$sourceValue);
		unset($cache); //clear
		$cache = new FileCache("/tmp/filecache_test");
		$this->assertEquals($cache->haveValue($sourceKey),true);		
		$cache->delete($sourceKey);		
	}
}




