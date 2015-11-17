# mharj-php-cache
generic key/value cache system via callback
```
$cache = new xxxCache();
$value = $cache->get($key, function() {
    return "value";
});
```
Or cache stack
```
$cache = new StackCache(array(
    new xxxCache(),
    new yyyCache(),
    new zzzCache()
));
$value = $cache->get($key, function() {
    return "value";
});
```

Unit test
```
phpunit --colors --testdox -c test/config.xml
```
