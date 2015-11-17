# mharj-php-cache
generic key/value cache system via callback
```
$cache = new xxxCache();
$value = $cache->get($key, function() {
    return "value";
});
```
Parameters
```
$cache = new xxxCache();
$value = $cache->get($key, $param1, $param2, ... , function($param1,$param2,...) {
    return $param1.$param2.$param3...
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
