# mharj-php-cache
generic key/value cache system via callback
```
$value = $cache->get($key, function() {
    return "value";
});
```


Unit test
```
phpunit --colors --testdox -c test/config.xml
```
