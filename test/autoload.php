<?php
set_include_path(implode(PATH_SEPARATOR, array(get_include_path(),'../')));
spl_autoload_register('spl_autoload');
